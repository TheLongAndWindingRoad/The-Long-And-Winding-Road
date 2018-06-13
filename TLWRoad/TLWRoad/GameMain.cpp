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
#include "Maps.h"
#include "Hero.h"
#include "Dragon.h"

void GameMainInit()
{
	BP.x = 0.0f;
	BP.y = (MAP_H - FH) * CHIP_SH;
	HeroInit();
	DragonInit();
}

int GameMainControl()
{
	BP.y--;
	if (BP.y <= 0)
	{
		BP.y = 0;
	}

	return Scene;
}


int GameMain()
{
	/* “®‚« */
	HeroAct();
	DragonAct();

	/* •`‰æ */
	DrawMaps();
	DrawHero();
	DrawDragon();
	DrawAnime(A_UI, WIN_W/2, WIN_H/2 + BP.y, 1.0f, 0, 0.0f);

	return Scene;

}