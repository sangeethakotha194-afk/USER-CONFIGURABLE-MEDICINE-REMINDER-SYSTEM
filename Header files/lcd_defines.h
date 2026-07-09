

//#ifndef_ DEFINES_H
//#define_ DEFINES_H

//Set a bit 
#define SETBIT(WORD,BITPOS) (WORD|=1<<BITPOS)
//Clear a bit
#define CLRBIT(WORD,BITPOS) (WORD&=~(1<<BITPOS)
//Set only one bit
#define SSETBIT(WORD,BITPOS) (WORD=1<<BITPOS)
//Clear all bits except one
#define SCLRBIT(WORD,BITPOS) (WORD=1<<BITPOS)
//Toggle a bit
#define CPLBIT(WORD,BITPOS) (WORD^=1<<BITPOS)
//Write one byte
#define WBYTE(WORD,SBITPOS,BYTE) (WORD=(WORD&~(0XFF<<SBITPOS))|(BYTE<<SBITPOS))
//Write one nibble
#define WNIBBLE(WORD,SBITPOS,NIBBLE) (WOPD=(WORD&~(0XF<<SBITPOS))|(NIBBLE<<SBITPOS))
//Write one bit
#define WBIT(WORD,BITPOS,BIT) (WORD=(WORD&~(1<<BITPOS))|(BIT<<SBITPOS))
//Read one bit
#define RBIT(WORD,BITPOS) ((WORD>>BITPOS)&1)
//Read one nibble
#define RNIBBLE(WORD,SBITPOS) ((WORD>>SBITPOS)&15)
//Read one byte
#define RBYTE(WORD,SBITPOS) ((WORD>>SBITPOS)&255)
//copy one bit from source to destination
#define READWRITEBIT(DWORD,DBIT,SBIT) (DWORD=(DWORD&~(1<<DBIT))|((DWORD>>SBIT)&1)<<DBIT)
