#include <REG_MPC82G516.H>
#include <stdio.h>

void delay();
void send(unsigned char);

void main() {	
	unsigned char switch_value = 0;
	
	IE = 0x90;
	T2CON = 0x34;
	PCON &= 0xFF;
	TH2 = 0xFF;
	TL2 = 0xD9;
	RCAP2H = 0xFF;
	RCAP2L = 0xD9;
	TR2 = 1;
	
	SCON = 0xD0;
	while(1) {
		P2 = 0xFF;
		if(P2 != switch_value) {
			switch_value = P2;
			P1 = switch_value;
			send(~switch_value);
		}
	}
}

void recv() interrupt 4 {
	if(RI == 1) {
		P1 = ~SBUF;
		RI = 0;
	}
}

unsigned char hex_table[16] = {
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

void send(unsigned char d) {	
	TI = 0;
	SBUF = hex_table[d >> 4];
	delay();
	while(!TI);
	
	TI = 0;
	SBUF = hex_table[d & 0x0F];
	delay();
	while(!TI);
}

void delay() {
	unsigned short i = 2500;
	while(i--);
}
