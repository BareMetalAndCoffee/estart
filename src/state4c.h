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
 * 
 * *******************************************************************
 * Usage:
 * 
 * Create a instance of state4c, then initialise it to your initial state.
 * Once you are ready set the state machine off by calling state4c_go()
 * 
 *  state4c instance;
 *  state4c_initialise(&instance, YOUR_INITIAL_STATE);
 * 
 *  state4c_go(&instance)
 */
#ifndef STATE_4_C_H
#define STATE_4_C_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>

/**
 * By default State4c will assert if a required condition failed. This can 
 * be overwitten by defining STATE4C_REQUIRED
 */
#ifndef STATE4C_REQUIRE
#include <assert.h>
#define STATE4C_REQUIRE(cond_)  assert((cond_))
#endif

/**
 * Return codes from a state function
 */
typedef enum
{
    STATE4C_TRANSITION,
    STATE4C_FINISHED
} state4c_action;

/**
 * Signature for state function
 */
typedef state4c_action (*state4c_state)(void *);

/**
 * This is a private structure that should not be interfered with. Please see
 * usage in header.
 */
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

/**
 * Help macro to make a transition to another state from within a state.
 * @see Usage at top of the header
 */
#define S4C_TRANSITION(instance_, func_)                                            \
            state4c_setTransition((state4c *) instance_, (state4c_state) func_) ?   \
                STATE4C_TRANSITION : STATE4C_FINISHED


/**
 * Help macro to inform dispatcher that state machine is finished.
 * @see Usage at top of the header
 */
#define S4C_FINISHED(instance_)                                                     \
            state4c_setTransition((state4c *) instance_, (state4c_state) NULL) ?    \
                STATE4C_FINISHED : STATE4C_FINISHED

/**
 * Initialise the state machine to transition to initialState when the 
 * state machine is activated with state4c_go()
 * 
 * @param   instance        The state machine instance. See header top for usage
 * @param   initialState    The initial state
 */
void state4c_initialise(state4c *instance, state4c_state initialState);

/**
 * Starts the state machine and will not finish until told to by returning a
 * STATE4C_FINISHED from within a state4c_state function
 * 
 * @param   instance        The state machine instance. See header top for usage
 */
void state4c_go(state4c *instance);

/**
 * Set the next state to transition to when a STATE4C_TRANSITION is return
 * from within a state4c_state function
 * 
 * @param   instance        The state machine instance. See header top for usage
 * @param   nextState       The next state
 */
bool state4c_setTransition(state4c *instance, state4c_state nextState);

#ifdef __cplusplus
}
#endif
#endif