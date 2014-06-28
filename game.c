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

#include "queue.h"
#include "commands.h"

#include <stdio.h>
#include <stdlib.h>

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


/* Boolean, is a game running or not */
char GAME_RUNING;

/* BOARD MATRIX */
char BOARD[8][8];

/* Global status */
int ENERGY; // Robot energy
int ENERGY_STAT; // Robot energy level status (good, medium, bad)
int X, Y; // Robot position
char DIRECTION; // Robot direction
static int is_station_below=0; // When Robot is above a station

/* Reset all game global variables and values */
void reset_game_values()
{
	int i,j;

	// Reset BOARD
	for(i=0; i<8; i++)
	{
		for(j=0; j<8; j++)
		{
			BOARD[i][j] = EMPTY;
		}
	}
	
	// Reset ENERGY
	ENERGY = INIT_ENERGY;
	ENERGY_STAT = GOOD;
	
	// Reset ROBOT position and direction
	X = 0;
	Y = 0;
	DIRECTION = RIGHT;

	// Blank the board
	blank_board(); 
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
	reset_game_values();

	/* Put Robot, always start at 0,0 ponting to the rigth */
	BOARD[0][0] = RROBOT;
	draw_robot(0,0,DIRECTION);
  
	/* Put Exit */
	BOARD[exit_x][exit_y] = EXIT;
	draw_object(exit_x, exit_y, 'e');

	/* Restart energy, refresh INFO window and inform in LOG window */
	draw_info(ENERGY,'g', 0, 0, DIRECTION);
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

	// Enable runing game
	GAME_RUNING=1;
}

	
/* Rotates the robot in DIR direction
 *
 *
 * LOGS the movement
 */
void rotate_robot(char dir)
{

	if( !GAME_RUNING ){ return; }

	if( dir == RIGHT )
	{
		draw_log("--Girar Derecha         ");
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
		draw_log("--Girar Izquierda        ");
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
	if( !GAME_RUNING ){ return 0; }

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
			draw_log("-| Cargando |-        ");
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
			draw_log("--Avanzar        ");
			return 1;
		}
		// Exit found
		else if( BOARD[X][Y+1] == EXIT )
		{
			draw_log("--Avanzar        ");
			draw_log("*** PARTIDA GANADA ***");
			// Show WIN pop-up
			get_winpopup(); 
			// Reset game
			reset_game_values();
			// Stop game
			GAME_RUNING=0;

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
				draw_log("--Avanzar        ");
				draw_log("### PARTIDA PERDIDA ###");
				// Show LOSE pop-up
				get_losepopup();
				// Reset game
				reset_game_values();
				// Stop game
				GAME_RUNING=0;
				return 1;
			}

			draw_info(ENERGY,ENERGY_STAT, X, Y, UP);
			draw_log("--Avanzar        ");
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
			draw_log("-| Cargando |-        ");
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
			draw_log("--Avanzar        ");
			return 1;
		}
		// Exit found
		else if( BOARD[X][Y-1] == EXIT )
		{
			draw_log("--Avanzar        ");
			draw_log("*** PARTIDA GANADA ***");
			// Show WIN pop-up
			get_winpopup(); 
			// Reset game
			reset_game_values();
			// Stop game
			GAME_RUNING=0;
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
				draw_log("--Avanzar        ");
				draw_log("### PARTIDA PERDIDA ###");
				// Show LOSE pop-up
				get_losepopup();
				// Reset game
				reset_game_values();
				// Stop game
				GAME_RUNING=0;
				return 1;
			}

			draw_info(ENERGY,ENERGY_STAT, X, Y, DOWN);
			draw_log("--Avanzar        ");
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
			draw_log("-| Cargando |-        ");
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
			draw_log("--Avanzar        ");
			return 1;
		}
		// Exit found
		else if( BOARD[X+1][Y] == EXIT )
		{
			draw_log("--Avanzar        ");
			draw_log("*** PARTIDA GANADA ***");
			// Show WIN pop-up
			get_winpopup(); 
			// Reset game
			reset_game_values();
			// Stop game
			GAME_RUNING=0;
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
				draw_log("--Avanzar        ");
				draw_log("### PARTIDA PERDIDA ###");
				// Show LOSE pop-up
				get_losepopup();
				// Reset game
				reset_game_values();
				// Stop game
				GAME_RUNING=0;
				return 1;
			}

			draw_info(ENERGY,ENERGY_STAT, X, Y, RIGHT);
			draw_log("--Avanzar        ");
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
			draw_log("-| Cargando |-        ");
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
			draw_log("--Avanzar        ");
			return 1;
		}
		// Exit found
		else if( BOARD[X-1][Y] == EXIT )
		{
			draw_log("--Avanzar        ");
			draw_log("*** PARTIDA GANADA ***");
			// Show WIN pop-up
			get_winpopup(); 
			// Reset game
			reset_game_values();
			// Stop game
			GAME_RUNING=0;
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
				draw_log("--Avanzar        ");
				draw_log("### PARTIDA PERDIDA ###");
				// Show LOSE pop-up
				get_losepopup();
				// Reset game
				reset_game_values();
				// Stop game
				GAME_RUNING=0;
				return 1;
			}

			draw_info(ENERGY,ENERGY_STAT, X, Y, LEFT);
			draw_log("--Avanzar        ");
			return 1;
		}

		return 0;
	}
}


	
/* Interchange robot coordinates
 *
 * If possible return 1, else return 0
 *
 * LOGS the movement
 * Charge robot energy when arrives a charge station
 * Invokes WIN and NEW GAME routines whe robot arrive the exit
 */
