#include <STC89C5xRC.H>

void delay_ms(unsigned int n_ms)
{
	unsigned int i,j;

	for(i=n_ms; i>0; i--)
		for(j=110; j>0; j--)
			;
}

void stop()
{
	P1 = P1 & 0xF0; 
	P2 = P2 & 0xF0;
}

void forward_ms(unsigned int n_ms)
{
	stop(); 
	P1 = P1 | 0x09; 
	P2 = P2 | 0x06;
	delay_ms(n_ms);
	stop();
}

void backward_ms(unsigned int n_ms)
{
	stop(); 
	P1 = P1 | 0x06; 
	P2 = P2 | 0x09;
	delay_ms(n_ms);
	stop();
}

void left_ms(unsigned int n_ms)
{
	stop(); 
	P1 = P1 | 0x0A; 
	P2 = P2 | 0x0A;
	delay_ms(n_ms);
	stop();
}

void right_ms(unsigned int n_ms)
{
	stop(); 
	P1 = P1 | 0x05; 
	P2 = P2 | 0x05;
	delay_ms(n_ms);
	stop();
}

void led_color(char color)
{
	switch (color)
	{
		case 'r':
			P24 = 1;
			P25 = 0;
			P26 = 0;			
			break;
		case 'g':
			P24 = 0;
			P25 = 1;
			P26 = 0;			
			break;
		case 'b':
			P24 = 0;
			P25 = 0;
			P26 = 1;			
			break;
		case 'k':
			P24 = 0;
			P25 = 0;
			P26 = 0;			
			break;
		default:
			P24 = 1;
			P25 = 1;
			P26 = 1;			
			break;
	}
}

void init()
{
	TMOD=0x20;
	TH1=0xfd;
	TL1=0xfd;
	TR1=1;
	REN=1;
	SM0=0;
	SM1=1;	
	EA=1;
	ES=1;	
}

unsigned char flag,a,i;
unsigned char code table[]="\nI get ";

void main()
{

	init();

	while(1)
	{
		if(flag==1)
		{
			ES=0;
			for(i=0;i<7;i++)
			{
				SBUF=table[i];
				while(!TI);
				TI=0;
			}
			SBUF=a;
			while(!TI);
			TI=0;
			ES=1;
			flag=0;

			switch(a)
			{
				case 'F':
					forward_ms(1000);
					led_color('g');
					break;
				case 'B':
					backward_ms(1000);
					led_color('r');
					break;
				case 'L':
					left_ms(360);
					led_color('b');
					break;
				case 'R':
					right_ms(360);
					led_color('b');
					break;
			}
		}
	}
}

void ser() interrupt 4
{
	RI=0;
	a=SBUF;
	flag=1;
}

