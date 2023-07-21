#include <at89c5131.h>
#include "lcd.h"

sbit start = P1^0;
sbit LED1=P3^6;
int minutes, seconds,upper, lower, dummy[4],i;
unsigned char display_msg[10] = "0123456789", display3[1]=":";

void display(){
	dummy[0] = minutes/10;
	dummy[1] = minutes - 10*(minutes/10);
	dummy[2] = seconds/10;
	dummy[3] = seconds - 10*(seconds/10);
	
	lcd_cmd(0x80);
	msdelay(4);
	for(i = 0; i < 4; i++){
		if(i == 2){
			lcd_write_char(display3[0]);
			lcd_cmd(0x06);
		}
		if(dummy[i] == 0){
			lcd_write_char(display_msg[0]);
			lcd_cmd(0x06);
		}
		else if(dummy[i] == 1){
			lcd_write_char(display_msg[1]);
			lcd_cmd(0x06);
		}
		else if(dummy[i] == 2){
			lcd_write_char(display_msg[2]);
			lcd_cmd(0x06);
		}
		else if(dummy[i] == 3){
			lcd_write_char(display_msg[3]);
			lcd_cmd(0x06);
		}
		else if(dummy[i] == 4){
			lcd_write_char(display_msg[4]);
			lcd_cmd(0x06);
		}
		else if(dummy[i] == 5){
			lcd_write_char(display_msg[5]);
			lcd_cmd(0x06);
		}
		else if(dummy[i] == 6){
			lcd_write_char(display_msg[6]);
			lcd_cmd(0x06);
		}
		else if(dummy[i] == 7){
			lcd_write_char(display_msg[7]);
			lcd_cmd(0x06);
		}
		else if(dummy[i] == 8){
			lcd_write_char(display_msg[8]);
			lcd_cmd(0x06);
		}
		else if(dummy[i] == 9){
			lcd_write_char(display_msg[9]);
			lcd_cmd(0x06);
		}
	}
}

void read(){
	upper = TH0;
	lower = TL0;
	while(upper!=TH0){
  	upper = TH0;
		lower = TL0;
	}
	return;
}
	
void counter(bit start){
	if(start == 0){
		TR0 = 0;
		return;
	}
	else{
		TR0 = 1;
		read();
		minutes = (lower + 256*upper)/3600;
		seconds = ((lower + 256*upper) - (3600*minutes))/60;
		display();
		return;
	}
}

void main(){
	TMOD = 0x05;
	TH0 = 0x00;
	TL0 = 0x00;
	lcd_init();
	while(1){
		counter(start);
	}
}