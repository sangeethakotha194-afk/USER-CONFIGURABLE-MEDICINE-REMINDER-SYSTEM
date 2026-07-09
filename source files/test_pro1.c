#include <lpc21xx.h>
#include "lcd.h"
#include "kpm.h"
#include "lcd_commands.h"
#include "RTC.h"
#include "delay.h"

#define EINT0_INPUT_PIN 0x0000000C //configure p0.1 as EINT0
#define EINT0_VIC_CHNO  14    		 //VIC channel number for EINT0

#define EINT1_INPUT_PIN 0x000000C0 //configure p0.3 as EINT1
#define EINT1_VIC_CHNO  15   		   //VIC channel number of EINT1

void eint0_isr(void) __irq;  //Interrupt func for EINT0
void eint1_isr(void) __irq;  //Interrupt func for EINT1

#define BUZZER 2 	//Buzzer connected p0.2

int flag1=0,flag2=0,flag3=0,flag4=0;
int timer=0,last_min_triggered=-1,last_sec=0;
signed char m1[]="00:00:00",m2[]="00:00:00",m3[]="00:00:00";
char key;
s32 hour=0,min=0,sec=0,date=0,month=0,year=0,day=0;//RTC variables
int m1_hour=0,m1_min=0,m1_sec=0;//Medicine 1 time
int m2_hour=0,m2_min=0,m2_sec=0;//Medicine 2 time
int m3_hour=0,m3_min=0,m3_sec=0;//Medicine 3 time

