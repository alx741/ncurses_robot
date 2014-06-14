#include <ncurses.h>

/* Create Board window and draws the board on X,Y
 * Height = 25
 * Width = 49
 *
 * returns the WINDOW pointer
 */
WINDOW* get_board_win(int x, int y)
{
	int win_board_height = 25;
	int win_board_width = 49;
	int win_board_y = y;
	int win_board_x = x;

	WINDOW* win_board = newwin(win_board_height, win_board_width, win_board_y, win_board_x);

	//Draw board 
	//wattron(win_board,COLOR_PAIR(7));
	box(win_board, 0, 0);

	//Horizontal lines
	mvwaddch(win_board,3,0,ACS_LTEE); mvwhline(win_board,3,1,ACS_HLINE,47); mvwaddch(win_board,3,48,ACS_RTEE);
	mvwaddch(win_board,6,0,ACS_LTEE); mvwhline(win_board,6,1,ACS_HLINE,47); mvwaddch(win_board,6,48,ACS_RTEE);
	mvwaddch(win_board,9,0,ACS_LTEE); mvwhline(win_board,9,1,ACS_HLINE,47); mvwaddch(win_board,9,48,ACS_RTEE);
	mvwaddch(win_board,12,0,ACS_LTEE); mvwhline(win_board,12,1,ACS_HLINE,47); mvwaddch(win_board,12,48,ACS_RTEE);
	mvwaddch(win_board,15,0,ACS_LTEE); mvwhline(win_board,15,1,ACS_HLINE,47); mvwaddch(win_board,15,48,ACS_RTEE);
	mvwaddch(win_board,18,0,ACS_LTEE); mvwhline(win_board,18,1,ACS_HLINE,47); mvwaddch(win_board,18,48,ACS_RTEE);
	mvwaddch(win_board,21,0,ACS_LTEE); mvwhline(win_board,21,1,ACS_HLINE,47); mvwaddch(win_board,21,48,ACS_RTEE);

	//Vertical lines
	mvwaddch(win_board,0,6,ACS_TTEE); mvwvline(win_board,1,6,ACS_VLINE,23); mvwaddch(win_board,24,6,ACS_BTEE);
	mvwaddch(win_board,0,12,ACS_TTEE); mvwvline(win_board,1,12,ACS_VLINE,23); mvwaddch(win_board,24,12,ACS_BTEE);
	mvwaddch(win_board,0,18,ACS_TTEE); mvwvline(win_board,1,18,ACS_VLINE,23); mvwaddch(win_board,24,18,ACS_BTEE);
	mvwaddch(win_board,0,24,ACS_TTEE); mvwvline(win_board,1,24,ACS_VLINE,23); mvwaddch(win_board,24,24,ACS_BTEE);
	mvwaddch(win_board,0,30,ACS_TTEE); mvwvline(win_board,1,30,ACS_VLINE,23); mvwaddch(win_board,24,30,ACS_BTEE);
	mvwaddch(win_board,0,36,ACS_TTEE); mvwvline(win_board,1,36,ACS_VLINE,23); mvwaddch(win_board,24,36,ACS_BTEE);
	mvwaddch(win_board,0,42,ACS_TTEE); mvwvline(win_board,1,42,ACS_VLINE,23); mvwaddch(win_board,24,42,ACS_BTEE);

	//Intersections
	int x_,y_;
	for(y_=3;y_<=21;y_+=3)
	{
		for(x_=6;x_<=42;x_+=6)
		{
			mvwaddch(win_board,y_,x_,ACS_PLUS);
		}
	}


	//wattroff(win_board,COLOR_PAIR(7));
	wrefresh(win_board);

	return win_board;
}



/* Gets X,Y standard coordinate and converts it to ncurses position coordinate
 *
 * Standard:
 *   +---------------------+
 *   |      |      |       |
 *   |---------------------|
 *   |      |      |       |
 *   |---------------------|
 *   |  0,0 |      |       |
 *   +---------------------+
 *
 * Ncurses:
 *   +---------------------+
 *   | 0,0  |      |       |
 *   |---------------------|
 *   |      |      |       |
 *   |---------------------|
 *   |      |      |       |
 *   +---------------------+
 *
 * returns 1 if succes
 */
int convert_coordinate(int* x, int* y)
{
	if( *x<0 || *x>7 || *y<0 || *y>7 ){ return 0; }

	*x = ( *x * 5 ) + *x + 1;
	*y = ( (7-*y) * 2 ) + (7-*y) + 1;

	return 1;
}



/* Draws OBJ object on X,Y
 *
 * OBJ: e = exit, s = station, b = barrier
 *
 * return 1 if succes
 */
