#ifndef STATE_4_C_H
#define STATE_4_C_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef STATE4C_REQUIRE
#include <assert.h>
#define STATE4C_REQUIRE(cond_)  assert((cond_))
#endif

typedef enum
{
    STATE4C_TRANSITION,
    STATE4C_FINISHED
} state4c_action;

typedef state4c_action (*state4c_state)(void *);

typedef struct
{
    struct
    {
        state4c_state state;
        state4c_action action;
    } next;
    struct
    {
        state4c_state state;
        state4c_action action;
    } curr;
} state4c;


void state4c_initialise(state4c *instance, state4c_state initialState);
void state4c_go(state4c *instance);
void state4c_setTransition(state4c *instance, state4c_state nextState);


#define STATE4C_SET_NEXT_STATE(instance_, func_) \
    state4c_setTransition((state4c *) instance_, (state4c_state) func_) 

#ifdef __cplusplus
}
#endif
#endif