//configuration menu
void configuration(void)
{
	cmdLCD(0x01);//clear lcd
	delay_ms(2);//wait for lcd to clear
	
		while(1)
		{
							cmdLCD(0x01);//clear lcd
							cmdLCD(GOTO_LINE1_POS0);//move cursor  to 1st line
							strLCD("1.Edit RTC 3.exit");
							cmdLCD(GOTO_LINE2_POS0);//Move cursor to 2nd line
							strLCD("2.set medicine");
								
							key=keyscan(); //Read Keypad key
			
					//Edit RTC timings
							switch(key)
							{
								
							case '1':
								//Edit RTC Menu
								while(1)
								{
									cmdLCD(CLR_LCD);//clear lcd
									cmdLCD(GOTO_LINE1_POS0);
									strLCD("1.H 2.Mi 3.S 4.dy");
									cmdLCD(GOTO_LINE2_POS0);
									strLCD("5.D 6.M 7.Y 8.Ex");
									key=keyscan();//Read user option
									flag3=1;//Enable medicine reminder checking
													//After key exist goto flag3 condition to check equal or not
													//give RTC timings only
									
								switch(key)
									{		
								case '1':
										a:cmdLCD(CLR_LCD);//clear lcd
										cmdLCD(0x80);//move cursor 1st line
										strLCD("enter hr:");//Ask user to enter hour
										cmdLCD(GOTO_LINE2_POS0);//move cursor 2nd line
											hour=ReadNum(2,"hr");//Read 2-digit hour
								//check valid hour
										if(hour>23)
										{
											strLCD("invalid input!");
											delay_s(1);//wait 1 second
											goto a;//Ask again
										}
										else
										{
										SetRTCTimeInfo(hour,min,sec);//save hour in RTC
										}
										cmdLCD(CLR_LCD);//clear lcd
											cmdLCD(0x80);//cursor 1st line
										DisplayRTCTime(hour,min,sec);//show updated time
										delay_s(1);//wait 1 sec
										break;//exit the loop
										
								case '2':
										b:cmdLCD(CLR_LCD);
										cmdLCD(0x80);
										strLCD("enter min:");//Ask minute
										cmdLCD(GOTO_LINE2_POS0);
											min=ReadNum(2,"min");//read minute
								//check valid minute
										if(min>59)
										{
											strLCD("invalid input!");//display error
											delay_s(1);//wait 1 sec
											goto b;	//read again
										}
										else
										{
										SetRTCTimeInfo(hour,min,sec);//Update RTC
										}
										cmdLCD(CLR_LCD);
											cmdLCD(0x80);
										DisplayRTCTime(hour,min,sec);//show updated RTC
											delay_s(1);//wait 1 sec
										break;//exit case
									
								case '3':
										c:cmdLCD(CLR_LCD);//clear lcd
										cmdLCD(0x80);//goto 1st line
										strLCD("enter sec:");
										cmdLCD(GOTO_LINE2_POS0);//goto 2nd line
											sec=ReadNum(2,"sec");//read seconds
								//check valid sec	
										if(sec>59)
										{
											strLCD("invalid input!");//display error
											delay_s(1);//wait
											goto c;//read again
										}
										else
										{
										SetRTCTimeInfo(hour,min,sec);//updated RTC
										}
										cmdLCD(CLR_LCD);//clear lcd
											cmdLCD(0x80);//cursor 1st line
										DisplayRTCTime(hour,min,sec);//show updated time
										delay_s(1);//wait 1 sec
										break;//exit case
										
								//select the day		
								case '4':
										while(1)
										{
										d:cmdLCD(CLR_LCD);//clear lcd
										cmdLCD(GOTO_LINE1_POS0);//move to 1st line
										strLCD("0.S 1.M 2.TU 3.W");
										cmdLCD(GOTO_LINE2_POS0);//move to 2nd line
										strLCD("4.T 5.F 6.SA 7.Ex");
										key=keyscan();//read keypad input
											
											//check if day is valid
											if(key>='0'&&key<'7')
											{
												day=key-'0';//convert ASCII to integer(Atoi)
												SetRTCDay(day);//store day in RTC
												break;
											}
											//exit option
											else if(key=='7')
											{
												break;
											}
											//invalid input
											else
											{
												cmdLCD(CLR_LCD);//clear lcd
												cmdLCD(GOTO_LINE1_POS0);
												strLCD("invalid!");//display error 
												cmdLCD(GOTO_LINE2_POS0);
												strLCD("enter again");//ask again
												delay_s(1);//wait 1 sec
											goto d;//read input again
											}
									}
							break;//return to RTC menu
							//Set Date	
							 case '5':
										e:cmdLCD(CLR_LCD);
										cmdLCD(GOTO_LINE1_POS0);
										strLCD("enter date:");//Ask user to enter the date
										cmdLCD(GOTO_LINE2_POS0);
										date=ReadNum(2,"date");//Read the date
										//check valid date
										if((date<=0)||(date>31))
										{
											cmdLCD(CLR_LCD);
											cmdLCD(GOTO_LINE1_POS0);
											strLCD("enter again");//Invalid sta			
											delay_s(1);
											goto e;//Read again
										}
										else
										{
											SetRTCDateInfo(date,month,year);//Update the RTC
										}
										cmdLCD(CLR_LCD);
											cmdLCD(GOTO_LINE1_POS0);
										DisplayRTCDate(date,month,year);//Display the RTC
										delay_s(1);//wait for 1 sec
										break;
								//Set the Month	
								case '6':
										f:cmdLCD(CLR_LCD);//Clear LCD
										cmdLCD(GOTO_LINE1_POS0);//Move cursor to 1st line
										strLCD("enter month:");//Ask to user for month
										cmdLCD(GOTO_LINE2_POS0);//Move cursor to 2nd line
										month=ReadNum(2,"month");//Read the month
								//check validate month
										if((month<=0)||(month>12))
										{
											cmdLCD(CLR_LCD);
											cmdLCD(GOTO_LINE1_POS0);
											strLCD("enter again");//Invalid Month			
											delay_s(1);
											goto f;//Read again
										}
										else
										{
											SetRTCDateInfo(date,month,year);//Update RTC
										}
										  cmdLCD(CLR_LCD);//Clear LCD
											cmdLCD(GOTO_LINE1_POS0);
											DisplayRTCDate(date,month,year);//Display RTC
										delay_s(1);
									break;
							//Set year
								case '7':
									g:cmdLCD(CLR_LCD);//Clear LCD
										cmdLCD(GOTO_LINE1_POS0);//Move cursor 1st line
										strLCD("enter year;");//Ask user for Year
										cmdLCD(GOTO_LINE2_POS0);//Move Cursor 2nd line
											year=ReadNum(4,"year");//Read the year
								//check validate year
											if((year<=0) || (year>4096))
											{
											cmdLCD(CLR_LCD);
														cmdLCD(GOTO_LINE1_POS0);
														strLCD((char*)"inval,enter once");//Invalid year
												delay_s(1);
											goto g;//Read again
											}
											else
											{
												SetRTCDateInfo(date,month,year);//update RTC
											}
									     cmdLCD(CLR_LCD);
											cmdLCD(GOTO_LINE1_POS0);
									   	DisplayRTCDate(date,month,year);//Display RTC
											delay_s(1);//wait for 1 sec
									break;
							//Exit RTC Menu
							 case '8':
									break;
							 //Default case
									default:
										cmdLCD(CLR_LCD);
										cmdLCD(GOTO_LINE1_POS0);
										strLCD((char*)"invalid input");//Display the invalid option
									 delay_s(1);
									break;
									}
									//If exit is selected
									if(key=='8')
										break;//Leave RTC menu 
								}
								break;
		//medicine time setting							
				case '2':
					//Repeat until Exit is selected
									while(1)
									{
										cmdLCD(CLR_LCD);
										cmdLCD(GOTO_LINE1_POS0);
										strLCD("1.m1time 2.m2time");
										cmdLCD(GOTO_LINE2_POS0);
										strLCD("3.m3time 4.exit");
										key=keyscan();//Read keypad input
						//check selected medicine					
					   	switch(key)
								{
									//medicine 1 setting	
									   case '1':
												while(1)
													{
														cmdLCD(CLR_LCD);
														cmdLCD(GOTO_LINE1_POS0);
														strLCD("1.hr 2.min");
														cmdLCD(GOTO_LINE2_POS0);
														strLCD("3.Exit");
														key=keyscan();//Read keypad input
														
															switch(key)
															{
														//Medicine1 hour 
													   case '1':
																		    m1a:cmdLCD(CLR_LCD);//clear LCD
																						cmdLCD(GOTO_LINE1_POS0);//first line
																						strLCD("enter hour:");//Ask for hour
																					cmdLCD(GOTO_LINE2_POS0);//second line
																						m1_hour=ReadNum(2,"hr");//Read hour
																				//check valid hour
																						if(m1_hour>23)
																						{
																							strLCD("invalid input!");//Display error
																							delay_s(1);
																							goto m1a;//Read again
																						}
																						cmdLCD(CLR_LCD);//clear LCD
																							cmdLCD(GOTO_LINE1_POS0);
																						DisplayRTCTime(m1_hour,m1_min,m1_sec);//Display medicine time
																						delay_s(1);//wait
																						break;
															//Medicine1 minute
																case '2':
																					m1b:cmdLCD(CLR_LCD);
																							cmdLCD(GOTO_LINE1_POS0);
																							strLCD("enter min:");//Ask minute
																					  	cmdLCD(GOTO_LINE2_POS0);
																							m1_min=ReadNum(2,"min");//Read minute
																						//validate minute
																					  	if(m1_min>59)
																						  {
																							  strLCD("invalid min input!");//Display error
																							  delay_s(1);//wait
																							  goto m1b;	//Read again
																						  }
																						cmdLCD(CLR_LCD);
																							cmdLCD(GOTO_LINE1_POS0);
																						DisplayRTCTime(m1_hour,m1_min,m1_sec);//Show update time
																							delay_s(1);
																						break;
														//Exit Medicine1 menu
																case '3':
																				break;
																//default case
																default:
															    	cmdLCD(CLR_LCD);
																		cmdLCD(GOTO_LINE1_POS0);
																		strLCD((char*)"invalid input");
																		delay_s(1);
																			break;
																		}
															//Exit key selected
																	if(key=='3')
																		break;//Return to Medicine menu 
																}
															break;
										//medicine2 setting						
										case '2':
												while(1)
														{
															cmdLCD(CLR_LCD);
															cmdLCD(GOTO_LINE1_POS0);
															strLCD("1.hr 2.min");
															cmdLCD(GOTO_LINE2_POS0);
															strLCD("3.Exit");
															key=keyscan();//Read key
															
																switch(key)
																 {
																//Medicine2 hour 
																 case '1':
																      	 m2a:cmdLCD(CLR_LCD);
																					cmdLCD(GOTO_LINE1_POS0);
																					strLCD("enter hour:");//Ask hour
																				cmdLCD(GOTO_LINE2_POS0);
																					m2_hour=ReadNum(2,"hr");//Read hour
																 //check validate hour
																					if(m2_hour>23)
																					{
																						strLCD("invalid input!");
																						delay_s(2);
																						goto m2a;//read again
																					}
																					cmdLCD(CLR_LCD);
																					cmdLCD(GOTO_LINE1_POS0);
																					DisplayRTCTime(m2_hour,m2_min,m2_sec);//Show medicine time
																					delay_s(1);//wait
																					break;
																////Medicine2 minute
																	case'2':
																			 	m2b:cmdLCD(CLR_LCD);//clear LCD
																						cmdLCD(GOTO_LINE1_POS0);
																						strLCD("enter min:");//Ask for minute
																					  cmdLCD(GOTO_LINE2_POS0);
																						m2_min=ReadNum(2,"min");//Read minute
																	//check validate min
																					if(m2_min>59)
																					{
																						strLCD("invalid input!");
																						delay_s(2);
																						goto m2b;	//Read again
																					}
																					cmdLCD(CLR_LCD);
																					cmdLCD(GOTO_LINE1_POS0);
																					DisplayRTCTime(m2_hour,m2_min,m2_sec);//Display saved time
																						delay_s(1);//wait
																					break;
																					
														//exit Medicine2	
															case '3':
																		break;
														//default case
															default:
																	cmdLCD(CLR_LCD);//clear LCD
																	cmdLCD(GOTO_LINE1_POS0);
																	strLCD((char*)"invalid input");//Invalid option
																	delay_s(2);
																	break;
																	}
														 //exit medicine2 
																if(key=='3')
																break;
															}
														break;
															
								//Medicine3 setting							
											case '3':
															while(1)
																	{
																		cmdLCD(CLR_LCD);
																		cmdLCD(GOTO_LINE1_POS0);
																		strLCD("1.hr 2.min");
																		cmdLCD(GOTO_LINE2_POS0);
																		strLCD("3.Exit");
																		key=keyscan();//Read keypad input
																		
																			switch(key)
																			{
																		//Medicine3 hour
																		 case '1':
																				      m3a:cmdLCD(CLR_LCD);
																								cmdLCD(GOTO_LINE1_POS0);
																								strLCD("enter hour:");//Ask user for hour
																							cmdLCD(GOTO_LINE2_POS0);
																								m3_hour=ReadNum(2,"hr");//Read hour
																							
																						//check validate hour
																								if(m3_hour>23)
																								{
																									strLCD("invalid input!");//invalid option
																									delay_s(2);//wait
																									goto m3a;//Read again
																								}
																								cmdLCD(CLR_LCD);
																								cmdLCD(GOTO_LINE1_POS0);
																								DisplayRTCTime(m3_hour,m3_min,m3_sec);//Display RTC
																								delay_s(1);
																								break;
																			
																		//Medicine2 minute
																			case '2':
																							 m3b:cmdLCD(CLR_LCD);//clear LCD
																									cmdLCD(GOTO_LINE1_POS0);
																									strLCD("enter min:");//Ask min
																								cmdLCD(GOTO_LINE2_POS0);
																									m3_min=ReadNum(2,"min");//Read min
																						//check validate min
																								if(m3_min>59)
																								{
																									strLCD("invalid input!");
																									delay_s(2);
																									goto m3b;	//Read again
																								}
																								cmdLCD(CLR_LCD);
																								cmdLCD(GOTO_LINE1_POS0);
																								DisplayRTCTime(m3_hour,m3_min,m3_sec);//Display updated RTC
																								delay_s(1);
																								break;
																		//exit case
																			case '3':
																								break;
																		//Default case			
																			default:
																					cmdLCD(CLR_LCD);
																					cmdLCD(GOTO_LINE1_POS0);
																					strLCD((char*)"invalid input");
																						delay_s(1);
																				break;
																						}
																	//Exit medicine3		
																		if(key=='3')
																			break;
																					
																		}
																break;
											//Exit loop for medicine Menu							
											case '4':
												break;
											//default case for medicine Menu		
											default:
												cmdLCD(CLR_LCD);
												cmdLCD(GOTO_LINE1_POS0);
												strLCD((char*)"invalid input");
												delay_s(2);
												break;
									}
					//exit case selected
					if(key=='4')						
						break;
				}
				break;
			//Exit case for main Menu
				case '3':
							cmdLCD(CLR_LCD);
						break;
				//Default case for main
				default:
						cmdLCD(CLR_LCD);
						cmdLCD(GOTO_LINE1_POS0);
						strLCD((char*)"invalid input");
						delay_s(2);
					break;
			}
			//Exit for main
					if(key=='3')							
						break;
		}
		
	}
	
