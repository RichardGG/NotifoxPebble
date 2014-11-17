#pragma once
#include "pebble.h"

#define CACHE_SIZE 4
#define TITLE_SIZE 100
#define ICON_SIZE 384
#define ICON_ROW_SIZE 8
	
char title[CACHE_SIZE][TITLE_SIZE];

static GBitmap icon[CACHE_SIZE];
static uint8_t icon_data[CACHE_SIZE][ICON_SIZE];



void create_bitmaps(){
	for(int i=0; i<CACHE_SIZE; i++){	
		icon[i] = (GBitmap){.addr=icon_data[i], .bounds = GRect(0,0,48,48), .row_size_bytes = ICON_ROW_SIZE,};
	}
}

static void set_icon_bit(int icon_no, int x, int y, char value)
{
	int byte = (x*ICON_ROW_SIZE)+(y/8);
	
	if(value == 0)
		icon_data[icon_no][byte] &= ~(1 << (y%8));
	else
		icon_data[icon_no][byte] |=   1 << (y%8) ;
}

void clear_data(int icon_no){
	for(int x = 0; x < 48; x++){
		for(int y = 0; y < 48; y++){
			//if(x > 4 && x < 44 && y > 4 && y < 44)
			//	set_icon_bit(icon_no,x,y,1);
			//else
				set_icon_bit(icon_no,x,y,0);
		}
	}
}

