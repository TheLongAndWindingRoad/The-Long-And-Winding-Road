#include <windows.h>
#include <d3dx9.h>
#include <d3dx9tex.h>
#include <dinput.h>
#include <dsound.h>

#include "UNION.h"
#include "Control.h"
#include "Render.h"
#include "MouseControl.h"

#include "SceneManager.h"
#include"Maps.h"

/* 使ってない ( ´∀｀ )/ */
void TitleInit()
{
	BP.x = 0.0f;
	BP.y = (MAP_H - FH) * CHIP_SH;
}

int TitleControl()
{
	if (MouseState.rgbButtons[0] & 0x80)
	{
		/* タイトル文字に当たっていたらにする */
		Scene = GAMEMAIN;
	}

	return Scene;
}

void TitleDraw()
{
	DrawAnime(A_UI, WIN_W / 2, WIN_H / 2 + BP.y, 1.0f, 0, 0.0f);
	int bidx;
	int bidx2;
	bidx = (int)(BP.y / BGH);
	bidx2 = bidx + 1;
	DrawAnime(A_BACKGRAUND, GMAIN_X - CHIP_SW / 2 + BGW / 2, GMAIN_Y - CHIP_SH / 2 + BGH / 2 + bidx  * BGH, 1.0f, 0, 0.0f);
	DrawAnime(A_BACKGRAUND, GMAIN_X - CHIP_SW / 2 + BGW / 2, GMAIN_Y - CHIP_SH / 2 + BGH / 2 + bidx2 * BGH, 1.0f, 0, 0.0f);
	DrawAnime(A_TITLE, WIN_W / 2, WIN_H / 2 + BP.y, 1.0f, 0, 0.0f);

}