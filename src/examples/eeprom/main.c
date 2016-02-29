/**
 * This file is part of State4C.
 *
 * State4C is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * State4C is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with State4C.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <state4c.h>
#include <time.h>
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

    srand(time(NULL));
    instance.isError = rand() > (RAND_MAX / 2);

    state4c_go((state4c *) &instance);
}

static state4c_action get_active_application_errors(eepromObj *instance)
{
    printf("In get_active_application_errors\n");
    return S4C_TRANSITION(instance, read_eeprom_error_table);
}

static state4c_action read_eeprom_error_table(eepromObj *instance)
{
    printf("In read_eeprom_error_table\n");
    if (instance->isError)
    {
        return S4C_TRANSITION(instance, write_eeprom_error_table);
    }
    else
    {
        return S4C_TRANSITION(instance, write_eeprom_error);
    }
}

static state4c_action write_eeprom_error_table(eepromObj *instance)
{
    printf("In write_eeprom_error_table\n");
    return S4C_TRANSITION(instance, write_eeprom_success);
}

static state4c_action write_eeprom_success(eepromObj *instance)
{
    (void) instance;
    printf("In write_eeprom_success\n");
    return S4C_FINISHED(instance);
}

static state4c_action write_eeprom_error(eepromObj *instance)
{
    (void) instance;
    printf("In write_eeprom_error\n");
    return S4C_FINISHED(instance);
}

int main(void)
{
    write_eeprom();
    return EXIT_SUCCESS;   
}
