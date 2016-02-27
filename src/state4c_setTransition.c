/**
 * 
 */
#include <state4c.h>

void state4c_setTransition(state4c *instance, state4c_state nextState)
{
    instance->next.state = nextState;
}