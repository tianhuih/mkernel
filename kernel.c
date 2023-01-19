/* define screen size: 80 cols * 25 rows * 2 bytes */
#define LINES 25
#define COLUMNS 80
#define BYTES_FOR_EACH_ELEMENT 2
#define SCREENSIZE LINES * COLUMNS * BYTES_FOR_EACH_ELEMENT

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8e
#define KERNEL_CODE_SEGMENT_OFFSET 0x08

#define ENTRY_KEY_CODE 0x1c

/* current cursor location */
unsigned int curr_loc = 0;
/* video memory starts at 0xb8000 */
char *vidptr = (char*)0xb8000; 

/* interrupt descriptor table */
struct IDT_entry {
	unsigned short int offset_lowerbits; 
	unsigned short int offset_higher bits;
	unsigned short int selector; 
	unsigned char zero; 
	unsigned char type_attr; 
}

struct IDT_entry IDT[IDT_SIZE]; 

void idt_init(void) {
	unsigned long keyboard_address; 
	unsigned long idt_address; 
	unsigned long idt_ptr[2];

	/* populate IDT entry of keyboard's interrupt */
	keyboard_address = (unsigned long)keyboard_handler; 
	IDT[0x21].offset_lowerbits = keyboard_address & 0xffff; 
	IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET; 
	IDT[0x21].zero = 0; 
	IDT[0x21].type_attr = INTERRUPT_GATE; 
	IDT[0x21].offset_higherbits = (keyboard_address & oxffff0000) >> 16; 

}

void kmain(void){
	const char *str = "my first kernel"; 
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
