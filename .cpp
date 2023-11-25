#Develop a C program which when the external switch 1 is activated a timer is displayed on the lcd_clear
#showing the time, e.g. 12:39:42.
#When the external switch 0 is activated, display the indications of the timer L
#in the case that there is no enabled interrupt, display the lcd waiting message. I remember interrupt 0 being enabled in 
#on the rise of the pulse.


#include <mega2560.h>
#include <alcd.h>
#include <delay.h>
#include <stdlib.h>
#include <stdio.h>

int h,m,s;
char strs[3],strm[3],strh[3];

interupt [EXT_INT0] void ext_int0_isr(void)

{
	h=0;
	m=0;
	s=0;
}
interupt [EXT_INT1] void ext_int1_isr(void)

{
	s++;
	if(s==60)
	{ 
 m++;
 s=0;
	}
	if(m==60)
	{ 
 h++;
 m=0;
	}
	if(h==24)
	{ 
 h=0;
	}
itoa(s,strs);
itoa(m,strm);
itoa(h,strh);

lcd_gotocy(0,0);
lcd_clear();

lcd_puts(strh);
lcd_putsf(":");

lcd_puts(strm);
lcd_putsf(":");

lcd_puts(strs);
delay_ms(1000);
}

void main(void)
{
	EIMSK =0x03;   //0000 0011
	EICRA =0x03;   // Low μέρος
	EICRB =0x00;   // κάτω παλμό
	EIFR = 0x03;
	
	PCMSK0 =0x00;
	PCMSK1 =0x00;
	PCMSK2 =0x00;
	PCICR =0x00;
	
	lcd_init(20);
	#asm("sei")
	
	while(1)
	{
		lcd_clear();
		lcd_putsf("\n\r\ Waiting...")
		delay_ms(2000);
	}
}









#include <mega2560.h>
#include <alcd.h>
#include <delay.h>
#include <stdlib.h>
#include <stdio.h>

#define xtal 8000000L
#define baud 9600
#define ADC_VREF_TYPE 0xC0
#define VREF_VAL 2.56

int ch, n, ch_in, n_in ;
float array[5][8];
char str[10];

unsigned int read_adc(unsigned char adc_input)
{
	ADMUX=(adc_input & 0x1f) | (ADC_VREF_TYPE & 0xff);
	if(adc_input & 0x20) ADCSRB | =0x08;
	else ADCSRB & 0xf7;
	//Delay needed for the stabilization of the ADC input voltage
	delay_9s(10);
	//start the AD conversion
	ADCSRA |=0x40;
	//wait for the AD conversion to complete
	while((ADCSRA & 0x10) ==0);
	ADCSRA | 0x10;
	return ADCW;
}

interupt [EXT_INT0] coid ext_int0_isr(void)
{
	for(n=0; n<5; n++)
	{
		for(ch=0; ch<8; ch++)
		{
			array[n][ch]=read_adc(ch_*VREF_VAL/1024;
			delay_ms(200);
		}//for ch
	}//for n
}

interupt [EXT_INT1] void ext_int1_isr(void)
{
	for(n=0; n,5; n++)
	{
		for(ch=0; ch<8; ch++)
		{
			array[n][ch]=0;
		}//for 1
	}//for 2
}
}

