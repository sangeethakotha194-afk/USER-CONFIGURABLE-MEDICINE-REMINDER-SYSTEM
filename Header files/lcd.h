 #include "lcd_commands.h" //LCD command definitions
 #include "types.h"       //User-defined datatypes

//send cmd to LCD
 void cmdLCD(u8 cmd);
//Display one character
 void charLCD(unsigned char ascii);
//Intialize LCD
 void InitLCD(void);
//send data to LCD
 void writeLCD(u8 data);
// Display string
 void strLCD(char *p);
//Display integer
void intLCD(u32 n);
