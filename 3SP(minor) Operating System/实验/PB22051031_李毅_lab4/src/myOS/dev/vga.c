//=========================simple output===========================================
#define VGA_BASE 0xb8000
#define ROWS 24   // row25 is for system
#define COLS 80

// with BRIGHT bit = 0
#define BLACK   0x0
#define BLUE    0x1
#define GREEN   0x2
#define CYAN    0x3
#define RED     0x4
#define MAGENTA 0x5
#define BROWN   0x6
#define LGRAY   0x7

// with BRIGHT bit = 1
#define BRIGHT  0x8
#define DGRAY   BRIGHT & BLACK
#define LBLUE   BRIGHT & BLUE
#define LGREEN  BRIGHT & GREEN
#define LCYAN   BRIGHT & CYAN
#define LRED    BRIGHT & RED
#define PINK    BRIGHT & MAGENTA
#define YELLOW  BRIGHT & BROWN
#define WHITE   BRIGHT & LGRAY

#define BLINK   0x80

#include "../include/io.h"

static void move_cursor(unsigned int _row, unsigned int _col){
    unsigned int cursorLocation = _row * 80 + _col;

    outb(0x3D4, 14); // select cursor location high register                   
    outb(0x3D5, cursorLocation >> 8);   
    outb(0x3D4, 15); // select cursor location low register                    
    outb(0x3D5, cursorLocation & 0xff);        
}

unsigned char * vgaPtr(int _row, int _col){
    unsigned char * ptr = (unsigned char *)VGA_BASE;
    return ptr + _row * COLS * 2 + _col *2;
}

void put_char(char c, char color, int _row, int _col) {
	unsigned char *ptr = vgaPtr(_row,_col);

	*ptr++ = c; 
    *ptr   = color;	
}

int put_chars(char *msg, char color, int _row, int _col){
	char c, *ptr=msg;		
    int n=0;
	
	c = *ptr;
	while (c!='\0'){
        n++;
	    if ( _col==80 ) {	_col = 0;	_row ++;	}
	    if ( _row==25 ) _row = 0;

	    put_char(c, color, _row, _col++);	 

	    c = *(++ptr);  //next char
	}
	return n;
}

void clear_char(int _row, int _col) {
	unsigned char *ptr = vgaPtr(_row,_col);

	*ptr++ = 0; 
    *ptr   = 0x7;	
}

void clearLastRow(void){
    int _col;
    for(_col=0; _col<COLS; _col++) clear_char(ROWS-1, _col);
}

void scrollOneRow(void){        
    int i;
    unsigned char * ptr = (unsigned char *)VGA_BASE;
    unsigned char * nextRowPtr = vgaPtr(1,0);

    for (i=0; i< (ROWS-1) * COLS; i++) {
        *ptr++ = *nextRowPtr++;
        *ptr++ = *nextRowPtr++;
    }
    clearLastRow();        
}

void clear_screen(void) {	
	unsigned char *ptr = (unsigned char *)VGA_BASE;  
    unsigned int _col,_row;  
	for(_row=0; _row< ROWS; _row++) {
	    for (_col=0; _col<COLS; _col++) {
            (*ptr++) = 0;  //first char
            (*ptr++) = 0x7;  //second char
	    }
	}    
    move_cursor(0,0);
    return;
}

void append2screen(char *str,int color){ 
    char c, *current =str ; 
    unsigned int cursorLocation;
    int row, col;
    outb(0x3D4, 14); cursorLocation = inb(0x3D5) << 8;
    outb(0x3D4, 15); cursorLocation |= inb(0x3D5);

    row = cursorLocation / 80;
    col = cursorLocation % 80;

    while(c = *current++) {
        if (c !='\n') {
            put_char(c,color,row,col++);              
        } else { // for '\n'            
            col = 0; row ++; 
        }        
        // what if col and row too big                
        if (col >= COLS) { col = 0; row++; }
        if (row >= ROWS) {            
            scrollOneRow(); 
            row = ROWS-1;
        }        
    } 
    move_cursor(row, col); 
}