#include <REG_MPC82G516.H>

void delay();
void send(unsigned char);

void main() {
	unsigned char c;
	
	TMOD = 0x20;
	PCON &= 0xFF;
	TH1 = 0xF3;
	TL1 = 0xF3;
	TR1 = 1;
	
	SCON = 0xD0;
	while(1) {
		for(c = 'a'; c <= 'z'; c++)
			send(c);
		for(c = 'A'; c <= 'Z'; c++)
			send(c);
	}
}

void send(unsigned char c) {
	TI = 0;
	SBUF = c;
	delay();
	
	while(!TI);
}

void delay() {
	unsigned short i = 250000;
	while(i--);
}
