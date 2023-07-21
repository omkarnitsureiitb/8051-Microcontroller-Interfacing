#include <at89c5131.h>
#include "lcd.h"

void main(){
	int inputs[5],temp,search,searchindex,found,i,j;
	lcd_init();
	lcd_cmd(0x80);
	msdelay(4);
	P1 = 0x00;
	lcd_write_string("  START PROGRAM ");
	msdelay(5000);
	
	lcd_init();
	lcd_cmd(0x80);
	msdelay(4);
	P1 = 0x0F;
	lcd_write_string("   FIRST INPUT  ");
	
	msdelay(5000);
	inputs[0] = P1;
	P1 = P1*16;
	msdelay(5000);
	P1 = 0x00;
	msdelay(1000);

	lcd_init();
	lcd_cmd(0x80);
	msdelay(4);
	P1 = 0x0F;
	lcd_write_string("   NEXT INPUT   ");
	msdelay(5000);
	inputs[1] = P1;
	P1 = P1*16;
	msdelay(5000);
	P1 = 0x00;
	msdelay(1000);
	
	lcd_init();
	lcd_cmd(0x80);
	msdelay(4);
	P1 = 0x0F;
	lcd_write_string("   NEXT INPUT   ");
	msdelay(5000);
	inputs[2] = P1;
	P1 = P1*16;
	msdelay(5000);
	P1 = 0x00;
	msdelay(1000);
	
	lcd_init();
	lcd_cmd(0x80);
	msdelay(4);
	P1 = 0x0F;
	lcd_write_string("   NEXT INPUT   ");
	msdelay(5000);
	inputs[3] = P1;
	P1 = P1*16;
	msdelay(5000);
	P1 = 0x00;
	msdelay(1000);
	
	lcd_init();
	lcd_cmd(0x80);
	msdelay(4);
	P1 = 0x0F;
	lcd_write_string("   NEXT INPUT   ");
	msdelay(5000);
	inputs[4] = P1;
	P1 = P1*16;
	lcd_init();
	lcd_cmd(0x80);
	msdelay(4);
	lcd_write_string("   SORTING...   ");
	msdelay(5000);
	
	lcd_init();
	lcd_cmd(0x80);
	msdelay(4);
	lcd_write_string("     SORTING    ");
	lcd_cmd(0xC0);
	msdelay(4);
	P1 = 0x00;
	lcd_write_string("    COMPLETED   ");
	msdelay(1000);
	
	for(i=1;i<6;i++)
	{
		for(j=0;j<4;j++)
		{
			if(inputs[j] > inputs[j+1])
			{
				temp = inputs[j];
				inputs[j] = inputs[j+1];
				inputs[j+1] = temp;
			}
		}
	}
	
	for(i=0;i<5;i++)
	{
		P1 = 16*inputs[i];
		msdelay(5000);
		P1 = 0x00;
		msdelay(1000);
	}
	
	P1 = 0xFF;
	lcd_init();
	lcd_cmd(0x80);
	msdelay(4);
	lcd_write_string("  NUMBER TO BE  ");
	lcd_cmd(0xC0);
	msdelay(4);
	lcd_write_string("    SEARCHED    ");
	msdelay(5000);
	P1 = P1*16;
	P1 = P1/16;
	
	search = P1;
	P1 = 0x00;
	lcd_init();
	msdelay(1000);
	
	found = 0;
	for(i=0;i<5;i++)
	{
		if(inputs[i] == search)
		{
			found = 1;
			searchindex = i;
		}
	}
	
	if(found)
	{
		P1 = 16*(searchindex+1);
		lcd_init();
		lcd_cmd(0x80);
		msdelay(4);
		lcd_write_string("   THE INDEX IS  ");
		msdelay(5000);
	}
	
	if(!found)
	{
		P1 = 0xF0;
		lcd_init();
		lcd_cmd(0x80);
		msdelay(4);
		lcd_write_string("     NUMBER     ");
		lcd_cmd(0xC0);
		msdelay(4);
		lcd_write_string("    NOT FOUND   ");
		msdelay(5000);
	}
	while(1);
}