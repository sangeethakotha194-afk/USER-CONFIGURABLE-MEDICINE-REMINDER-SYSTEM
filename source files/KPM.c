#include<lpc21xx.h>
#include "kpm_defines.h"
#include "types.h"
#include "lcd.h"
#include "delay.h"
#include "defines.h"
#include<string.h>


int sum=0,i=0,temp1=0,temp2=0,temp3=0;
//keypad look up table
unsigned char KPMLUT[4][4]={
                                {'7','8','9','/'},
                                {'4','5','6','*'},
                                {'1','2','3','-'},
                                {'c','0','=','+'}       };

//Intialize the keypad
void InitKPM(void)
{
        IODIR1=15<<ROW0;//cnfg row pins as output
}

//check any key pressed or not
u32 colscan(void)
{
        return ((RNIBBLE(IOPIN1,COL0)&15)<15)?0:1;//return value based on the value is <15 as 0 or >15 as 1
}

//Find  which row is pressed
u32 rowcheck(void)
{
u32 rno;
//check all rows
for(rno=0;rno<4;rno++)
{
        IOPIN1=(~(1<<rno)<<ROW0);//make one row active
//key found
if(colscan()==0)
{
break;//stop checking
}

}
//make rows default
IOPIN1=0X0<<ROW0;
return rno;//return row number
}

//Find which column pressed
u32 colcheck(void)
{
        u32 cno;
        //check all columns
        for(cno=0;cno<4;cno++)
        {
                if(((IOPIN1>>(COL0+cno))&1)==0)
                {
                        break;//column found
                }
        }
        return cno;//return column number
}

//Read one key from keypad
unsigned char keyscan(void)
{
        u32 rno,cno,keyV;
        //wait for switch press;
        while(colscan());
        //find rno;
        rno=rowcheck();
        //find cno;
        cno=colcheck();
        //get keyvalue using KPMLUT
        keyV=KPMLUT[rno][cno];
        //wait for switch release
        while(!colscan());//wait until key is released
        return keyV;//return pressed key
}

//Read number from keypad
int ReadNum(int n)
{
        char key;
        int sum=0,i=0;
        //read required digits
        for(;n>0;)
        {
                key=keyscan();//Read one key
                //check digit
                if(key>='0' && key<='9')
                {
                        charLCD(key);//Display digit
                        sum=(sum*10) + (key - '0');//convert to number
                        i++;//increase count
                        n--;//one digit completed
                }
                //clear key
                else if(key=='c')
                {
                        if(i>0)
                        {
                                i--;//reduce digit count
                                n++; //allow to rentry the digit
                                sum=sum/10;//remove last digit
                        cmdLCD(SHIFT_DISP_LEFT);//move cursor left
                        charLCD(' ');//erase digit
                        cmdLCD(SHIFT_DISP_LEFT);//move cursor back
                        }
                }
                //Invalid key
                else
                {
                        cmdLCD(CLR_LCD);//clear LCD
                        cmdLCD(GOTO_LINE1_POS0);//first line
                        strLCD("Invalid input");
                        delay_ms(1000);
                        sum=0;//Reset number
                        break;//exit
                }
        }
        return sum;//Return entered number
}
