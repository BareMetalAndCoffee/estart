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

void state4c_initialise(state4c *instance, state4c_state initialState)
{
    instance->next.state = initialState;
    instance->next.action = STATE4C_TRANSITION;
    instance->curr.state = NULL;
    instance->curr.action = ~STATE4C_TRANSITION;
}