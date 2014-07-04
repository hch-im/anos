/****************************************************
 * port_io.c
 ***************************************************/
#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

//colour schemes
#define DEFAULT_COLOUR_SCHEMA 0x0f //white on black

//display I/O ports
#define DISPLAY_CTRL_PORT 0x03d4
#define DISPLAY_DATA_PORT 0x03d5

//cursor 
#define CURSOR_LOW_BYTE 0x0f
#define CURSOR_HIGH_BYTE 0x0e 

/*
 *	Print a char on the with the specified attribute
 *	at the specified location. If attr == 0, it will 
 *	use the default color style (white on black). If
 *	either col or row is not within the correct range
 *	, the location of cursor will be used to print the
 *	char.
 *	
 *		ch: the char to print
 *		attr: the print style
 *		row: the row of screen to print	 
 *		col: the column of screen to print
 *
 *		returns: void
 */
void print_char(char ch, int row, int col);

/*
 *	Calculate the memory offset from the specified row and
 *	col.
 *
 *		row: the row of screen to print	 
 *		col: the column of screen to print
 *
 *		returns: 
 *			-1, if either row or col is a value 
 *			the offset of video memory to print a char
 */
int get_screen_offset(int row, int col);

/*
 *	Get the offset of cursor from the start of video
 *	memory address.
 *
 *		returns: the offset
 */
int get_cursor(); 

/*
 *	Set the location of cursor.
 *
 *		offset: the offset 
 *
 *		returns: void
 */
void set_cursor(int offset); 

/*
 *	Print the string from the specified location
 *
 *		str: the string to print.
 *		row: the start row of screen to print	 
 *		col: the start column of screen to print
 *
 *		returns: void
 */
void print(char* str, int row, int col);
void puts(char* str);

/*
 *	Clear the screen.
 */
void clear_screen(); 

/*
 *	Scroll the screen if required.
 *	
 *		offset: the offset of the cursor.
 *
 *		returns: the new offset of the cursor
 */
int handle_scroll(int offset);

/*
 *	Set the style of the text.
 *	
 *		attr: the tyle.
 *
 *		returns: void
 */
void set_text_color(unsigned char attr);

#endif