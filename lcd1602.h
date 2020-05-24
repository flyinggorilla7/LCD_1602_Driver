//Header file for HiLetGo 1602 LCD Module


void lcd_clearDisplay(struct lcd * lcd);

void lcd_returnHome(struct lcd * lcd);

void lcd_entryModeSet(struct lcd * lcd,
		      unsigned int direction,
		      unsigned int shift);

void lcd_setDisplay(struct lcd * lcd,
		    unsigned int display,
		    unsigned int cursor,
		    unsigned int blink);

void lcd_shift(struct lcd * lcd,
	       unsigned int direction,
	       unsigned int type);

void lcd_functionSet(struct lcd * lcd,
		     unsigned int dl,
		     unsigned int n,
		     unsigned int f);

void lcd_setCGRAM(struct lcd * lcd, unsigned int ac);

void lcd_setDDRAM(struct lcd * lcd, unsigned int ac);

void lcd_wait(struct lcd * lcd);

unsigned int lcd_readData(struct lcd * lcd);