int teleport_robot()
{
	if( !GAME_RUNING ){ return 0; }

	int new_x, new_y; 

	// Interchange coordinates
	new_x = Y;
	new_y = X;


	if( BOARD[new_x][new_y] == BARRIER )
	{
		draw_log("[!] Imposible [!]     ");
		return 0;
	}
	
	// Charge station found
	else if( BOARD[new_x][new_y] == STATION )
	{
		draw_log("[!] Imposible [!]     ");
		return 0;
	}
	// Exit found
	else if( BOARD[new_x][new_y] == EXIT )
	{
		draw_log("[!] Imposible [!]     ");
		return 0;
	}
	// Empty box found
	else if( BOARD[new_x][new_y] == EMPTY )
	{
		draw_robot(new_x, new_y, DIRECTION);
		BOARD[X][Y] = EMPTY;
		if( is_station_below )
		{
			BOARD[X][Y] = STATION;
			draw_object(X, Y, 's');
			is_station_below=0;
		}
		X = new_x;
		Y = new_y;
		if( DIRECTION == UP)
		{
			BOARD[X][Y] = UROBOT;
		}
		else if( DIRECTION == DOWN)
		{
			BOARD[X][Y] = DROBOT;
		}
		else if( DIRECTION == RIGHT)
		{
			BOARD[X][Y] = RROBOT;
		}
		else if( DIRECTION == LEFT)
		{
			BOARD[X][Y] = LROBOT;
		}
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
			draw_log("--Teletransportar       ");
			draw_log("### PARTIDA PERDIDA ###");
			// Show LOSE pop-up
			get_losepopup();
			// Reset game
			reset_game_values();
			// Stop game
			GAME_RUNING=0;
			return 1;
		}

		draw_info(ENERGY,ENERGY_STAT, X, Y, DIRECTION);
		draw_log("--Teletransportar      ");
		return 1;
	}
}

/* Puts robot in (0,0)
 *
 *
 * LOGS the movement
 */
void move_robot_origin()
{
	draw_info(ENERGY,ENERGY_STAT, 0, 0, DIRECTION);
	draw_log("--Ir al origen      ");

	draw_robot(0, 0, DIRECTION);
	BOARD[X][Y] = EMPTY;
	if( is_station_below )
	{
		BOARD[X][Y] = STATION;
		draw_object(X, Y, 's');
		is_station_below=0;
	}
	X=0;
	Y=0;
	if( DIRECTION == UP)
	{
		BOARD[X][Y] = UROBOT;
	}
	else if( DIRECTION == DOWN)
	{
		BOARD[X][Y] = DROBOT;
	}
	else if( DIRECTION == RIGHT)
	{
		BOARD[X][Y] = RROBOT;
	}
	else if( DIRECTION == LEFT)
	{
		BOARD[X][Y] = LROBOT;
	}
}

	
/* Reads and execute robot commands from FILE
 *
 * return 0 if fail
 */
int execute_from_file(char* file)
{
	int i;
	
	// Init COMMANDS_QUEUE
	COMMANDS_QUEUE = queue_new();

	if( ! fread_commands(file) ){ return 0; }
	
	command_t* command = (command_t*) malloc(sizeof(command_t)); 
	command = (command_t*) dequeue(COMMANDS_QUEUE);

	while( command != NULL )
	{ 
		if( command -> command == C_STEP )
		{
			move_robot();
		}
		else if( command -> command == C_ROTATE )
		{
			if( command -> parameter_char == 'r' )
			{
				rotate_robot(RIGHT);
			}
			else
			{
				rotate_robot(LEFT);
			}
		}
		else if( command -> command == C_JUMP )
		{
			for(i=0; i < (command -> parameter_int); i++)
			{
				move_robot();
			}
		}
		else if( command -> command == C_TELEPORT )
		{
			teleport_robot();
		}
		else if( command -> command == C_ORIGIN )
		{
			move_robot_origin();
		}

		command = (command_t*) dequeue(COMMANDS_QUEUE);
	} 
}
