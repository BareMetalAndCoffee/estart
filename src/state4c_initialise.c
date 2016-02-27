/**
 * 
 */
#include <state4c.h>
#include <stdlib.h>

void state4c_initialise(state4c *instance, state4c_state initialState)
{
    instance->next.state = initialState;
    instance->next.action = STATE4C_TRANSITION;
    instance->curr.state = NULL;
    instance->curr.action = ~STATE4C_TRANSITION;
}