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

				File: driver.c

*/

#include "driver.h"

#include <fcntl.h>
#include <termios.h>
#include <stdio.h>

//Hardware Position
static int h_x,h_y;

// COM PORT file descriptor
int COM_FD;


/* Configure serial port with
 *
 * 9600 baud
 * 8 bit data
 * No parity
 * Non blocking reading
 * Special lines ignore
 * No control Terminal
 * Read enable
 * RAW input/output
 *
 * Puts Serial Descriptor in COM_FD, 0 if fail
 */
int serial_init(void)
{
	//Open serial port file
	int fd = open(COMPORT, O_RDWR | O_NOCTTY | O_NDELAY);
	if( fd < 0 ){ COM_FD = -1; return 0; }

	//Configure serial port
	struct termios config;
	if( tcgetattr(fd, &config) != 0 )
	{
		COM_FD = -1;
		return 0;
	}

	cfsetispeed(&config, B9600);
	cfsetospeed(&config, B9600);

	config.c_cflag |= (CLOCAL | CREAD | CS8);
	config.c_cflag &= ~(PARENB | PARODD);
	config.c_iflag = 0;
	config.c_oflag = 0;
	config.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	config.c_cc[VTIME] = 5;
	config.c_cc[VMIN] = 0;

	if( tcsetattr(fd, TCSANOW, &config) != 0 )
	{
		COM_FD = -1;
		return 0;
	}

	//INIT hardware position
	h_x=0;
	h_y=0;

	COM_FD = fd;
	return 1; 
}



/*Puts actual position in X,Y
 *
 * Returns 0 if fail
 */
int getxy(int* x, int* y)
{
	*x=h_x;
	*y=h_y;
	return 1;
}


/* Returns 1 if hardware is redy to recive a command 
 * 
 * Its a blocking function, returns only when hardware is ready
 * */
int wait_hw(void)
{
	char a=0;

	if( COM_FD < 0 ){ return 0; }

	while(a != '>')
	{
		read(COM_FD, &a, 1);
	}
	a=0;
	return 1;
}

	

/* Moves hardware in AXIS with direccion DIR
 * AXIS = <x,y>
 * DIR = <f,b>
 * 
 * Returns 0 if is not possible to move
 */
int step(char axis,char dir)
{
	int i=0;

	if( COM_FD < 0 ){ return 0; }

	if( axis == 'x' )
	{
		if( dir == 'f' && h_x < X_SIZE)
		{
			for(i=0;i<X_REPEATS;i++)
			{
				wait_hw();
				write(COM_FD, "x:f:0090", 8);
				h_x++;
			}
			return 1;
		}
		else{ return 0; }

		if( dir == 'b' && h_x > 0 )
		{
			for(i=0;i<X_REPEATS;i++)
			{ 
				wait_hw();
				write(COM_FD, "x:b:0090", 8);
				h_x--;
			}
			return 1;
		}
		else{ return 0; }
	}


	if( axis == 'y' )
	{
		if( dir == 'f' && h_y < Y_SIZE)
		{
			for(i=0;i<Y_REPEATS;i++)
			{
				wait_hw();
				write(COM_FD, "y:f:0790", 8);
				h_y++;
			}
			return 1;
		}
		else{ return 0; }

		if( dir == 'b' && h_y > 0 )
		{
			for(i=0;i<Y_REPEATS;i++)
			{ 
				wait_hw();
				write(COM_FD, "y:b:0155", 8);
				h_y--;
			}
			return 1;
		}
		else{ return 0; }
	}


	return 1;

}
