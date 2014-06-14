/* file: driver.c
 */

#include "driver.h"

#include <fcntl.h>
#include <termios.h>
#include <stdio.h>

//SERIAL PORT FILE
#define COMPORT "/dev/ttyUSB0"


//Hardware Position
static int h_x,h_y;

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
 * Returns Serial Descriptor, -1 if fail
 */
int serial_init(void)
{
	//Open serial port file
	int fd = open(COMPORT, O_RDWR | O_NOCTTY | O_NDELAY);
	if( fd < 0 ){ return -1; }

	//Configure serial port
	struct termios config;
	if( tcgetattr(fd, &config) != 0 )
	{
		return -1;
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
		return -1;
	}

	//INIT hardware position
	h_x=0;
	h_y=0;

	return fd; 
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


/* Returns 1 if hardware is redy to recive a command */
int wait_hw(int fd)
{
	char a=0;

	while(a != '>')
	{
		read(fd, &a, 1);
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
int step(char axis,char dir,int fd)
{
	int i=0;

	if( axis == 'x' )
	{
		if( dir == 'f' && h_x < X_SIZE)
		{
			for(i=0;i<X_REPEATS;i++)
			{
				wait_hw(fd);
				write(fd, "x:f:0090", 8);
				h_x++;
			}
			return 1;
		}
		else{ return 0; }

		if( dir == 'b' && h_x > 0 )
		{
			for(i=0;i<X_REPEATS;i++)
			{ 
				wait_hw(fd);
				write(fd, "x:b:0090", 8);
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
				wait_hw(fd);
				write(fd, "y:f:0790", 8);
				h_y++;
			}
			return 1;
		}
		else{ return 0; }

		if( dir == 'b' && h_y > 0 )
		{
			for(i=0;i<Y_REPEATS;i++)
			{ 
				wait_hw(fd);
				write(fd, "y:b:0155", 8);
				h_y--;
			}
			return 1;
		}
		else{ return 0; }
	}


	return 1;

}

int main(void)
{

	int fd = serial_init();
	if( fd>0 )
	{
		printf("\npuerto listo\n");
	}
	else
	{
		printf("\npuerto fallo\n");
		return 0;
	}
			
	while(1)
	{
		if( step('y','f',fd) )
		{
			printf("\nSE MOVIO\n");
			printf("\n%d\n", h_y);
		}else{
			printf("\nQUIETO\n");
		}

		//if( step('x','f',fd) )
		//{
		//	printf("\nSE MOVIO\n");
		//	printf("\n%d\n", h_x);
		//}else{
		//	printf("\nQUIETO\n");
		//}
		return 0;
	}

	//if( is_redy(fd) )
	//	printf("\n\n\nREDY TO RECIVE COMMAND\n\n\n");
	//step('x','f',fd);

	return 0;
}
