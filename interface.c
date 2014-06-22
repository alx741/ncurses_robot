#include <ncurses.h>
#include <menu.h>
#include <form.h>
#include <panel.h>
#include <string.h>
#include <stdlib.h>

/* Global window pointers */
WINDOW* WIN_BOARD=0;
WINDOW* WIN_INFO=0;
WINDOW* WIN_HELP=0;
WINDOW* WIN_LOG=0;
WINDOW* WIN_MENU=0;
MENU* MEN_MENU=0;

/* ################################################ */
/*                     BOARD                        */
/* ################################################ */

/* Create Board window and draws the board on X,Y
 * Height = 25
 * Width = 49
 *
 * Fills WIN_BOARD
 * Returns 1 if susses
 */
int get_board_win(int x, int y)
{
	int win_board_height = 25;
	int win_board_width = 49;
	int win_board_y = y;
	int win_board_x = x;

	if( WIN_BOARD != 0 ){ return 0; }

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

	WIN_BOARD = win_board;
	return 1;
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
int put_object(int x, int y, char obj)
{
	if( !convert_coordinate(&x, &y) ){ return 0; }
	if( WIN_BOARD == 0 ){ return 0; }

	if( obj == 'e' )
	{
		wattron(WIN_BOARD, COLOR_PAIR(3));
		mvwaddstr(WIN_BOARD, y, x, ">EXIT");
		mvwaddstr(WIN_BOARD, (y+1), x, "=====" );
		wattroff(WIN_BOARD, COLOR_PAIR(3));
	}
	else if( obj == 's' )
	{
		wattron(WIN_BOARD, COLOR_PAIR(2));
		mvwaddstr(WIN_BOARD, y, x, "-|*|-");
		mvwaddstr(WIN_BOARD, (y+1), x, "-|*|-" );
		wattroff(WIN_BOARD, COLOR_PAIR(2));
	}
	else if( obj == 'b' )
	{
		wattron(WIN_BOARD, COLOR_PAIR(1));
		mvwaddstr(WIN_BOARD, y, x, "|\\:/|");
		mvwaddstr(WIN_BOARD, (y+1), x, "|\\:/|" );
		wattroff(WIN_BOARD, COLOR_PAIR(1));
	}

	wrefresh(WIN_BOARD);
	return 1; 
}


/* Moves robot to X, Y pointing to DIR direction <u,d,r,l>
 * returns 1 if succes
 */
int move_robot(int x, int y, char dir)
{
	static int actual_x=0;
	static int actual_y=0;
	int i=0;

	if( x<0 || x>7 || y<0 || y>7 || (dir!='u' && dir!='d' && dir!='r' && dir!='l') ){ return 0; }
	if( WIN_BOARD == 0 ){ return 0; }

	/* ###### Clean robot ###### */
	int x_char = actual_x;
	int y_char = actual_y;

	convert_coordinate(&x_char, &y_char);

	mvwaddstr(WIN_BOARD, y_char, x_char, "     ");
	mvwaddstr(WIN_BOARD, (y_char+1), x_char, "     ");


	/* ###### Draw robot ##### */
	
	//Update acutal position
	actual_x = x;
	actual_y = y;	

	convert_coordinate(&x, &y);

	if( dir == 'u' )
	{
		wattron(WIN_BOARD, COLOR_PAIR(4));
		mvwaddstr(WIN_BOARD, y, x, "  |  ");
		mvwaddstr(WIN_BOARD, y+1, x, "(vvv)");
		wattroff(WIN_BOARD, COLOR_PAIR(4));
	}
	else if (dir == 'd' )
	{
		wattron(WIN_BOARD, COLOR_PAIR(4));
		mvwaddstr(WIN_BOARD, y, x, "(^^^)");
		mvwaddstr(WIN_BOARD, y+1, x, "  |  ");
		wattroff(WIN_BOARD, COLOR_PAIR(4));
	}
	else if (dir == 'r' )
	{
		wattron(WIN_BOARD, COLOR_PAIR(4));
		mvwaddstr(WIN_BOARD, y, x, " ##_ ");
		mvwaddstr(WIN_BOARD, y+1, x, " ##  ");
		wattroff(WIN_BOARD, COLOR_PAIR(4));
	}
	else if (dir == 'l' )
	{
		wattron(WIN_BOARD, COLOR_PAIR(4));
		mvwaddstr(WIN_BOARD, y, x, " _## ");
		mvwaddstr(WIN_BOARD, y+1, x, "  ## ");
		wattroff(WIN_BOARD, COLOR_PAIR(4));
	}


	// Refresh window
	wrefresh(WIN_BOARD);

	return 1;
}


/* ################################################ */
/*                     HELP                         */
/* ################################################ */

/* Create Help window and draws it on the top of the screen
 *
 * Fills WIN_HELP pointer
 * returns 1 if susses
 */
int get_help_win()
{
	int win_help_height = 2;
	int win_help_width = COLS;
	int win_help_y = 0;
	int win_help_x = 0;

	if( WIN_HELP != 0 ){ return 0; }

	WINDOW* win_help = newwin(win_help_height, win_help_width, win_help_y, win_help_x);

	mvwprintw(win_help, 0, 0, "Girar: Teclas de direccion IZQ, DER  ||  Avanzar: Barra espaciadora  ||  Salir: q");
	mvwhline(win_help, 1, 0, ACS_HLINE, win_help_width);

	wrefresh(win_help);

	WIN_HELP = win_help;
	return 1;
}



/* ################################################ */
/*                     LOG                          */
/* ################################################ */


/* Create Info window and draws it on X,Y
 * Height = LINES-4
 * Width = 30
 *
 * Fills WIN_INFO pointer
 * returns 1 if susses
 */
int get_log_win(int x, int y)
{
	int win_log_height = LINES-4;
	int win_log_width = 30;
	int win_log_y = y;
	int win_log_x = x;

	if( WIN_LOG != 0 ){ return 0; }

	WINDOW* win_log = newwin(win_log_height, win_log_width, win_log_y, win_log_x);

	//Draw
	box(win_log, 0, 0);

	//Header
	wattron(win_log, A_BOLD);
	mvwprintw(win_log, 1, (win_log_width-3)/2, "LOG");
	wattroff(win_log, A_BOLD);
	mvwaddch(win_log, 2, 0, ACS_LTEE); whline(win_log, ACS_HLINE, win_log_width-2); mvwaddch(win_log, 2, win_log_width-1, ACS_RTEE);



	wrefresh(win_log);

	WIN_LOG = win_log;
	return 1;
}


/* Writes STRING on log window
 *
 * Returns 1 if susses
 */
int put_log(char* string)
{

	if( WIN_LOG == 0 ){ return 0; }
	
	static int index=4;

	if( index == (LINES-4)-2 )
		index=4;

	
	wattron(WIN_LOG, COLOR_PAIR(6));
	mvwprintw(WIN_LOG, index, 4, string);
	wattroff(WIN_LOG, COLOR_PAIR(6));

	wrefresh(WIN_LOG);
	index++;

	return 1;
}



/* ################################################ */
/*                     INFO                         */
/* ################################################ */

/* Create Info window and draws it on X,Y
 * Height = 25
 * Width = 49
 *
 * Fills WIN_INFO pointer
 * returns 1 if susses
 */
int get_info_win(int x, int y)
{
	int win_info_height = 7;
	int win_info_width = 40;
	int win_info_y = y;
	int win_info_x = x;

	if( WIN_INFO != 0 ){ return 0; }

	WINDOW* win_info = newwin(win_info_height, win_info_width, win_info_y, win_info_x);

	//Draw
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

	WIN_INFO = win_info;
	return 1;
}


/* Writes info on information window
 * e_lvl: Energy level, g=good, m=medium, b=bad
 * dir: <u,d,r,l>
 * x,y: <0-7>
 *
 * Returns 1 if susses
 */
int put_info(int energy,char e_lvl, int x, int y, char dir)
{

	if( WIN_INFO == 0 ){ return 0; }

	int color_index=0;

	if( e_lvl == 'g' )
		color_index = 2;
	if( e_lvl == 'm' )
		color_index = 5;
	if( e_lvl == 'b' )
		color_index = 1;

	wattron(WIN_INFO, COLOR_PAIR(color_index));
	mvwprintw(WIN_INFO, 2, 9, "%d [kb]", energy);
	wattroff(WIN_INFO, COLOR_PAIR(color_index));

	mvwprintw(WIN_INFO, 4, 12, "X:%d / Y:%d", x, y);

	if( dir == 'u' )
	{
		wattron(WIN_INFO, A_REVERSE);
		mvwaddch(WIN_INFO, 2, 32, ACS_UARROW);
		wattroff(WIN_INFO, A_REVERSE);
	}
	else if( dir == 'd' )
	{
		wattron(WIN_INFO, A_REVERSE);
		mvwaddch(WIN_INFO, 4, 32, ACS_DARROW);
		wattroff(WIN_INFO, A_REVERSE);
	}
	else if( dir == 'l' )
	{
		wattron(WIN_INFO, A_REVERSE);
		mvwaddch(WIN_INFO, 3, 30, ACS_LARROW);
		wattroff(WIN_INFO, A_REVERSE);
	}
	else if( dir == 'r' )
	{
		wattron(WIN_INFO, A_REVERSE);
		mvwaddch(WIN_INFO, 3, 34, ACS_RARROW);
		wattroff(WIN_INFO, A_REVERSE);
	}

	wrefresh(WIN_INFO);
	return 1;
}



/* ################################################ */
/*                     MENU                         */
/* ################################################ */


/* Takes OPTION string from menu
 *
 * Calls respective menu option panels
 * TODO: replace "mvprintw" -> panels creation functions
 */
void menu_handler(char* option)
{
	if( strcmp(option, "Nuevo Juego")==0 )
	{
		get_newgame_form();
	}
	else if( strcmp(option, "Saltar")==0 )
	{
		mvprintw(0,0,option);
	}
	else if( strcmp(option, "Teletransportar")==0 )
	{
		mvprintw(0,0,option);
	}
	else if( strcmp(option, "Ir al origen")==0 )
	{
		mvprintw(0,0,option);
	}
	else if( strcmp(option, "Cargar Instrucciones")==0 )
	{
		mvprintw(0,0,option);
	}
}


/* Create Menu window and draws it on X,Y
 * Height = 15
 * Width = 30
 *
 * Fills WIN_MENU and MEN_MENU pointers
 * returns 1 if susses
 */
int get_menu_win(int x, int y)
{
	int win_menu_height = 15;
	int win_menu_width = 30;
	int win_menu_y = y;
	int win_menu_x = x;
	int n_options,i;

	if( WIN_MENU != 0 || MEN_MENU !=0 ){ return 0; }

	char* options[] = { 
				"Nuevo Juego",
				"Saltar",
				"Teletransportar",
				"Ir al origen",
				"Cargar Instrucciones",
				(char*) NULL,
			};
	n_options = sizeof(options) / sizeof(options[0]);

	WINDOW* win_menu = newwin(win_menu_height, win_menu_width, win_menu_y, win_menu_x);
	keypad(win_menu, TRUE);
	
	ITEM** items = (ITEM**)calloc(n_options, sizeof(ITEM*));

	for(i=0;i<n_options;i++)
	{
		items[i] = new_item(options[i], "");
		set_item_userptr(items[i], menu_handler);
	}

	MENU* menu = new_menu((ITEM**)items);

	set_menu_win(menu, win_menu);
	set_menu_sub(menu, derwin(win_menu, 10, 28, 4, 1));
	set_menu_mark(menu, " > ");

	//Draw
	box(win_menu, 0, 0);

	wattron(win_menu, A_BOLD);
	mvwprintw(win_menu, 1, (win_menu_width-3)/2, "MENU");
	wattroff(win_menu, A_BOLD);
	mvwaddch(win_menu, 2, 0, ACS_LTEE); whline(win_menu, ACS_HLINE, win_menu_width-2); mvwaddch(win_menu, 2, win_menu_width-1, ACS_RTEE);

	post_menu(menu);

	MEN_MENU = menu;
	WIN_MENU = win_menu;
	wrefresh(win_menu);
	return 1;
}

/* ////////////////   MENU OPTION FORMS  \\\\\\\\\\\\\\\ */

/* Create -new game- panel form
 * at center of the screen
 *
 * returns 1 if susses
 */
int get_newgame_form()
{
	int win_menu_newgame_height = 12;
	int win_menu_newgame_width = 40;
	int win_menu_newgame_y =  5;
	int win_menu_newgame_x = (COLS-40)/2;

	WINDOW* win_menu_newgame = newwin(win_menu_newgame_height, win_menu_newgame_width, win_menu_newgame_y, win_menu_newgame_x);
	keypad(win_menu_newgame, TRUE);
	PANEL* pan_menu_newgame = new_panel(win_menu_newgame);



	/*   -----  CREATE FORM ----- */
	// Fields config
	FIELD* fields_menu_newgame[4];
	fields_menu_newgame[0] = new_field(1,10,1,1,0,0);
	fields_menu_newgame[1] = new_field(1,10,4,1,0,0);
	fields_menu_newgame[2] = new_field(1,10,6,1,0,0);
	fields_menu_newgame[3] = NULL;

	set_field_back(fields_menu_newgame[0], A_UNDERLINE);
	field_opts_on(fields_menu_newgame[0], O_EDIT);
	field_opts_off(fields_menu_newgame[0], O_AUTOSKIP);
	set_field_type(fields_menu_newgame[0], TYPE_INTEGER, 0, 1, 30); // Validate: Number, 1-30

	set_field_back(fields_menu_newgame[1], A_UNDERLINE);
	field_opts_on(fields_menu_newgame[1], O_EDIT);
	field_opts_off(fields_menu_newgame[1], O_AUTOSKIP);
	set_field_type(fields_menu_newgame[1], TYPE_INTEGER, 0, 3, 8); // Validate: Number, 3-8

	set_field_back(fields_menu_newgame[2], A_UNDERLINE);
	field_opts_on(fields_menu_newgame[2], O_EDIT);
	field_opts_off(fields_menu_newgame[2], O_AUTOSKIP);
	set_field_type(fields_menu_newgame[2], TYPE_INTEGER, 0, 3, 8); // Validate: Number, 3-8

	// Create FORM
	FORM* form_menu_newgame = new_form(fields_menu_newgame);
	set_form_win(form_menu_newgame, win_menu_newgame);
	set_form_sub(form_menu_newgame, derwin(win_menu_newgame, 8, 15, 1, 24));



	/*   -----  CREATE MENU ----- */ 

	char* options[] = { 
				"Aceptar",
				"Cancelar",
				(char*) NULL,
			};
	int n_options = sizeof(options) / sizeof(options[0]);
	int i;

	ITEM** items = (ITEM**)calloc(n_options, sizeof(ITEM*));

	for(i=0;i<n_options;i++)
	{
		items[i] = new_item(options[i], "");
		set_item_userptr(items[i], menu_handler);
	}

	MENU* menu = new_menu((ITEM**)items);

	set_menu_win(menu, win_menu_newgame);
	set_menu_sub(menu, derwin(win_menu_newgame, 1, 30, 9, 8));
	set_menu_format(menu, 1, 2);
	set_menu_mark(menu, " ");

	
	
	/*   -----  DRAW ----- */ 
	
	// Frame
	wattron(win_menu_newgame, COLOR_PAIR(8) | A_BOLD);
	box(win_menu_newgame, 0, 0);
	mvwprintw(win_menu_newgame, 0, 8, " Nuevo Juego ");
	wattroff(win_menu_newgame, COLOR_PAIR(8) | A_BOLD);

	// Field labels
	mvwprintw(win_menu_newgame, 2, 2, "Numero de Barreras: ");
	mvwprintw(win_menu_newgame, 5, 2, "Salida [X] <3-8> : ");
	mvwprintw(win_menu_newgame, 7, 2, "Salida [Y] <3-8> : ");

	// Post form, menu
	post_form(form_menu_newgame);
	post_menu(menu); 
	update_panels();
	doupdate();
	wrefresh(win_menu_newgame);



	/*   -----  HANDLE ----- */ 

	int c;

	while(1)
	{
		c = wgetch(win_menu_newgame);

		if( c == KEY_DOWN )
		{
			form_driver(form_menu_newgame, REQ_NEXT_FIELD);
		}
		else if( c == KEY_UP )
		{
			form_driver(form_menu_newgame, REQ_PREV_FIELD);
		}
		else if( c == KEY_LEFT )
		{
			menu_driver(menu, REQ_LEFT_ITEM);
		}
		else if( c == KEY_RIGHT )
		{
			menu_driver(menu, REQ_RIGHT_ITEM);
		}
		else if( c == 127 ) // Back Space
		{
			form_driver(form_menu_newgame, REQ_CLR_FIELD);
		}
		else if( c == 10 ) // Enter
		{
			if( strcmp( item_name(current_item(menu)), "Cancelar") == 0 ) // "Cancelar" option handling
			{
				/*    //  Wipe form and return  \\ */

				// Wipe menu
				unpost_menu(menu);
				for(i=0; i<n_options; i++)
				{
					free_item(items[i]);
				}
				free_menu(menu);

				// Wipe form 
				unpost_form(form_menu_newgame);
				free_form(form_menu_newgame);
				free_field(fields_menu_newgame[0]);
				free_field(fields_menu_newgame[1]);
				free_field(fields_menu_newgame[2]);
				free_field(fields_menu_newgame[3]);

				// Wipe panel
				del_panel(pan_menu_newgame);

				// Wipe window
				delwin(win_menu_newgame);

				// Refresh 
				wrefresh(WIN_BOARD);
				refresh();
				touchwin(WIN_BOARD);

				return 1;
			}
			else 		// "Aceptar" option handlig
			{
				// End fields filling
				form_driver(form_menu_newgame, REQ_NEXT_FIELD); 
				
				// Get values from fields
				int value1 = atoi(field_buffer(fields_menu_newgame[0], 0));
				int value2 = atoi(field_buffer(fields_menu_newgame[1], 0));
				int value3 = atoi(field_buffer(fields_menu_newgame[2], 0));

				// Validate
				if( (value1 > 0 && value1 < 31) && (value2 > 2 && value2 < 9) && (value3 > 2 && value3 < 9) )
				{
					// TODO: new_game no implemented yet
					//new_game(value1, value2, value3);
				} 
			}
		}
		else  // Filling fields
		{
			form_driver(form_menu_newgame, c);
		}
	}


	unpost_form(form_menu_newgame);
	hide_panel(pan_menu_newgame);
	update_panels();
	doupdate();
	wrefresh(win_menu_newgame);
	delwin(win_menu_newgame);
	wrefresh(WIN_BOARD);
	refresh();
	touchwin(WIN_BOARD);
	return 1;
}












/* Curses init
 * color pairs declarations
 * windows load
 */
void init_interface(void)
{
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	start_color();

	init_pair(1, COLOR_RED, COLOR_BLACK); //Barriers, Energy level bad
	init_pair(2, COLOR_GREEN, COLOR_BLACK); //Stations, Energy level good
	init_pair(3, COLOR_BLACK, COLOR_GREEN); //Exit
	init_pair(4, COLOR_CYAN, COLOR_BLACK); //Robot
	init_pair(5, COLOR_YELLOW, COLOR_BLACK); //Energy level medium
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK); //Log
	init_pair(7, COLOR_BLACK, COLOR_WHITE);
	init_pair(8, COLOR_WHITE, COLOR_BLUE); //Forms title

	refresh();


	get_board_win((COLS-49)/2, 3);
	get_info_win((COLS-40)/2, LINES-7);
	put_info(40,'b', 5, 7, 'l');
	get_help_win();
	get_log_win((COLS-30)-5, 3);

	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("hola1");
	put_log("jajaja");
	put_log("jajaja");
	put_log("jajaja");
	put_log("jajaja");
	put_log("jajaja");
	put_log("jajaja");
	put_log("jajaja");
	put_log("jajaja");
	put_log("jajaja");
	put_log("jajaja");
	put_log("jajaja");
	put_log("jajaja");
	put_log("jajaja");
	put_log("jajaja");
	put_log("jajaja");
	put_log("jajaja");
	put_log("jajaja");
	put_log("jajaja");
	put_log("jajaja");



	get_menu_win(5, (LINES-15)/2);
}

	





int main(void)
{

	init_interface();


	move_robot(0,0,'r');
	getch();
	move_robot(1,2,'u');
	getch();
	move_robot(5,5,'d');
	getch();
	put_object( 4, 2, 'b');
	put_object( 3, 6, 'e');
	put_object( 1, 3, 's');



	int c=0;
	while( (c = getch()) != KEY_F(1))
	{
		if( c == KEY_DOWN )
		{
			menu_driver(MEN_MENU, REQ_DOWN_ITEM);
		}
		if( c == KEY_UP )
		{
			menu_driver(MEN_MENU, REQ_UP_ITEM);
		}
		if( c == 10 ) // ENTER
		{
			ITEM* cur;
			void (*p)(char*);

			cur = current_item(MEN_MENU);
			p = item_userptr(cur);
			p( (char*) item_name(cur) );

		}
		if( c == KEY_LEFT )
		{
			move_robot(6,6,'l');
		}
		wrefresh(WIN_MENU);
		wrefresh(WIN_BOARD);
	}



	endwin();

	return 0;
}
