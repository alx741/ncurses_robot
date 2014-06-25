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

				File: game.c

*/


/* Objects definitiosn */
#define EMPTY 	0x00 // Empty Board box
#define UROBOT 	0x01 // Up pointing Robot
#define DROBOT 	0x02 // Down pointing Robot
#define RROBOT 	0x03 // Right pointing Robot
#define LROBOT 	0x04 // Left pointing Robot
#define BARRIER 0x05 // Barrier
#define STATION 0x06 // Charge Station
#define EXIT 	0x07 // Exit

/* Game definitions */
#define INIT_ENERGY 10 // Robot Energy
#define ENERGY_STATIONS 2 // Energy stations charge
#define GOOD 'g' // Good Energy level
#define MEDIUM 'm' // Medium Energy level
#define BAD 'b' // Bad Energy level
#define UP 'u' 	// Ponting directions
#define DOWN 'd'
#define RIGHT 'r'
#define LEFT 'l'


/* BOARD MATRIX */
char BOARD[8][8];

/* Global status */
int ENERGY; // Robot energy
int ENERGY_STAT; // Robot energy level status (good, medium, bad)
int X, Y; // Robot position
char DIRECTION; // Robot direction


/* Empty BOARD boxes */
void init_board()
{
	int i,j;

	for(i=0; i<8; i++)
	{
		for(j=0; j<8; j++)
		{
			BOARD[i][j] = EMPTY;
		}
	}
}


/* Empty the BOARD, fills it and draw with game elements
 *
 * Put Robot at 0,0
 * Put N_BARRIERS barriers randomly
 * Put [1, ( (N_BARRIERS*10)/100 )] charge stations randomly
 * Put the exit at (EXIT_X, EXIT_Y)
 */
void new_game(int n_barriers, int exit_x, int exit_y)
{
	int rand_x, rand_y;
	int barriers_allocated=0;
	int stations_allocated=0;
	int n_stations;

	// Adjust EXIT coordinates to [0-7]
	exit_x--;
	exit_y--;
	
	// Empty the BOARD and blank it
	init_board();
	blank_board();

	/* Put Robot, always start at 0,0 ponting to the rigth */
	BOARD[0][0] = RROBOT;
	X = 0;
	Y = 0;
	DIRECTION = RIGHT;
	draw_robot(0,0,RIGHT);
  
	/* Put Exit */
	BOARD[exit_x][exit_y] = EXIT;
	draw_object(exit_x, exit_y, 'e');

	/* Restart energy, refresh INFO window and inform in LOG window */
	ENERGY = INIT_ENERGY;
	ENERGY_STAT = GOOD;
	draw_info(ENERGY,'g', 0, 0, RIGHT);
	draw_log("*** NEW GAME ***");


	/* Put Barriers */
	while( barriers_allocated != n_barriers )
	{
		rand_x = (rand()%8);
		rand_y = (rand()%8);
		
		// Barrires can't jail the robot
		if( !((rand_x==1 && rand_y==0) || (rand_x==0 && rand_y==1)) )
		{

			if( BOARD[rand_x][rand_y] == EMPTY )
			{
				BOARD[rand_x][rand_y] = BARRIER;
				draw_object(rand_x, rand_y, 'b');

				barriers_allocated++;
			}
		}
	}



	/* Put Charge Stations */
	n_stations = (n_barriers*40)/100;
	if( n_stations < 0)
		n_stations = 1;

	while( stations_allocated != n_stations )
	{
		rand_x = (rand()%8);
		rand_y = (rand()%8);

		if( BOARD[rand_x][rand_y] == EMPTY )
		{
			BOARD[rand_x][rand_y] = STATION;
			draw_object(rand_x, rand_y, 's');

			stations_allocated++;
		}
	}
}

	
/* Rotates the robot in DIR direction
 *
 *
 * LOGS the movement
 */
