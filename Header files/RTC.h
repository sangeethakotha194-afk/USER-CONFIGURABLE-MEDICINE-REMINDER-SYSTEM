#include <lpc214x.h>

//include LCD header files
#include "lcd.h"
#include "lcd_defines.h"


// System clock and peripheral clock Macros
#define FOSC 3000000
#define CCLK (5*FOSC)    
#define PCLK (CCLK/4)

// RTC Prescaler Calculation Macros
// RTC requires 32.768 kHz clock for 1-second increment.
// PREINT and PREFRAC registers divide PCLK to generate 32.768 kHz.

// PREINT = int (PCLK / 32768) - 1;
// PREFRAC = PCLK -((PREINT + 1) * 32768);
// Note: This information collected from LPC2129 Manual

#define PREINT_VAL (int) ((PCLK / 32768) - 1)
#define PREFRAC_VAL (PCLK -((PREINT_VAL + 1) * 32768))

//Enable RTC
#define RTC_ENABLE (1<<0)

//  Reset RTC
#define RTC_RESET (1<<1)
 

//only for LPC2148
//Select external RTC clock 
#define RTC_CLKSRC (1<<4)

//Day values
#define SUN 0
#define MON 1
#define TUE 2
#define WED 3
#define THU 4
#define FRI 5
#define SAT 6

//Intialize RTC
void RTC_Init(void);
//Read current time
void GetRTCTimeInfo(s32 *,s32 *,s32 *);
//Display time
void DisplayRTCTime(u32,u32,u32);
//Read current date
void GetRTCDateInfo(s32 *,s32 *,s32 *);
//Display date
void DisplayRTCDate(u32,u32,u32);
//Set RTC time
void SetRTCTimeInfo(u32,u32,u32);
//Set RTC date
void SetRTCDateInfo(u32,u32,u32);
//Read current day
void GetRTCDay(s32 *);
//Display day
void DisplayRTCDay(u32);
//Set current day
void SetRTCDay(u32);