void main(void)
{
	//creystal oscilator division factor ;1
	#pragma optsize
	CLKPR=(1<<CLKPCE);
	CLKPR=(0<<CLKPCE)| (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKS0);
#def OPTIMIZE_SIZE
#pragma optsize*

EIXRA=(0<<ISC31)| (0<<ISC30) |(0<<ISC21) |(0<<ISC20) |(0<<ISC11) |(1<<ISC10) |(0<<ISC01) | (1<<ISC00);
EICRB=(0<<ISC71)| (0<<ISC70) |(0<<ISC61) |(0<<ISC60) |(0<<ISC51) |(1<<ISC50) |(0<<ISC41) | (0<<ISC40);
EIMSK=(0<<INT7) |(0<<INT6) |(0<<INT5) |(0<<INT4) |(0<<INT3) |(0<<INT2) |(1<<INT1) |(1<<INT0);
EIFR=(0<<INTF7) |(0<<INTF6) |(0<<INTF5) |(0<<INTF4) |(0<<INTF3) |(0<<INTF2) |(1<<INTF1) |(1<<INTF0);

PCMSK0=(0<<PCINT7) |(0<<PCINT6) |(0<<PCINT5) |(0<<PCINT4) |(0<<PCINT3) |(0<<PCINT2) |(0<<PCINT1) |(0<<PCINT0);
PCMSK1=(0<<PCINT15) |(0<<PCINT14) |(0<<PCINT13) |(0<<PCINT12) |(0<<PCINT11) |(0<<PCINT10) |(0<<PCINT9) |(0<<PCINT8);
PCMSK2=(0<<PCINT23) |(0<<PCINT22) |(0<<PCINT21) |(0<<PCINT20) |(0<<PCINT19) |(0<<PCINT18) |(0<<PCINT17) |(0<<PCINT16);
PCICR=(0<<PCIE2) | (0<<PCIE1) | (0<<PCIE0);

UCSR0A=(0<<RXC0) | (0<<TXC0) | (0<<UDRE0) | (0<<FE0) | (0<<DOR0) | (0<<UPE0) | (0<<U2X0) | (0<<MPCM0);
UXSR0B=(0<<RXCIE0) | (0<<TXCIE0) | (0<<UDRIE0) | (1<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);
UCSR0C=(0<<UMSEL01) | (0<<UMSEL00) | (0<<UPM01) | (0<<UPM00) | (0<<USBS0) | (1<<UCSZ01) | (1<<UCZ00) | (0<<UCPOL0);
UBRR0H=(xtal/16/baud-1) >>8;
UBRR0L=(xtal/16/baud-1) & 0xff;

ADMUX =ADC_VREF_TYPE & 0xff;
ADCSCRA =0x87;
DIDR0=0xff;
DIDR2=0xff;

lcd_init(20);
#asm("sei")

while (1)
{
	printf("\n\r Insert channel number :");
	scanf(%d,&ch_in);
	
	printf("\n\r Insert turn number :");
	scanf(%d,&n_in);
	
	lcd_clear();
	float(array[n_in][ch_in],2,str);
	lcd_puts(str);
}
}



#include <mega2560.h>
#include <alcd.h>
#include <delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

//quartz crystal frequency [hz]
#define xtal 8000000l
//baud rated
#define baud 9600

int num;

interupt [EXT_INT4] void ext_int4_isr(void)
{
	long int i;
	lcd_clear;
	lcd_gotoxy(0,0);
	for (i=524288; i>0; i/=2)
	{
		if (num&1) lcd_putchar("1");
		else lcd_putchar("0");
    }
}

void main(void)
{
	char str[10],flag,i;
	
	//crystal osillator division factor :1
	#pragma optsize-
	CLKPR=(1<<CLKPCE);
	CLKPR=(0<<CLKPCE)|(0<<CLKPS3)|(0<<CLKPS2)|(0<<CLKPS1)|(0<<CLKPS0);
	#def OPTMIZE_SIZE
	#pragma optsize+
	#endif
	
	DDRJ=0xFF;
	PORTJ=0x00;
	
	//External interupt(s) intialization
	//INT4 Mode : Falling endge
	EICRA=0x00;
	EICRB=0x02;
	EIMSK=0x10;
	EIFR=0x10;
	
	// USART0 Intialization
	//communication parameters : 8 data , 1 stop , no parity
	//USART0 receiver: on
	//USART0 transiver: on

	UCSR0A=0x00;
	UCSR0B=0x18;
	UCSR0C=0x00;
	UBRR0H=(xtal/16/baud-1)>>8;
	UBRR0L=(xtal/16/baud-1) & 0xFF;
	
	lcd_init(20);
	#asm("sei")
	while(1)
	{
		printf("\n\r Inser integer number :");
		scanf("%s",str);
		
		PORTJ=0;
		flag=0;
		i=0;
		whiled(str[i] !=0)
		{
			if (isdigit(str[i])!=1)
			{
				PORTJ=oxFF;
				flag=1;
			}
			i++;
		}
		
		if (flag==0 && i<7) num=atoi(str);
		else num=0;
	}
}
