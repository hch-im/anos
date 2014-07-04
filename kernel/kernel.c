/****************************************************
 * kernel.c
 * 
 * The kernel of the operating system.
 ***************************************************/

void main(){
	clear_screen();
	int i;
	for(i = 'a'; i <= 'y'; i++){
		set_text_color((unsigned char)i);		
		print_char(i, -1, -1);
		puts("test \n");
	}
}
