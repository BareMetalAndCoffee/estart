#include <state4c.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
  state4c super;
  bool isError;
} eepromObj;

static void write_eeprom(void);
static state4c_action get_active_application_errors(eepromObj *instance);
static state4c_action read_eeprom_error_table(eepromObj *instance);
static state4c_action write_eeprom_error_table(eepromObj *instance);
static state4c_action write_eeprom_success(eepromObj *instance);
static state4c_action write_eeprom_error(eepromObj *instance);

static void write_eeprom(void)
{
    eepromObj instance;
    state4c_initialise((state4c *) &instance, (state4c_state) get_active_application_errors);

    instance.isError = false;

    state4c_go((state4c *) &instance);
}

static state4c_action get_active_application_errors(eepromObj *instance)
{
    printf("In get_active_application_errors\n");
    STATE4C_SET_NEXT_STATE(instance, read_eeprom_error_table);
    return STATE4C_TRANSITION;
}

static state4c_action read_eeprom_error_table(eepromObj *instance)
{
    printf("In read_eeprom_error_table\n");
    if (instance->isError)
    {
        STATE4C_SET_NEXT_STATE(instance, write_eeprom_error_table);
        return STATE4C_TRANSITION;
    }
    else
    {
        STATE4C_SET_NEXT_STATE(instance, write_eeprom_error);
        return STATE4C_TRANSITION;
    }
}

static state4c_action write_eeprom_error_table(eepromObj *instance)
{
    printf("In write_eeprom_error_table\n");
    STATE4C_SET_NEXT_STATE(instance, write_eeprom_success);
    return STATE4C_TRANSITION;
}

static state4c_action write_eeprom_success(eepromObj *instance)
{
    (void) instance;
    printf("In write_eeprom_success\n");
    return STATE4C_FINISHED;
}

static state4c_action write_eeprom_error(eepromObj *instance)
{
    (void) instance;
    printf("In write_eeprom_error\n");
    return STATE4C_FINISHED;
}

int main(void)
{
    write_eeprom();
    return EXIT_SUCCESS;   
}