void rotate_robot(char dir)
{
	if( dir == RIGHT )
	{
		draw_log("--Girar Derecha");
		if( DIRECTION == UP )
		{
			draw_robot(X, Y, RIGHT);
			draw_info(ENERGY,ENERGY_STAT, X, Y, RIGHT);
			DIRECTION = RIGHT;
		}
		else if( DIRECTION == DOWN )
		{
			draw_robot(X, Y, LEFT);
			draw_info(ENERGY,ENERGY_STAT, X, Y, LEFT);
			DIRECTION = LEFT;
		}
		else if( DIRECTION == LEFT )
		{
			draw_robot(X, Y, UP);
			draw_info(ENERGY,ENERGY_STAT, X, Y, UP);
			DIRECTION = UP;
		}
		else if( DIRECTION == RIGHT )
		{
			draw_robot(X, Y, DOWN);
			draw_info(ENERGY,ENERGY_STAT, X, Y, DOWN);
			DIRECTION = DOWN;
		}
	}
	else if( dir == LEFT )
	{
		draw_log("--Girar Izquierda");
		if( DIRECTION == UP )
		{
			draw_robot(X, Y, LEFT);
			draw_info(ENERGY,ENERGY_STAT, X, Y, LEFT);
			DIRECTION = LEFT;
		}
		else if( DIRECTION == DOWN )
		{
			draw_robot(X, Y, RIGHT);
			draw_info(ENERGY,ENERGY_STAT, X, Y, RIGHT);
			DIRECTION = RIGHT;
		}
		else if( DIRECTION == LEFT )
		{
			draw_robot(X, Y, DOWN);
			draw_info(ENERGY,ENERGY_STAT, X, Y, DOWN);
			DIRECTION = DOWN;
		}
		else if( DIRECTION == RIGHT )
		{
			draw_robot(X, Y, UP);
			draw_info(ENERGY,ENERGY_STAT, X, Y, UP);
			DIRECTION = UP;
		}
	}
}
	




/* Moves the robot 1 step
 *
 * If possible return 1, else return 0
 *
 * LOGS the movement
 * Charge robot energy when arrives a charge station
 * Invokes WIN and NEW GAME routines whe robot arrive the exit
 */
