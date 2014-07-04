/****************************************************
 * port_io.c
 * 
 * Low-level port I/O functions.
 ***************************************************/
 
/*
 *	Read a byte from the specified port.
 *
 *		port: the port of the device.
 *		
 *		returns: the byte read from the port.
 */
unsigned char read_port_byte(unsigned short port){
	unsigned char data;
	//read a byte to al from the port number in dx.
	//dx maps to port; al maps to data
	__asm__("in al, dx"	
			: "=a" (data)
			: "d" (port)
			);
	return data;
}

/*
 *	Write a byte to the specified port.
 *
 *		port: the port of the device.
 *		data: the data to write.
 *
 *		returns: void
 */
void write_port_byte(unsigned short port, unsigned char data){
	//write a byte in al to the specified port number in dx.
	__asm__("out dx, al"	
			: "=d" (port)
			: "a" (data)
			);
}

/*
 *	Read a word from the specified port.
 *
 *		port: the port of the device.
 *		
 *		returns: the word read from the port.
 */
unsigned short read_port_word(unsigned short port){
	unsigned short data;
	//read a word to ax from the port number in dx.
	//dx maps to port; ax maps to data
	__asm__("in ax, dx"	
			: "=a" (data)
			: "d" (port)
			);
	return data;
}

/*
 *	Write a word to the specified port.
 *
 *		port: the port of the device.
 *		data: the data to write.
 *
 *		returns: void
 */
void write_port_word(unsigned short port, unsigned short data){
	//write a word in ax to the specified port number in dx.
	__asm__("out dx, ax"	
			: "=d" (port)
			: "a" (data)
			);
}