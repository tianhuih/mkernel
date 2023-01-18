void kmain(void){
	const char *str = "my first kernel";
	char *vidptr = (char*)0xb8000; 
	unsigned int i = 0; 
	unsigned int j = 0; 

	// clear the screen 
	// size: 80 cols * 25 rows * 2 bytes
	while (j < 80 * 25 * 2){
		// first byte of each element is an ASCII character
		vidptr[j] = ' ';
		// attribute-byte - magenta on black screen 	
		vidptr[j+1] = 0x05;
		j = j + 2; 
	}

	j = 0; 

	// write the str to video memory
	while (str[j] != '\0'){
		vidptr[i] = str[j];
		vidptr[i+1] = 0x05;
		++j;
		i = i + 2;
	}
	return;
}
