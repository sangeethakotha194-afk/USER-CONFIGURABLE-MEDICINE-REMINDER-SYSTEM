//LCD data pins start from P0.8
#define PIN 8
//LCD Register select pin
#define RS 16
//LCD Read/Write pin
#define RW 17
//LCD Enable pin
#define EN 18
//clear LCD screen
#define CLR_LCD 0X01
//Turn off LCD display
#define DISP_OFF 0X08
//move cursor to home position
#define RET_CUR_HOME 0X02
//Turn ON LCD display
#define DISP_ON 0X0C
//Display ON with cursor
#define DISP_ON_CUR_ON 0X0E
//Display ON with Blinking cursor
#define DISP_CUR_BLINK 0X0F
//8-bit 1-line mode 
#define M_8_1LINE 0X30
//8-bit 2-line mode 
#define M_8_2LINE 0X38
//4-bit 1-line mode 
#define M_4_1LINE 0X20
//4-bit 2-line mode 
#define M_4_2LINE 0X28
//cursor to 1st line
#define GOTO_LINE1_POS0 0X80 
//cursor to 2nd line
#define GOTO_LINE2_POS0 0XC0
//cursor to 3rd line
#define GOTO_3_POS0 0X94
//cursor to 4th line
#define GOTO_4_POS0 0X04
//Move cursor right
#define SHIFT_CUR_RIGHT 0X06
//shift display left
#define SHIFT_DISP_LEFT 0X10
//shift display right
#define SHIFT_DISP_RIGHT 0X04
//Goto CGRAM
#define GOTO_CGRAM 0X40
