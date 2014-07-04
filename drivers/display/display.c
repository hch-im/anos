/****************************************************
 * display.c
 * 
 * Display driver.
 ***************************************************/
 #include "display.h"
 unsigned char text_color = DEFAULT_COLOUR_SCHEMA;

 void print_char(char ch, int row, int col){
 	unsigned char* vm = (unsigned char*)VIDEO_ADDRESS;
 
 	//get the memory offset to write the char.
 	int offset = get_screen_offset(row, col);
 	if(offset == -1){
 		offset = get_cursor();
 	}
 	switch(ch){
 		case '\n':
	 		//row may be changed to the row of cursor
 			row = offset / (MAX_COLS * 2);
 			//scroll screen
 			offset = get_screen_offset(row, MAX_COLS - 1); 		
 			break;
 		default:
			vm[offset] = ch;
			vm[offset + 1] = text_color; 		
			break;
 	}

 	offset += 2;	//move offset to the next cell
 	offset = handle_scroll(offset);	//scroll if required
 	set_cursor(offset);		//update the location of cursor			
 }

 int get_screen_offset(int row, int col){
 	if(row < 0 || row >= MAX_ROWS || 
 		col < 0 || col >= MAX_COLS)
 		return -1;
 	else
		return (row * MAX_COLS + col) * 2;
 }

 int get_cursor(){
 	//select the internal register 14 and 15 of display
 	//to read the high byte and low byte of the cursor 
 	//offset.
 	int offset;
 	write_port_byte(DISPLAY_CTRL_PORT, CURSOR_HIGH_BYTE);
 	offset = read_port_byte(DISPLAY_DATA_PORT) << 8;
 	write_port_byte(DISPLAY_CTRL_PORT, CURSOR_LOW_BYTE);
 	offset += read_port_byte(DISPLAY_DATA_PORT); 	

 	return offset * 2;
 }

 void set_cursor(int offset){
 	offset /= 2;
 	//select the internal register 14 and 15 of display
 	//to write the high byte and low byte of the new 
 	//cursor offset.
 	write_port_byte(DISPLAY_CTRL_PORT, CURSOR_LOW_BYTE);
 	write_port_byte(DISPLAY_DATA_PORT, (unsigned char)offset);
 	write_port_byte(DISPLAY_CTRL_PORT, CURSOR_HIGH_BYTE);
 	write_port_byte(DISPLAY_DATA_PORT, (unsigned char)(offset >> 8));
 }

 void print(char* str, int row, int col){
 	//if row and col are valid, set the cursor else start from 
 	//the current location of the cursor to print
 	int offset = get_screen_offset(row, col);
 	if(offset != -1)
 		set_cursor(offset);

 	char * ptr = str;
 	while(*ptr != 0)
 		print_char(*ptr++, -1, -1);
 }

 void puts(char* str){
 	print(str, -1, -1);
 }

 void clear_screen(){
 	unsigned char* vm = (unsigned char*)VIDEO_ADDRESS; 	
 	int i, max = MAX_COLS * MAX_ROWS * 2;
 	for(i = 0; i < max; i += 2){
 		vm[i] = ' ';
 		vm[i + 1] = DEFAULT_COLOUR_SCHEMA;
 	}
 	//move cursor to top left
 	set_cursor(0);
 } 

 int handle_scroll(int offset){
 	int i;
 	if(offset < MAX_ROWS * MAX_COLS * 2)
 		return offset;
 	unsigned char* vm = (unsigned char*)VIDEO_ADDRESS;
 	//move rows
 	mem_copy(vm + get_screen_offset(1, 0), vm, 
 				(MAX_ROWS - 1) * MAX_COLS * 2);
 	//clear last line
 	offset = get_screen_offset(MAX_ROWS - 1, 0);
 	for(i = 0; i < MAX_COLS; i++)
 		vm[offset + i * 2] = 0;

 	return offset;
 }

 void set_text_color(unsigned char attr){
 	text_color = attr;
 }