#include <at89c5131.h>
#include "lcd.h"

unsigned char password[8]="15A8*D6#";
code unsigned char row0[]="123A";
code unsigned char row1[]="456B";
code unsigned char row2[]="789C";
code unsigned char row3[]="*0#D";
unsigned char pass[8];
char character;

int c, column, d, row, iter=0, b, a, dummy, check,i;


int take_input(){
	a = 0xF0;
	
	while(a != 0x0F){
		a = P3 & 0x0F;
		a = a & 0x0F;
	}
	
	while(a == 0x0F){
		a = P3 & 0x0F;
	}
		
	msdelay(20);
	a = P3 & 0x0F;
	return a;
}

char read(){
	int row_id, column_id;
	char char1;
	row_id = row;
	column_id = column;
	
	if(row == 0){
		char1 = row0[column_id];
	}
	else if(row == 1){
		char1 = row1[column_id];
	}
	else if(row == 2){
		char1 = row2[column_id];
	}
	else{
		char1 = row3[column_id];
	}
	
	return char1;
}

void recognize_key(){
	c = b;
	b = b & 0x07;
	if(b == c){
		column = 0;
	}
		
	b = c;
	b = b & 0x0B;
	if(b == c){
		column = 1;
	}
		
	b = c;
	b = b & 0x0D;
	if(b == c){
		column = 2;
	}
		
	b = c;
	b = b & 0x0E;
	if(b == c){
		column = 3;
	}

	P3_7 = 1;
	P3_6 = 1;
	P3_5 = 1;
	P3_4 = 0;
	d = P3 & 0x0F;
	if(d != 0x0F){
		row = 0;
	}
		
	P3_7 = 1;
	P3_6 = 1;
	P3_5 = 0;
	P3_4 = 1;
	d = P3 & 0x0F;
	if(d != 0x0F){
		row = 1;
	}
		
	P3_7 = 1;
	P3_6 = 0;
	P3_5 = 1;
	P3_4 = 1;
	d = P3 & 0x0F;
	if(d != 0x0F){
		row = 2;
	}
		
	P3_7 = 0;
	P3_6 = 1;
	P3_5 = 1;
	P3_4 = 1;
	d = P3 & 0x0F;
	if(d != 0x0F){
		row = 3;
	}
		
	character = read();
	pass[iter] = character;
	//lcd_cmd(0xC0);
	
	lcd_write_char(character);
	lcd_cmd(0x06);
	dummy = 0;
}
	

void main(){

	lcd_init();
	lcd_cmd(0x80);
	msdelay(4);
	lcd_write_string(" ENTER PASSWORD ");
	msdelay(4);
	lcd_cmd(0xC0);
	P3 = 0x0F;
	a = 0x0F;
	while(a == 0x0F){
		a = P3 & 0x0F;
	}
	
	msdelay(20);
	a = P3 & 0x0F;
	b = a;
	recognize_key();
	
	for(iter = 1; iter < 8; iter++){
		P3 = 0x0F;
		b = take_input();
		
		while(b == 0x0F){
			P3 = 0x0F;
			b = take_input();
		}
		recognize_key();
	}
	check = 0;
	for(i=0;i<8;i++)
	{
		if(pass[i]==password[i])
		{
			check++;
		}	
		else{check=check;}
	}
	if(check == 8){
		lcd_init();
		lcd_cmd(0x80);
		msdelay(4);
		lcd_write_string("Correct Password");
		lcd_cmd(0xC0);
		msdelay(4);
		lcd_write_string(" Access Granted ");
		while(1);
	}
	if(check != 8){
		lcd_init();
		lcd_cmd(0x80);
		msdelay(4);
		lcd_write_string(" Wrong Password ");
		lcd_cmd(0xC0);
		msdelay(4);
		lcd_write_string("  Access Denied ");
		while(1);
	}
}