int put_object(WINDOW* window, int x, int y, char obj)
{
	if( !convert_coordinate(&x, &y) ){ return 0; }

	if( obj == 'e' )
	{
		wattron(window, COLOR_PAIR(3));
		mvwaddstr(window, y, x, ">EXIT");
		mvwaddstr(window, (y+1), x, "#####" );
		wattroff(window, COLOR_PAIR(3));
	}
	else if( obj == 's' )
	{
		wattron(window, COLOR_PAIR(2));
		mvwaddstr(window, y, x, "*GAS*");
		mvwaddstr(window, (y+1), x, "-----" );
		wattroff(window, COLOR_PAIR(2));
	}
	else if( obj == 'b' )
	{
		wattron(window, COLOR_PAIR(1));
		mvwaddstr(window, y, x, "|---|");
		mvwaddstr(window, (y+1), x, "|---|" );
		wattroff(window, COLOR_PAIR(1));
	}

	wrefresh(window);
	return 1; 
}


/* Moves robot to X, Y pointing to DIR direction <u,d,r,l>
 * returns 1 if succes
 */
int move_robot(WINDOW* window, int x, int y, char dir)
{
	static int actual_x=0;
	static int actual_y=0;
	int i=0;

	if( x<0 || x>7 || y<0 || y>7 || (dir!='u' && dir!='d' && dir!='r' && dir!='l') ){ return 0; }

	/* ###### Clean robot ###### */
	int x_char = actual_x;
	int y_char = actual_y;

	convert_coordinate(&x_char, &y_char);

	mvwaddstr(window, y_char, x_char, "     ");
	mvwaddstr(window, (y_char+1), x_char, "     ");


	/* ###### Draw robot ##### */
	
	//Update acutal position
	actual_x = x;
	actual_y = y;	

	convert_coordinate(&x, &y);

	if( dir == 'u' )
	{
		wattron(window, COLOR_PAIR(4));
		mvwaddstr(window, y, x, " ^-^ ");
		mvwaddstr(window, y+1, x, " --- ");
		wattroff(window, COLOR_PAIR(4));
	}
	else if (dir == 'd' )
	{
		wattron(window, COLOR_PAIR(4));
		mvwaddstr(window, y, x, " --- ");
		mvwaddstr(window, y+1, x, " v-v ");
		wattroff(window, COLOR_PAIR(4));
	}
	else if (dir == 'r' )
	{
		wattron(window, COLOR_PAIR(4));
		mvwaddstr(window, y, x, " |-> ");
		mvwaddstr(window, y+1, x, " |-> ");
		wattroff(window, COLOR_PAIR(4));
	}
	else if (dir == 'l' )
	{
		wattron(window, COLOR_PAIR(4));
		mvwaddstr(window, y, x, " <-| ");
		mvwaddstr(window, y+1, x, " <-| ");
		wattroff(window, COLOR_PAIR(4));
	}


	// Refresh window
	wrefresh(window);

	return 1;
}


/* Create Info window and draws it on X,Y
 * Height = 25
 * Width = 49
 *
 * returns the WINDOW pointer
 */
WINDOW* get_info_win(int x, int y)
{
	int win_info_height = 7;
	int win_info_width = 40;
	int win_info_y = y;
	int win_info_x = x;

	WINDOW* win_info = newwin(win_info_height, win_info_width, win_info_y, win_info_x);

	//Draw board 
	box(win_info, 0, 0);

	wattron(win_info, A_BOLD);
	mvwaddstr(win_info, 2, 2, "Carga: ");
	mvwaddstr(win_info, 4, 2, "Posición: ");
	wattroff(win_info, A_BOLD);

	mvwaddch(win_info, 3, 30, ACS_LARROW);
	mvwaddch(win_info, 3, 34, ACS_RARROW);
	mvwaddch(win_info, 2, 32, ACS_UARROW);
	mvwaddch(win_info, 4, 32, ACS_DARROW);

	wrefresh(win_info);

	return win_info;
}

	





int main(void)
{

	//CURSES INIT
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	start_color();

	init_pair(1, COLOR_RED, COLOR_BLACK); //Barriers
	init_pair(2, COLOR_GREEN, COLOR_BLACK); //Stations
	init_pair(3, COLOR_BLACK, COLOR_GREEN); //Exit
	init_pair(4, COLOR_BLUE, COLOR_BLACK); //Robot
	init_pair(5, COLOR_CYAN, COLOR_BLACK);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(7, COLOR_BLACK, COLOR_WHITE);


	refresh();


	WINDOW* win_board = get_board_win(50, 1);
	WINDOW* win_info = get_info_win(0, LINES-7);

	move_robot(win_board,0,0,'r');
	getch();
	move_robot(win_board,1,2,'u');
	getch();
	move_robot(win_board,5,5,'d');
	getch();


	put_object(win_board, 4, 2, 'b');
	put_object(win_board, 3, 6, 'e');
	put_object(win_board, 1, 3, 's');

	getch();

	endwin();

	return 0;
}
