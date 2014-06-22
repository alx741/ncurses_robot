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

				File: interface.h

*/



/*
						########## Interface description  ###########


   	+----------------------------------------------------------------------------------+
	|_______________________________  HELP window ___________________________________  |
	|                                                                                  |
	|                        +----------------------------------+                      |
	|                        |         |          	 |          |                      |
	|   +-------------+      |         |             |          |    +-------------+   |
	|   | MENU window |      |         |             |          |    | LOG window  |   |
	|   ---------------      |---------|-------------|----------|    ---------------   |
	|   |             |      |         |             |          |    |             |   |
	|   |             |      |         | BOARD window|          |    |             |   |
	|   |             |      |         |             |          |    |             |   |
	|   |             |      |---------|-------------|----------|    |             |   |
	|   |             |      |         |             |          |    |             |   |
	|   |             |      |         |             |          |    |             |   |
	|   |             |      |         |             |          |    |             |   |
	|   |             |      |---------|-------------|----------|    |             |   |
	|   |             |      |         |             |          |    |             |   |
	|   +-------------+      |         |             |          |    +-------------+   |
	|                        |         |             |          |                      |
	|                        |         |             |          |                      |
	|                        +----------------------------------+                      |
	|                                                                                  |
	|                                                                                  |
    |                  +----------------------------------------------+                |
    |                  |                                              |                |
	|                  |              INFO window                     |                |
	|                  |                                              |                |
	|                  |                                              |                |
	|                  +----------------------------------------------+                |
	|                                                                                  |
	+----------------------------------------------------------------------------------+

*/


/* Get user interface */
void init_interface(void);


/* Draws OBJ object on X,Y
 *
 * OBJ: e = exit, s = station, b = barrier
 *
 * return 1 if succes
 */
int put_object(int x, int y, char obj);


/* Moves robot to X, Y pointing to DIR direction <u,d,r,l>
 * returns 1 if succes
 */
int move_robot(int x, int y, char dir);


/* Writes STRING on log window
 *
 * Returns 1 if susses
 */
int put_log(char* string);


/* Writes info on information window
 * e_lvl: Energy level, g=good, m=medium, b=bad
 * dir: <u,d,r,l>
 * x,y: <0-7>
 *
 * Returns 1 if susses
 */
int put_info(int energy,char e_lvl, int x, int y, char dir);
