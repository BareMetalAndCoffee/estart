#include <state4c.h>
#include <stdlib.h>

void state4c_go(state4c *instance)
{
    while ((instance->next.state != NULL) &&
           (instance->next.action == STATE4C_TRANSITION))
    {
        instance->next.action = instance->next.state((void *) instance);

        if (instance->next.action == STATE4C_TRANSITION)
        {
            /**
            * Require the user to set the next state via state4c_setTransition
            */
            STATE4C_REQUIRE(instance->next.state != instance->curr.state &&
                            instance->next.state != NULL);
        }
    }
}