int move_robot()
{
	static int is_station_below=0;

	// UP step
	if( DIRECTION == UP && Y<7 )
	{
		// Barrier found
		if( BOARD[X][Y+1] == BARRIER )
		{
			return 0;
		}
		
		// Charge station found
		else if( BOARD[X][Y+1] == STATION )
		{
			draw_robot(X, Y+1, UP);
			BOARD[X][Y] = EMPTY;
			if( is_station_below )
			{
				BOARD[X][Y] = STATION;
				draw_object(X, Y, 's');
				is_station_below=0;
			}
			Y++;
			BOARD[X][Y] = UROBOT;
			ENERGY+=ENERGY_STATIONS;
			draw_log("-| Cargando |-");
			if(ENERGY>=INIT_ENERGY)
			{
				ENERGY_STAT = GOOD;
			}
			else if(ENERGY>=(INIT_ENERGY)/2)
			{
				ENERGY_STAT = MEDIUM;
			}
			else
			{
				ENERGY_STAT = BAD;
			}

			is_station_below=1;
			draw_info(ENERGY,ENERGY_STAT, X, Y, UP);
			draw_log("--Avanzar");
			return 1;
		}
		// Exit found
		else if( BOARD[X][Y+1] == EXIT )
		{
			draw_log("--Avanzar");
			draw_log("*** PARTIDA GANADA ***");
			//TODO:  WIN ROUTINE
			return 1;
		}
		// Empty box found
		else if( BOARD[X][Y+1] == EMPTY )
		{
			draw_robot(X, Y+1, UP);
			BOARD[X][Y] = EMPTY;
			if( is_station_below )
			{
				BOARD[X][Y] = STATION;
				draw_object(X, Y, 's');
				is_station_below=0;
			}
			Y++;
			BOARD[X][Y] = UROBOT;
			ENERGY--;
			if(ENERGY>=INIT_ENERGY)
			{
				ENERGY_STAT = GOOD;
			}
			else if(ENERGY>=(INIT_ENERGY)/2)
			{
				ENERGY_STAT = MEDIUM;
			}
			else if( ENERGY > 0 )
			{
				ENERGY_STAT = BAD;
			}
			else
			{
				draw_log("--Avanzar");
				//TODO: LOST ROUTINE
				return 1;
			}

			draw_info(ENERGY,ENERGY_STAT, X, Y, UP);
			draw_log("--Avanzar");
			return 1;
		}

		return 0;
	}
			


	// DOWN step
	else if( DIRECTION == DOWN && Y>0 )
	{
		// Barrier found
		if( BOARD[X][Y-1] == BARRIER )
		{
			return 0;
		}
		
		// Charge station found
		else if( BOARD[X][Y-1] == STATION )
		{
			draw_robot(X, Y-1, DOWN);
			BOARD[X][Y] = EMPTY;
			if( is_station_below )
			{
				BOARD[X][Y] = STATION;
				draw_object(X, Y, 's');
				is_station_below=0;
			}
			Y--;
			BOARD[X][Y] = DROBOT;
			ENERGY+=ENERGY_STATIONS;
			draw_log("-| Cargando |-");
			if(ENERGY>=INIT_ENERGY)
			{
				ENERGY_STAT = GOOD;
			}
			else if(ENERGY>=(INIT_ENERGY)/2)
			{
				ENERGY_STAT = MEDIUM;
			}
			else
			{
				ENERGY_STAT = BAD;
			}

			is_station_below=1;
			draw_info(ENERGY,ENERGY_STAT, X, Y, DOWN);
			draw_log("--Avanzar");
			return 1;
		}
		// Exit found
		else if( BOARD[X][Y-1] == EXIT )
		{
			draw_log("--Avanzar");
			draw_log("*** PARTIDA GANADA ***");
			//TODO:  WIN ROUTINE
			return 1;
		}
		// Empty box found
		else if( BOARD[X][Y-1] == EMPTY )
		{
			draw_robot(X, Y-1, DOWN);
			BOARD[X][Y] = EMPTY;
			if( is_station_below )
			{
				BOARD[X][Y] = STATION;
				draw_object(X, Y, 's');
				is_station_below=0;
			}
			Y--;
			BOARD[X][Y] = DROBOT;
			ENERGY--;
			if(ENERGY>=INIT_ENERGY)
			{
				ENERGY_STAT = GOOD;
			}
			else if(ENERGY>=(INIT_ENERGY)/2)
			{
				ENERGY_STAT = MEDIUM;
			}
			else if( ENERGY > 0 )
			{
				ENERGY_STAT = BAD;
			}
			else
			{
				draw_log("--Avanzar");
				//TODO: LOST ROUTINE
				return 1;
			}

			draw_info(ENERGY,ENERGY_STAT, X, Y, DOWN);
			draw_log("--Avanzar");
			return 1;
		}

		return 0;
	}


	
	// RIGHT step
	else if( DIRECTION == RIGHT && X<7 )
	{
		// Barrier found
		if( BOARD[X+1][Y] == BARRIER )
		{
			return 0;
		}
		
		// Charge station found
		else if( BOARD[X+1][Y] == STATION )
		{
			draw_robot(X+1, Y, RIGHT);
			BOARD[X][Y] = EMPTY;
			if( is_station_below )
			{
				BOARD[X][Y] = STATION;
				draw_object(X, Y, 's');
				is_station_below=0;
			}
			X++;
			BOARD[X][Y] = RROBOT;
			ENERGY+=ENERGY_STATIONS;
			draw_log("-| Cargando |-");
			if(ENERGY>=INIT_ENERGY)
			{
				ENERGY_STAT = GOOD;
			}
			else if(ENERGY>=(INIT_ENERGY)/2)
			{
				ENERGY_STAT = MEDIUM;
			}
			else
			{
				ENERGY_STAT = BAD;
			}

			is_station_below=1;
			draw_info(ENERGY,ENERGY_STAT, X, Y, RIGHT);
			draw_log("--Avanzar");
			return 1;
		}
		// Exit found
		else if( BOARD[X+1][Y] == EXIT )
		{
			draw_log("--Avanzar");
			draw_log("*** PARTIDA GANADA ***");
			//TODO:  WIN ROUTINE
			return 1;
		}
		// Empty box found
		else if( BOARD[X+1][Y] == EMPTY )
		{
			draw_robot(X+1, Y, RIGHT);
			BOARD[X][Y] = EMPTY;
			if( is_station_below )
			{
				BOARD[X][Y] = STATION;
				draw_object(X, Y, 's');
				is_station_below=0;
			}
			X++;
			BOARD[X][Y] = RROBOT;
			ENERGY--;
			if(ENERGY>=INIT_ENERGY)
			{
				ENERGY_STAT = GOOD;
			}
			else if(ENERGY>=(INIT_ENERGY)/2)
			{
				ENERGY_STAT = MEDIUM;
			}
			else if( ENERGY > 0 )
			{
				ENERGY_STAT = BAD;
			}
			else
			{
				draw_log("--Avanzar");
				//TODO: LOST ROUTINE
				return 1;
			}

			draw_info(ENERGY,ENERGY_STAT, X, Y, RIGHT);
			draw_log("--Avanzar");
			return 1;
		}

		return 0;
	}



	// LEFT step
	else if( DIRECTION == LEFT && X>0 )
	{
		// Barrier found
		if( BOARD[X-1][Y] == BARRIER )
		{
			return 0;
		}
		
		// Charge station found
		else if( BOARD[X-1][Y] == STATION )
		{
			draw_robot(X-1, Y, LEFT);
			BOARD[X][Y] = EMPTY;
			if( is_station_below )
			{
				BOARD[X][Y] = STATION;
				draw_object(X, Y, 's');
				is_station_below=0;
			}
			X--;
			BOARD[X][Y] = LROBOT;
			ENERGY+=ENERGY_STATIONS;
			draw_log("-| Cargando |-");
			if(ENERGY>=INIT_ENERGY)
			{
				ENERGY_STAT = GOOD;
			}
			else if(ENERGY>=(INIT_ENERGY)/2)
			{
				ENERGY_STAT = MEDIUM;
			}
			else
			{
				ENERGY_STAT = BAD;
			}

			is_station_below=1;
			draw_info(ENERGY,ENERGY_STAT, X, Y, LEFT);
			draw_log("--Avanzar");
			return 1;
		}
		// Exit found
		else if( BOARD[X-1][Y] == EXIT )
		{
			draw_log("--Avanzar");
			draw_log("*** PARTIDA GANADA ***");
			//TODO:  WIN ROUTINE
			return 1;
		}
		// Empty box found
		else if( BOARD[X-1][Y] == EMPTY )
		{
			draw_robot(X-1, Y, LEFT);
			BOARD[X][Y] = EMPTY;
			if( is_station_below )
			{
				BOARD[X][Y] = STATION;
				draw_object(X, Y, 's');
				is_station_below=0;
			}
			X--;
			BOARD[X][Y] = LROBOT;
			ENERGY--;
			if(ENERGY>=INIT_ENERGY)
			{
				ENERGY_STAT = GOOD;
			}
			else if(ENERGY>=(INIT_ENERGY)/2)
			{
				ENERGY_STAT = MEDIUM;
			}
			else if( ENERGY > 0 )
			{
				ENERGY_STAT = BAD;
			}
			else
			{
				draw_log("--Avanzar");
				//TODO: LOST ROUTINE
				return 1;
			}

			draw_info(ENERGY,ENERGY_STAT, X, Y, LEFT);
			draw_log("--Avanzar");
			return 1;
		}

		return 0;
	}
}


	
