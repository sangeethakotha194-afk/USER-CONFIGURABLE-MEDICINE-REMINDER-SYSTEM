#include "types.h" //User-defined data types

//Intialize keypad
void InitKPM(void);
//Read one key from keypad
unsigned char keyscan(void);
//Read number from keypad
u32 ReadNum(int n,char*);
//check any key is pressed
u32 colscan(void);
//Find pressed row
u32 rowcheck(void);
//Find pressed column
u32 colcheck(void);
