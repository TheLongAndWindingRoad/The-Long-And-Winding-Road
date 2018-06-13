#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include <d3dx9tex.h>
#include <dinput.h>

#include "UNION.h"
#include "Control.h"
#include "Render.h"
#include "SceneManager.h"

void InitScene(void)
{
	PrevScene = NONE;
	Scene = TITLESCENE;
}

void ControlScene(void)
{
	switch (Scene)
	{
	case TITLESCENE:
		TitleControl();
		break;
	case GAMEMAIN:
		GameMainControl();
		break;
	}
}

void DrawScene(void)
{
	switch (Scene)
	{
	case TITLESCENE:
		TitleDraw();
		break;
	case GAMEMAIN:
		GameMain();
		break;

	}
}

void InitFadeScene( DWORD FadeCol)
{
	SceneFade.Fadeval = 0;
	SceneFade.FadeCnt = FadeCol / 0x1000000;
	SceneFade.FadeCol = FadeCol & 0xffffff;
}

void StartFadeScene(int FadeVal)
{
	SceneFade.Fadeval = FadeVal;
}