//main
	
int main()
{
	int sec=0;
	IODIR0|=1<<BUZZER;//intialise the buzzer direction
	InitLCD();//Intialize LCD
	RTC_Init();//Intialize RTC
	InitKPM();//Initialize KPM
	
	//cfg p0.1,p0.3 pin as EINT0,EINT1 input pins
	//clr bit pair 2&3 & bit pair 6&7,w/o affecting other bits
	PINSEL0 &= ~((3<<2) | (3<<6));   // clear P0.1 & P0.3
	PINSEL0 |=  ((1<<2) | (1<<6));   // set EINT0 & EINT1
	//update bit2&3,bit6&7 for EINT0,EINT1 pin function
	PINSEL0|=EINT0_INPUT_PIN|EINT1_INPUT_PIN;//Enable interrupt pins
	
	//cfg VIC peripheral/block allow EINT0,EINT1 as irq type
	//VICIntSelect=0; //default
	//enable EINT0,EINT1 through channel
	VICIntEnable=1<<EINT0_VIC_CHNO|
	             1<<EINT1_VIC_CHNO;//Enable EINT0 and EINT1
	//Cfg EINT0 as v.irq with highest priority(0)
	VICVectCntl1=(1<<5)|EINT0_VIC_CHNO;
	//load eint0_isr address into LUT sfr
  VICVectAddr1=(u32 ) eint0_isr;

  //Cfg EINT1 as v.irq with next highest priority(1)
	VICVectCntl0=(1<<5)|EINT1_VIC_CHNO;
	//load eint1_isr address into LUT sfr
  VICVectAddr0=(u32 ) eint1_isr;

  //Cfg EINT0,EINT1 via External Interrupts Peripheral	
	//Enable EINT0,EINT1
	//EXTINT=0;//default
	//Cfg EINT0,EINT1 as edge triggered interrupt
	EXTMODE=((1<<1)|(1<<0));//cfg EINT0,EINT1 as falling edge triggered
	//EXTPOLAR=0;//default
	
	cmdLCD(DISP_ON);//Turn ON LCD display
	
	while(1)
	{
		//Read current RTC time
		GetRTCTimeInfo(&hour,&min,&sec);//get here the medicine timings and RTC timings 
		//Check if configuration button pressed
		if(flag1)
		{
			flag1=0;//reset flag
			cmdLCD(DISP_CUR_BLINK);//Enable LCD cursor
			configuration();//Enable LCD cursor
			cmdLCD(CLR_LCD);//Clear LCD
			cmdLCD(DISP_ON);//Turn display ON
		}
	//one second 	timer
		if(sec !=last_sec)
		{
			last_sec=sec;//store current sec
		//Timer is ruuning
			if(timer>0)
			{
				timer--;//Decrease timer by 1
				//timer expired
				 if(timer == 0)
         {
            cmdLCD(CLR_LCD);
            strLCD("Medicine skipped");
					  delay_s(5);
            
            last_min_triggered = -1;   // reset trigger
					  cmdLCD(CLR_LCD);//Clear LCD
         }
			}
		
		}
//Medicine taken button		
		if(flag2)
		{
			flag2=0;//reset flag2
			cmdLCD(CLR_LCD);
			strLCD("Medicine Taken"); // Visual confirmation
			delay_s(2);
			timer=0;//stop timer
			flag3=0;//Disable reminder checking
			cmdLCD(GOTO_LINE1_POS0);
			cmdLCD(CLR_LCD);//clear lcd

		}
	//Medicine button pressed without reminder
		if(flag4)
		{
			flag4=0;//reset flag4
			cmdLCD(CLR_LCD);
			strLCD("No remainders");
			cmdLCD(GOTO_LINE2_POS0);
			strLCD("NOW!!!!");
			delay_s(5);
			cmdLCD(CLR_LCD);//Clear LCD
		}
	//Medicine reminder enabled	
			 if(flag3)
			 {
				 
				 if(last_min_triggered!=min)
		    	{
			 //check RTC time eith medicine time
				  if((hour==m1_hour && min==m1_min)||
						(hour==m2_hour && min==m2_min)||
					  (hour==m3_hour && min==m3_min))
						{
							//timer not running
							if(timer==0)
							{
								timer=60;//set timer as 60 sec
								last_min_triggered=min;	//save triggered min
						  }

				   }
				}
					
			}
		//Reminder is active
			 if(timer>0)
			 {
				 //same reminder minute
				if(last_min_triggered==min)
				{

					cmdLCD(GOTO_LINE1_POS0);
					strLCD("Take Medicine!!");
					cmdLCD(GOTO_LINE2_POS0);
					strLCD(" NOW!!  ");
					cmdLCD(GOTO_LINE2_POS0+8);
					strLCD("Timer:");//Display timer
					cmdLCD(GOTO_LINE2_POS0+14);
					intLCD(timer);//Display timer value
					if(timer<10)
					{
						strLCD("  ");//to remove overlapping of timer
					}
					
					IOSET0=1<<BUZZER;//set buzzer
					flag1=0;
					
				}
			}
					else 
					{				
					//set buzzer clearing
					IOCLR0=1<<BUZZER;
						
						
						//set RTC time
						cmdLCD(GOTO_LINE1_POS0);//first line
						GetRTCTimeInfo(&hour,&min,&sec);//Read RTC
						DisplayRTCTime(hour,min,sec);//Display time
						
						cmdLCD(GOTO_LINE1_POS0+10);//Move cursor
						GetRTCDay(&day);//Read day
						DisplayRTCDay(day);//Display day
						
						cmdLCD(GOTO_LINE2_POS0);//second line
						GetRTCDateInfo(&date,&month,&year);	//Read date
						DisplayRTCDate(date,month,year);//Display date
					}
		
			}
}

void eint0_isr(void) __irq
{
	//clear EINT0 Status in Ext Int Peripheral
	EXTINT=1<<0;
	//clear EINT0 status in VIC peripheral
	VICVectAddr=0;
	flag1=1;
	IOCLR0=1<<BUZZER;
}

void eint1_isr(void) __irq 
{
    EXTINT = 1 << 1;        // Clear EINT1 interrupt flag
    VICVectAddr = 0;        // Acknowledge VIC
    if(timer>0)
		{
    IOCLR0 = 1 << BUZZER;   // Immediately stop the buzzer
		timer = 0;        // Reset the alert duration
    flag2=1;
		cmdLCD(0x01);
		}
		else
		{
			flag4=1;
		}
    
}
