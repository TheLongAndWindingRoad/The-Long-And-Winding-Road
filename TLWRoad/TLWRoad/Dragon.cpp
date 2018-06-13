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
#include "Dragon.h"
#include "Hero.h"

DragonStatas DState;

static int g_count = 0;
static int g_bcount = 0;

void DragonInit()
{
	DState.Hp = 20;
	DState.Pos_X = 767;
	DState.Pos_Y = 80;
	DState.count = 0;
	DState.revers = true;
	DState.fire = false;

}

void DragonAct(void)
{
	if (!DState.revers)
	{
		DState.Pos_X += CHIP_SW / 15;
	}
	else
	{
		DState.Pos_X -= CHIP_SW / 15;
	}

	if (DState.Pos_X >= 900)
	{
		DState.revers = true;
	}

	if (DState.Pos_X < 600)
	{
		DState.revers = false;
	}

	/*	�����h���S���ƗE�҂�X���W�������Ȃ�ΉΉ��𐁂�
	*	����5�b��ɂ��������Ή��𐁂�
	*/
	/* �����蔻��̎d����ς��� */
	/*
	*	�h���S���̌��݂̍��W���}�b�v�z��ɓ��ěƂ߂Ĕ�������
	*/
	if ((DState.Pos_X) == (HState.Pos_X))
	{
		DState.fire = true;
	}
}

void DrawDragon()
{
	DrawAnime(A_DRADON, DState.Pos_X, DState.Pos_Y + BP.y, 1.0f, 0, 0.0f);
}