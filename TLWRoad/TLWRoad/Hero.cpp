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
#include "Hero.h"

HeroStatas HState;

void HeroInit()
{
	
	HState.Hp = 3;
	HState.Pos_X = 787;
	HState.Pos_Y = 566;
	HState.hub = false;

}

void HeroAct(void)
{
	/*
	*	足元の座標をサイズで割って割りだして左(-1)と右(+1)をみて0やったら動かす
	*/
	static bool MEFlag = true;
	static int py = 0;
	/*  勇者の足元　*/
	int x = ((HState.Pos_X - GMAIN_X) / CHIP_SW);
	int y = (((HState.Pos_Y + BP.y + 60 - GMAIN_Y)) / CHIP_SH);


	if (MEFlag && x > 0 && (Field[y][x - 1]) == 0)
	{
		HState.Pos_X -= CHIP_SW * 2;
		py = y;
		MEFlag = false;
	}

	if (MEFlag && x < FW - 1 && (Field[y][x + 1]) == 0)
	{
		HState.Pos_X += CHIP_SW * 2;
		py = y;
		MEFlag = false;
	}
	if (py != y)
	{
		MEFlag = true;
	}

	/*
	*	武器との判定
	*
	*	//武器を持っている状態で武器を取るとどうなるのか？
	*/
	if ((Field[y - 1][x]) == 2)
	{
		Field[y - 1][x] = 0;
		HState.hub = true;
	}


	/*
	*	草狩りのカウントをもう少しわかりやすく
	*	ていうか最初の回数を三回にしてそこから減らしていけよ
	*/

	/* マウスと草との判定 */
	static int cutcount = 0;
	static int cuttime = 0;
	cuttime++;

	if (MouseState.rgbButtons[0] & 0x80)
	{
		/* マウスの位置をMap座標に置き換えている */
		int mx = ((Mx - GMAIN_X) / CHIP_SW);
		int my = (((My + BP.y - GMAIN_Y)) / CHIP_SH);

		if (cutcount < 3 && Field[my][mx] == 1)
		{
			Field[my][mx] = 0;
			cutcount++;
		}
	}

	/* 時間経過で草狩り数回復 */
	if (cuttime == 600)
	{
		cutcount -= 1;
	}

	/* 回復し過ぎないように */
	if (cutcount <= 0)
	{
		cutcount = 0;
	}
}

void DrawHero()
{
	if (HState.hub)
	{
		DrawAnime(A_HERO1_F3, HState.Pos_X, HState.Pos_Y + BP.y, 1.0f, 0, 0.0f);
	}
	else
	{
		DrawAnime(A_HERO1_F1, HState.Pos_X, HState.Pos_Y + BP.y, 1.0f, 0, 0.0f);
	}
}