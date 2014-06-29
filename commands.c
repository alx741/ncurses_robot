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



/* Read commands from FILE_NAME and fill COMMAND_QUEUE
 *
 * Returns 0 if fail
 */
int fread_commands(char* file_name)
{
	char line[100];
	char* command_str;
	char* parameter_str;
	int parameter;

	// Open file
	// int parameter;
	FILE* file = fopen(file_name, "r"); 
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
	
	fclose(file); 
	return 1;
}



/* Writes LOG line to FILE_NAME
 *
 * Returns 0 if fail
 */
int fwrite_log(char* file_name, char* log)
{
	// Open file
	FILE* file = fopen(file_name, "a"); 
	if( file == NULL ){ return 0; }

	fputs(log, file);

	fclose(file); 
	return 1;
}
