#include"RTC.h"

extern s32 hour,min,sec,date,month,year,day;//Global RTC variables

//store names of week days
char week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};
//select LPC2148 controller
#define _LPC2148

//Intialize RTC
void RTC_Init(void)
{
  // Disable and reset the RTC
        CCR = RTC_RESET;
  // Set prescaler integer and fractional parts
        PREINT = PREINT_VAL;
        PREFRAC = PREFRAC_VAL;

  // Enable the RTC
        CCR = RTC_ENABLE;
}

//Display time on LCD
void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second)
{
        *hour = HOUR;//Read hour
        *minute = MIN;//Read min
        *second = SEC;//Read sec

}

//Display time on LCD
void DisplayRTCTime(u32 hour, u32 minute, u32 second)
{
        charLCD(hour/10+48);//Display hour in tens digit
        charLCD(hour%10+48);//Display hour in units digit
        charLCD(':');//Display :
        charLCD(minute/10+48);//Display min in tens digit
        charLCD(minute%10+48);//Display min in units digit
        charLCD(':');//Display :
        charLCD(second/10+48);//Display sec in tens digit
        charLCD(second%10+48);//Display sec in units digit
}

//Read current date
void GetRTCDateInfo(s32 *date, s32 *month, s32 *year)
{
        *date = DOM;//Read date
        *month = MONTH;//Read month
        *year = YEAR;//Read year
}

//Display date on LCD
void DisplayRTCDate(u32 date, u32 month, u32 year)
{

        charLCD(date/10+48);
        charLCD(date%10+48);
        charLCD('/');
        charLCD(month/10+48);
        charLCD(month%10+48);
        charLCD('/');
        if(year==0)
                strLCD("0000");
        else
                intLCD(year);
}

//set RTC time
void SetRTCTimeInfo(u32 hour, u32 minute, u32 second)
{
        HOUR = hour;//store hour
        MIN = minute;//store min
        SEC = second;//store sec
}

//Set the RTC date
void SetRTCDateInfo(u32 date, u32 month, u32 year)
{
        DOM = date;//store date
        MONTH = month;//store month
        YEAR = year;//store year
}

//Get the current day of the week
void GetRTCDay(s32 *dow)
{
        *dow = DOW;//store day
}

//Display the current day of the week on LCD
void DisplayRTCDay(u32 dow)
{
        //cmdLCD(GOTO_LINE1_POS0+10);
        strLCD(week[dow]);

}

//Set the day of the week in RTC
void SetRTCDay(u32 dow)
{
        DOW = dow;
}
