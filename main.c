#include <agb_lib.h>
#include "cursor.h"
#include "cat.h"
int hx,hy,cx,cy,timecnt,randcnt,i,sram,time2,cx2,cy2,cx3,cy3,no,timer;

int main()
{
	sram=LoadInt(0x60);
	Initialize();
	loadSpritePal((void*)cursorPalette);
	loadSpriteGraphics((void*)cursorData, 1024);
	initSprite(1, SIZE_32, 0);
	SetMode(MODE_3|BG2_ENABLE|OBJ_ENABLE|OBJ_MAP_1D);
	fillscreen3(0xFFFF);
	for(i=0;i<sram;i++)
	{
		cx=rand()%208;
		cy=rand()%128;
	}
	cy2=cy-1;
	cx2=cx-1;
	DrawPixel3(cx,cy,0xFFC6);
	FadeIn(2);
	while(1)
	{
		vsync
		CopyOAM();
		MoveSprite(&sprites[1], hx, hy);
		if(keyDown(KEY_LEFT))
		{
			if(NOT(keyDown(KEY_A)))
			{
				hx--;
			}	
		}
		if(keyDown(KEY_RIGHT))
		{
			if(NOT(keyDown(KEY_A)))
			{
				hx++;
			}	
		}
		if(keyDown(KEY_UP))
		{
			if(NOT(keyDown(KEY_A)))
			{
				hy--;
			}	
		}
		if(keyDown(KEY_DOWN))
		{
			if(NOT(keyDown(KEY_A)))
			{
				hy++;
			}	
		}
		if(hx<0)
		{
			hx=0;
		}
		if(hx>223)
		{
			hx=223;
		}
		if(hy<0)
		{
			hy=0;
		}
		if(hy>138)
		{
			hy=138;
		}
		if(((hx==cx)AND(hy==cy))OR((hx==cx2)AND(hy==cy2))OR((hx==cx2)AND(hy==cy))OR((hx==cx)AND(hy==cy2)))
		{
			SetOBJPalPoint(3, us GREEN);
			SetOBJPalPoint(2, us 0x0200);
			if(keyDown(KEY_A))
			{
				loadSpritePal((void*)catPalette);
				loadSpriteGraphics((void*)catData, 1024);
				initSprite(1, SIZE_32, 64);
				MoveSprite(&sprites[1], hx-16, hy-16);
				CopyOAM();
				glideSpritetoPos(1, hx-16, hy-16, 104, 64, 5.00);
				Print(0,32,"PRESS ANY BUTTON TO PLAY AGAIN", BLUE, WHITE);
				while(NOT(KEY_ANY_PRESSED));
				return 0;
			}	
		}else{
			SetOBJPalPoint(3, us RED);
			SetOBJPalPoint(2, us 0x0010);
		}
		Sleep(1);
		timecnt+=4;
		if(timecnt>256)
		{
			time2=timecnt;
			SaveInt(0x60,time2/256+sram);
			timecnt=0;
		}
	}
	return 0;
}