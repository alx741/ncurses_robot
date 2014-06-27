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

				File: commands.h

*/

#include "queue.h"


#ifndef COMMANDS_H
#define COMMANDS_H


/* COMMANDS */
#define C_STEP 0x00
#define C_JUMP 0x01
#define C_ROTATE 0x02
#define C_TELEPORT 0x03
#define C_ORIGIN 0x04


// Command type
typedef struct command_t
{
	char command;
	union
	{
		int parameter_int;
		char parameter_char;
	};
}command_t;


// Commands Queue
queue_t* COMMANDS_QUEUE;


#endif
