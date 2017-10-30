#include<stdio.h>
#include <LPC21xx.H>
#include"UART.h"

void ext1 (void);
void EXTINT1VectoredIRQ (void)__irq;
void delay(unsigned long int count1);
void LEDInit (void);
void LedOn1 (void);
void LedOn2 (void);
void LedOn3 (void);
void LedOn4 (void);
void LedOff1 (void);
void LedOff2 (void);
void LedOff3 (void);
void LedOff4 (void);
unsigned int a=0;
#define  LCD_D1    (1 << 8)   // P0.10			100 0000 0000
#define  LCD_D2    (1 << 9)
#define  LCD_D3    (1 << 10)
#define  LCD_D4    (1 << 11)

void main (void)
{
	UART0_initial();
	printf("Hello\n");
	LEDInit ();
	LedOff4();	   //d4=0 
	LedOff3();
	LedOff2();
	LedOff1(); 
	                                                                                    
	ext1();			
	while(1);
}
void ext1 (void){
	printf("%d\n",a);
	PINSEL0 |= 0x20000000;
	VICVectCntl1 	= 0x00000020 | 0x0000000F;  		//select a priority slot for a given interrupt
	VICVectAddr1 	= (unsigned)EXTINT1VectoredIRQ;		//pass the address of the IRQ into the VIC slot
	VICIntEnable 	|= 0x00008000;
}
void EXTINT1VectoredIRQ (void)__irq
{	
	
	delay(3000000);
	for(a=0;a<9;a++){
	if(a == 0){
	delay(1000000);
	printf("%d\n",a);
	LedOff4();	   //d4= 
	LedOff3();
	LedOff2();
	LedOn1();
	}
	else if (a == 1){
	delay(1000000);
	printf("%d\n",a);
	LedOff4();	   //d4= 
	LedOff3();
	LedOn2();
	LedOff1();	   //d4= 
	}
	else if (a == 2){
	delay(1000000);
	printf("%d\n",a);
	LedOff4();	   //d4= 
	LedOff3();
	LedOn2();
	LedOn1();	   //d4=
	}
	else if (a == 3){
	delay(1000000);
	printf("%d\n",a);
	LedOff4();	   //d4= 
	LedOn3();
	LedOff2();
	LedOff1();	   //d4= 
	}
	else if (a == 4){
	delay(1000000);
	printf("%d\n",a);
	LedOff4();	   //d4= 
	LedOn3();
	LedOff2();
	LedOn1();	   //d4= 
	}
	else if (a == 5){
	delay(1000000);
	printf("%d\n",a);
	LedOff4();	   //d 
	LedOn3();
	LedOn2();
	LedOff1();	   //d
	}
	else if (a == 6){
	delay(1000000);
	printf("%d\n",a);
	LedOff4();	   //d
	LedOn3();
	LedOn2();
	LedOn1();	   // 
	}
	else if (a == 7){
	delay(1000000);
	printf("%d\n",a);
	LedOn4();	   //
	LedOff3();
	LedOff2();
	LedOff1();	   // 
	}
	}
	EXTINT  = 0x00000002;					//Clear the peripheral interrupt flag
	VICVectAddr 	= 0x00000000;			//Dummy write to signal end of interrupt
}
void delay(unsigned long int count1)
{
 	while(count1 > 0) {count1--;}
}
void LEDInit (void){
	IODIR0 |= (LCD_D4|LCD_D3|LCD_D2|LCD_D1)	;
	IOSET0 |= (LCD_D4|LCD_D3|LCD_D2|LCD_D1)	;	 

}
void LedOn4 (void){
	IOCLR0 |= LCD_D4;
}
void LedOff4 (void){
	IOSET0 |= LCD_D4;
}
void LedOn3 (void){
	IOCLR0 |= LCD_D3;
}
void LedOff3 (void){
	IOSET0 |= LCD_D3;
}
void LedOn2 (void){
	IOCLR0 |= LCD_D2;
}
void LedOff2 (void){
	IOSET0 |= LCD_D2;
}
void LedOn1 (void){
	IOCLR0 |= LCD_D1;
}
void LedOff1 (void){
	IOSET0 |= LCD_D1;
}

