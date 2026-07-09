#include<lpc21xx.h>
#include"LCD_commands.h"
#include"types.h"
#include"defines.h"
#include"delay.h"


//Send data/command to LCD
void WriteLCD(u8 data)
{
        IOCLR0=1<<RW;//select write mode(RW=0)
        IOPIN0=(IOPIN0&~(0XFF<<PIN))|(data<<PIN);//put 8-bit data on LCD pins
        IOSET0=1<<EN;//Enable LCD
        delay_us(1);//delay
        IOCLR0=1<<EN;//Disable LCD
        delay_ms(2);//Wait until LCD completes operation
}

//send cmd to LCD
void cmdLCD(u8 cmd)
{
        IOCLR0=1<<RS;//(RS=0->command mode)
        WriteLCD(cmd);//send command to LCD
}

//Display one character
void charLCD(unsigned char ascii)
{
        IOSET0=1<<RS;//(RS=1->Data mode)
        WriteLCD(ascii);//send character to LCD
}

//Initialize LCD
void InitLCD(void)
{
        IODIR0=((IODIR0&~(0XFF<<PIN))|(255<<PIN));//configure LCD data pins as output
        IODIR0|=1<<RS;//cnfg RS pin as output
        IODIR0|=1<<RW;//cnfg RW pin as output
        IODIR0|=1<<EN;//cnfg EN pin as output
        delay_ms(15);//Wait after Power ON
        cmdLCD(M_8_1LINE);//Select 1st line
        delay_ms(5);//wait
        cmdLCD(M_8_1LINE);//Repeat the cmd
        delay_us(100);
        cmdLCD(M_8_1LINE);//repeat again
        cmdLCD(M_8_2LINE);//Select 2nd line
        cmdLCD(DISP_CUR_BLINK);//Turn ON display with blinking cursor
        cmdLCD(CLR_LCD);//clear LCD
        cmdLCD(SHIFT_CUR_RIGHT);//move cursor to Right
}

//Display a string
void strLCD(char *p)
{
        //Repeat until '\0'
        while(*p)
                charLCD(*p++);//Display one character and move to next
}

//Display integer value
void intLCD(int n)
{
        int a[10];//store the digits in array
        int i=0;
        //if number is zero
        if(n==0)
        {
                charLCD('0');//Display 0
        }
        //if number is negative
        else if(n<0)
        {
                charLCD('-');//display minus sign
                n=-n;//make num positive
                charLCD('n');
        }

        else
        {
                //Extra digits
                while(n)
                {
                        a[i++]=(n%10)+48;//convert digit to ascii
                        n/=10;//remove last digit
                }
                //Display digits in correct order
                for(--i;i>=0;i--)
                charLCD(a[i]);//Display one digit
        }
}
