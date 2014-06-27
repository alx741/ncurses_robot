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

				File: commands.c

*/

#include "commands.h"
#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/* Read commands from FILE and fill COMMAND_QUEUE
 *
 * Returns 0 if fail
 */
int fread_commands(char* FILE_)
{
	char line[100];
	char* command_str;
	char* parameter_str;
	int parameter;

	// Open file
	// int parameter;
	FILE* file = fopen(FILE_, "r"); 
	if( file == NULL ){ return 0; }

	// Read file line by line
	while( fgets(line, 100, file) != NULL )
	{
		// Create new command
		command_t* command = (command_t*) malloc(sizeof(command_t)); 

		/* Validate command */ 
		// Splitt
		command_str = strtok(line, " ");
		
		if( strcmp(command_str, "avanzar\n") == 0 )
		{
			command -> command = C_STEP;
			command -> parameter_int = 0;
		} 
		else if( strcmp(command_str, "girar") == 0 )
		{
			command -> command = C_ROTATE; 

			// Get parameter
			parameter_str = strtok(NULL, " "); 
			if( strcmp(parameter_str, "i\n") == 0 )
			{
				command -> parameter_char = 'i';
			}
			else if( strcmp(parameter_str, "d\n") == 0 )
			{
				command -> parameter_char = 'd';
			}
			else
			{
				return 0;
			} 
		}
		else if( strcmp(command_str, "saltar") == 0 )
		{
			command -> command = C_JUMP; 

			// Get parameter
			parameter_str = strtok(NULL, " "); 
			if( parameter_str == NULL ){ return 0; }
			command -> parameter_int = atoi(parameter_str);
		}
		else if( strcmp(command_str, "teletransportar\n") == 0 )
		{
			command -> command = C_TELEPORT;
			command -> parameter_int = 0;
		} 
		else if( strcmp(command_str, "volver_origen\n") == 0 )
		{
			command -> command = C_ORIGIN;
			command -> parameter_int = 0;
		} 
		else // Bad command
		{
			return 0;
		}
			
		// enqueue the command
		enqueue(COMMANDS_QUEUE, (void*)command); 
	}
	
	return 1;
}

		
//int main()
//{ 
//	COMMANDS_QUEUE = queue_new();
//
//	if( ! fread_commands("test") )
//		printf("READ COMMANDS FAIL!!\n");
//
//	command_t* command = (command_t*) malloc(sizeof(command_t)); 
//
//	do
//	{
//		command = (command_t*) dequeue(COMMANDS_QUEUE);
//		if( command == NULL )
//			printf("NUUUUUUUUUULL command\n");
//		else
//		{
//			printf("comando: %d\n", command -> command);
//			printf("parametro: %c\n", command -> parameter_char);
//		}
//	} 
//	while( command != NULL );
//}