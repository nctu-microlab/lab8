#include <REG_MPC82G516.H>

void delay();
void send(const unsigned char *);
unsigned char recv();

unsigned char *dict[26] = {0};

void main() {
	unsigned char c;
	dict['Q' - 'A'] = "QAQ";
	dict['W' - 'A'] = "wwwww";
	dict['E' - 'A'] = "NCTU";
	dict['R' - 'A'] = "CSIE";
	
	T2CON = 0x34;
	PCON &= 0xFF;
	TH2 = 0xFF;
	TL2 = 0xD9;
	RCAP2H = 0xFF;
	RCAP2L = 0xD9;
	TR2 = 1;
	
	SCON = 0xD0;
	while(1) {
		c = recv();
		c &= (255-32);
		c -= 'A';
		
		send(dict[c]);
	}
}

unsigned char recv() {
	RI = 0;
	delay();
	
	while(!RI);
	return SBUF;
}

void send(const unsigned char *str) {
	if(!str)
		return;
	
	while(*str) {
		TI = 0;
		SBUF = *str;
		delay();
		
		while(!TI);
		++str;
	}
}

void delay() {
	unsigned short i = 250000;
	while(i--);
}
