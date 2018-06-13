#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include <d3dx9tex.h>
#include <dinput.h>
#include <dsound.h>

#include "UNION.h"
#include "MouseControl.h"
#include "Control.h"	//Control.hがRender.hの手前
#include "Render.h"
#include "SceneManager.h"
#include "Maps.h"


/*
*	画面外にあれば描画しないようにする
*	ここでcsvファイルを読み込みField[][]に代入する
*/



void DrawMaps(void)
{
	int i, j;
	float cx, cy;
	float zoom;
	int sidx;
	int bidx;

	bidx = (int)(BP.y / BGH);

	DrawAnime(A_BACKGRAUND, GMAIN_X - CHIP_SW / 2 + BGW / 2, GMAIN_Y - CHIP_SH / 2 + BGH / 2 +  bidx	* BGH, 1.0f, 0, 0.0f);
	DrawAnime(A_BACKGRAUND, GMAIN_X - CHIP_SW / 2 + BGW / 2, GMAIN_Y - CHIP_SH / 2 + BGH / 2 + (bidx+1) * BGH, 1.0f, 0, 0.0f);

	cx = GMAIN_X;
	cy = GMAIN_Y;

	sidx = (int)(BP.y / CHIP_SH) - 1;

	for (i = 0; i < FH + 3; i++, sidx++) 
	{
		for (j = 0; j < FW; j++) 
		{
			if (Field[sidx][j] == 1)
			{
				/* 草 */
				DrawAnime(A_KUSA, cx + j * (CHIP_SW), cy + sidx * (CHIP_SH), 1, 0, 0.0f);
				
			}

			if (Field[sidx][j] == 2)
			{
				/* 武器 */
				DrawAnime(A_BUKI1, cx + j * (CHIP_SW), cy + sidx * (CHIP_SH), 1, 0, 0.0f);

			}
		}
	}
	
}






