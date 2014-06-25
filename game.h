/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

				File: game.h

*/


#include "interface.h"



#ifndef GAME_H
#define GAME_H

/* Empty the BOARD, fills it and draw with game elements
 *
 * Put Robot at 0,0
 * Put N_BARRIERS barriers randomly
 * Put [1, ( (N_BARRIERS*10)/100 )] charge stations randomly
 * Put the exit at (EXIT_X, EXIT_Y)
 */
void new_game(int n_barriers, int exit_x, int exit_y);


/* Moves the robot 1 step
 *
 * If possible return 1, else return 0
 *
 * LOGS the movement
 * Charge robot energy when arrives a charge station
 * Invokes WIN and NEW GAME routines whe robot arrive the exit
 */
int move_robot();


/* Rotates the robot in DIR direction
 *
 *
 * LOGS the movement
 */
void rotate_robot(char dir);


#endif
