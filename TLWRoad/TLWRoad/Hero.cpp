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
#include "Control.h"	//Control.h��Render.h�̎�O
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
	*	�����̍��W���T�C�Y�Ŋ����Ċ��肾���č�(-1)�ƉE(+1)���݂�0������瓮����
	*/
	static bool MEFlag = true;
	static int py = 0;
	/*  �E�҂̑����@*/
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
	*	����Ƃ̔���
	*
	*	//����������Ă����Ԃŕ�������Ƃǂ��Ȃ�̂��H
	*/
	if ((Field[y - 1][x]) == 2)
	{
		Field[y - 1][x] = 0;
		HState.hub = true;
	}


	/*
	*	�����̃J�E���g�����������킩��₷��
	*	�Ă������ŏ��̉񐔂��O��ɂ��Ă������猸�炵�Ă�����
	*/

	/* �}�E�X�Ƒ��Ƃ̔��� */
	static int cutcount = 0;
	static int cuttime = 0;
	cuttime++;

	if (MouseState.rgbButtons[0] & 0x80)
	{
		/* �}�E�X�̈ʒu��Map���W�ɒu�������Ă��� */
		int mx = ((Mx - GMAIN_X) / CHIP_SW);
		int my = (((My + BP.y - GMAIN_Y)) / CHIP_SH);

		if (cutcount < 3 && Field[my][mx] == 1)
		{
			Field[my][mx] = 0;
			cutcount++;
		}
	}

	/* ���Ԍo�߂ő���萔�� */
	if (cuttime == 600)
	{
		cutcount -= 1;
	}

	/* �񕜂��߂��Ȃ��悤�� */
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