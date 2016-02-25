# state4c
state4c is a state machine framework of sorts that helps when refactoring legacy c. 
It is not a state machine framework with add ons. That is, you won't find support
for event handling, active objects, or Harel state machines. In fact, it probably 
struggles to implement finite state machines. Anyhow, it is what it is. I hope it helps.
Happy C refactoring!

## The Story of C Refactoring
Like many times before, you are searching for a bug. It is an old C program (could be
for an embedded system or linux server). You are putting debug statements all over the 
code attempting to find the bug. You finnally find it and it looks something like this:

    void UpdateSomething(.....) {
        ....
        printf("Starting to write to eeprom...\n");
        
        write_eeprom();
        
        printf("Eeprom written successfully...\n"); 
        
Okay, you think you have it because the last print statement is never executed. Wahoo, you go
look at write_eeprom().

### Horror
What you find is this:

    void write_eeprom() {
      if () {
        .... 40 lines
        if () {
          if () {
           ... 20 lines
           goto: error
          }
          elseif () {
           ... 30 lines
           goto: awesomeplace
          }
        }
        else ...
        
        do {
          if () {
            .... 50 lines 
        }
        while (get_some_value_from_somewhere() != -1)
        goto: success
      }
      ..... 300 lines
      // O you thought I was done.
      switch (get_some_value_that_seems_to_have_nothing_to_do_with_flash())
      {
        case 1
        ....
        case N:
        ....
      }
      
      // It is now line 3450 and yay you go to the goto
      error:
        .... more lines
      awesomeplace
        .... more lines
      success:
        ... You don't believe this could ever be triggered.
    }

### And State4c To the Rescue
Instead of spending 4 days of your life devoted to finding the 5 lines that currently 
don't work, rewrite it like this.

    typedef struct
    {
      State4c super;    // Inherit state4c
      uint32_t someVar; // This var already existed as a global var in file
      bool anotherVar;  // so did this one
      ....              // and so on. Give you data some structure, please :)
    } MyStateObject;
    
    void write_eeprom() {
      MyStateObject me;
      state4c_initialise(&me.super, get_active_application_errors);

      me.someVar = 0;
      me.anotherVar = false;
      
      state4c_go(&me);
    }
    
    state4c_state get_active_application_errors(MyStateObject *me) {
      ... code to get active application errors
      return S4C_TRANSITION(read_eeprom_error_table);
    }
    
    state4c_state read_eeprom_error_table(MyStateObject *me) {
      start_eeprom_read(ERROR_TABLE);
      do {
        if (is_eeprom_byte_ready()) {
          me->eeprom_data[i] = get_eeprom_byte();
        }
        
        if (is_eeprom_read_finished()) {
          return S4C_TRANSITION(calculate_new_eeprom_error_table);
        }
      } while(elapse_time < time_allowed);
      return S4C_TRANSITION(set_error_state); 
    }
    
    state4c_state set_error_state(MyStateObject *me) {
      .... Set error variables.
      return S4C_FINISHED();
    }
    
And so on until you are satisfied that the behaviour is easy to follow.
