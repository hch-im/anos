 /****************************************************
 * util.c
 * 
 * Low-level util functions.
 ***************************************************/

 /*
  *	Copy the specified number of bytes from the source
  * to the destination.
  *
  *		src: the source of memory address to copy
  *		dst: the destion of memory address to copy
  *		bytes: the number of bytes to copy
  *
  *		returns: void
  */
 void mem_copy(char* src, char* dst, int bytes){
 	int i;
 	for(i = 0; i < bytes; i++)
 		dst[i] = src[i];	
 }