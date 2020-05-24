//Source file for HiLetGo 1602 LCD Module
#include "lcd1602.h"

struct lcd {
	unsigned char select;	//High - data input, Low - instruction input
	unsigned char rw;	//High - read, Low - write
	unsigned char enable;
	//Data bits 0-7
	//Maybe separate into high and low nibbles
	unsigned char data;
}

struct lcd * lcd_init(unsigned int select, unsigned int rw,
		     unsigned int enable, unsigned int data){

	struct lcd * lcd;
	lcd->select = select;
	lcd->enable = enable;
	lcd->rw = rw;
	lcd->data = data;

}

void lcd_clearDisplay(struct lcd * lcd){
	lcd->select = 0u;
	lcd->rw = 0u;	
	lcd->data = 1u;
}

void lcd_returnHome(struct lcd * lcd){
	lcd->select = 0u;
	lcd->rw = 0u;
	lcd->data = 1u << 1;
}

//cursor/blink moves right if direction is high, left if low
//entire display is shifted if shift is high, else it is not shifted
void lcd_entryModeSet(struct lcd * lcd,
		      unsigned int direction,
		      unsigned int shift){
	
	lcd->select = 0u;
	lcd->rw = 0u;
	lcd->data = (1u << 2) | (direction << 1) | (shift);
}

//turns on display, cursor, blink
void lcd_setDisplay(struct lcd * lcd,
		    unsigned int display,
		    unsigned int cursor,
		    unsigned int blink){
	
	lcd->select = 0u;
	lcd->rw = 0u;
	lcd->data = (1u << 3) | (display << 2) | (cursor << 1) | blink;
}

//type is high for display shift, low for cursor
//direction is high for right shift
void lcd_shift(struct lcd * lcd,
	       unsigned int direction,
	       unsigned int type){
	
	lcd->select = 0u;
	lcd->rw = 0u;
	lcd->data = (1u << 4) | (type << 3) | (direction << 2);
}

//dl -> high for 8-bit bus mode, low for 4-bit
//n  -> high for 2-line mode, low for 1-line
//f  -> high for 5x11 dots format, low for 5x8 dots format
void lcd_functionSet(struct lcd * lcd,
		     unsigned int dl,
		     unsigned int n,
		     unsigned int f){
	
	lcd->select = 0u;
	lcd->rw = 0u;
	lcd->data = (1u << 5) | (dl << 4) | (n << 3) | (f << 2);
}

//sets CGRAM address to ac
void lcd_setCGRAM(struct lcd * lcd, unsigned int ac){
	//ac must be contained to 6 bits
	if(ac < 64u){	
		lcd->select = 0u;
		lcd->rw = 0u;
		lcd->data = (1u << 6) | ac;
	}

}	

//sets DDRAM address to acd
void lcd_setDDRAM(struct lcd * lcd, unsigned int ac){
	//ac must be contained to 7 bits
	if(ac < 128u){
		lcd->select = 0u;
		lcd->rw = 0u;
		lcd->data = (1u << 7) | ac;
	}

}

//waits for device to finish current instruction
void lcd_wait(struct lcd * lcd){
	
	lcd->select = 0u;
	lcd->rw = 1u;
	while(!(((lcd->data) >> 7) & 1));
}

//write data to CGRAM or DDRAM
void lcd_writeData(struct lcd * lcd, unsigned int data){
	
	lcd->select = 1u;
	lcd->rw = 0u;
	lcd->data = data;

}

//read data from CGRAM or DDRAM
unsigned int lcd_readData(struct lcd * lcd){
	
	lcd->select = 1u;
	lcd->rw = 1u;
	return lcd->data;

}

























