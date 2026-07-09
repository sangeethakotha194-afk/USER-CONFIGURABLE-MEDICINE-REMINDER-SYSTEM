//Delay in microseconds
void delay_us(unsigned int dlyus)
{
//convert us into loop count
for(dlyus*=12;dlyus>0;dlyus--);//wait until loop finishes
}

//Delay in milliseconds
void delay_ms(unsigned int dlyms)
{
//convert ms into loop count
for(dlyms*=12000;dlyms>0;dlyms--);//wait until loop finishes
}

//Delay in seconds
void delay_s(unsigned int dlys)
{
//convert sec into loop count
for(dlys*=1200000;dlys>0;dlys--);//wait until loop finishes
}

