#include "GameBackGround.h"
#include "DirectX9\TextureManager\TextureManager.h"
#include "DirectX9\DirectGraphics\DirectGraphics.h"
#include "Main\Application\MouseDevice\MouseDevice.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/* 画像の読み込みは統合ならばApp、一つ一つならばここで */

GameBackGround::GameBackGround()
{
}

GameBackGround::~GameBackGround()
{
}

bool GameBackGround::Initialize()
{

	CUSTOMVERTEX BackGround1[]
	{
		{	0.f,	-Height, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ Width,	-Height, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ Width,	0.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{	0.f,	0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	/* 最初に画面が表示される */
	CUSTOMVERTEX BackGround2[]
	{
		{	0.f,	0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ Width,	0.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ Width, Height, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{	0.f, Height, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX BackGround3[]
	{
		{	0.f,	Height, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ Width,	Height, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ Width,	Height + Height, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{	0.f,	Height + Height, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX Grass[]
	{
		{		   0.f,  0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ TipsizeWidth,  0.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ TipsizeWidth, TipsizeHeight, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{		   0.f, TipsizeHeight, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	for (int i = 0; i < 4; i++)
	{
		m_BackGround1[i] = BackGround1[i];
		m_BackGround2[i] = BackGround2[i];
		m_BackGround3[i] = BackGround3[i];
		/* 草の位置は別に変えなくてもいい */
		m_Grass1[i] = Grass[i];
		m_Grass2[i] = Grass[i];
		m_Grass3[i] = Grass[i];
	}

	TextureManager::GetInstance()->LoadTexture("Texture//haikei.png", &m_BackGroundTexture);
	TextureManager::GetInstance()->LoadTexture("Texture//kusa.png", &m_GrassTexture);

	MapLoad("csv//csv1.csv",  1);
	MapLoad("csv//csv2.csv",  2);
	MapLoad("csv//csv3.csv",  3);
	MapLoad("csv//csv4.csv",  4);
	MapLoad("csv//csv5.csv",  5);
	MapLoad("csv//csv6.csv",  6);
	MapLoad("csv//csv7.csv",  7);
	MapLoad("csv//csv8.csv",  8);
	MapLoad("csv//csv9.csv",  9);
	MapLoad("csv//csv10.csv",10);

	return true;
}

void GameBackGround::Finalize()
{

}

void GameBackGround::Update()
{
	/* スクロールの処理 */
	for (int i = 0; i < 4; i++)
	{
		m_BackGround1[i].y += 5;
		m_BackGround2[i].y += 5;
		m_BackGround3[i].y += 5;
	}

	/* 画面下まで行った時の処理 */
	if (m_BackGround1[2].y > Height)
	{
		/* 余剰分の数字を入れている */
		float tmp;

		for (int i = 0; i < 4; i++)
		{
			m_BackGround1[i].y -= Height * 3 + modff(m_BackGround1[2].y, &tmp);
		}

		srand((unsigned)time(NULL));
		int r = rand() % 3 + 1;

		for (int i = 0; i < Map_Height; i++)
		{
			for (int j = 0; j < Map_Width; j++)
			{
				/* 落ちてくるmapをランダムにしている */
				switch (r)
				{
				case 1:
					map1[i][j] = Initmap1[i][j];
					break;
				case 2:
					map1[i][j] = Initmap2[i][j];
					break;
				case 3:
					map1[i][j] = Initmap3[i][j];
					break;
				case 4:
					map1[i][j] = Initmap4[i][j];
					break;
				case 5:
					map1[i][j] = Initmap5[i][j];
					break;
				case 6:
					map1[i][j] = Initmap6[i][j];
					break;
				case 7:
					map1[i][j] = Initmap7[i][j];
					break;
				case 8:
					map1[i][j] = Initmap8[i][j];
					break;;
				case 9:
					map1[i][j] = Initmap9[i][j];
					break;
				case 10:
					map1[i][j] = Initmap10[i][j];
					break;
				}
			}
		}
	}

	if (m_BackGround2[2].y > Height)
	{
		float tmp;

		for (int i = 0; i < 4; i++)
		{
			m_BackGround2[i].y -= Height * 3 + modff(m_BackGround2[2].y, &tmp);
		}

		srand((unsigned)time(NULL));
		int r = rand() % 3 + 1;

		for (int i = 0; i < Map_Height; i++)
		{
			for (int j = 0; j < Map_Width; j++)
			{
				switch (r)
				{
				case 1:
					map2[i][j] = Initmap1[i][j];
					break;
				case 2:
					map2[i][j] = Initmap2[i][j];
					break;
				case 3:
					map2[i][j] = Initmap3[i][j];
					break;
				case 4:
					map2[i][j] = Initmap4[i][j];
					break;
				case 5:
					map2[i][j] = Initmap5[i][j];
					break;
				case 6:
					map2[i][j] = Initmap6[i][j];
					break;
				case 7:
					map2[i][j] = Initmap7[i][j];
					break;
				case 8:
					map2[i][j] = Initmap8[i][j];
					break;;
				case 9:
					map2[i][j] = Initmap9[i][j];
					break;
				case 10:
					map2[i][j] = Initmap10[i][j];
					break;
				}
			}
		}
	}

	if (m_BackGround3[2].y > Height)
	{
		float tmp;

		for (int i = 0; i < 4; i++)
		{
			m_BackGround3[i].y -= Height * 3 + modff(m_BackGround3[2].y, &tmp);
		}

		srand((unsigned)time(NULL));
		int r = rand() % 3 + 1;

		for (int i = 0; i < Map_Height; i++)
		{
			for (int j = 0; j < Map_Width; j++)
			{
				switch (r)
				{
				case 1:
					map3[i][j] = Initmap1[i][j];
					break;
				case 2:
					map3[i][j] = Initmap2[i][j];
					break;
				case 3:
					map3[i][j] = Initmap3[i][j];
					break;
				case 4:
					map3[i][j] = Initmap4[i][j];
					break;
				case 5:
					map3[i][j] = Initmap5[i][j];
					break;
				case 6:
					map3[i][j] = Initmap6[i][j];
					break;
				case 7:
					map3[i][j] = Initmap7[i][j];
					break;
				case 8:
					map3[i][j] = Initmap8[i][j];
					break;;
				case 9:
					map3[i][j] = Initmap9[i][j];
					break;
				case 10:
					map3[i][j] = Initmap10[i][j];
					break;
				}
			}
		}
	}

	/* マウスとMaptipの当たり判定 */
	MOUSEKIND mouse;
	MouseDevice::GetpInstance()->MouseCheck(&mouse);

	if (mouse.IsLeftClick)
	{
		/* ここは切り捨てて大丈夫なのか */
		int mouse_x = MouseDevice::GetpInstance()->GetMousePos().x / TipsizeWidth;
		int mouse_y = MouseDevice::GetpInstance()->GetMousePos().y / TipsizeHeight;

		/* カーソルが1,2,3の何処にいるか確認する */
		/* map1 */
		if ((mouse_y > m_BackGround1[0].y) && (mouse_y < m_BackGround1[2].y))
		{
			if (map1[mouse_y][mouse_x] == Grass)
			{
				map1[mouse_y][mouse_x] = road;
			}
		}

		/* map2 */
		if ((mouse_y > m_BackGround2[0].y) && (mouse_y < m_BackGround2[2].y))
		{
			if (map2[mouse_y][mouse_x] == Grass)
			{
				map2[mouse_y][mouse_x] = road;
			}
		}

		/* map3 */
		if ((mouse_y > m_BackGround3[0].y) && (mouse_y < m_BackGround3[2].y))
		{
			if (map3[mouse_y][mouse_x] == Grass)
			{
				map3[mouse_y][mouse_x] = road;
			}
		}
	}
}

void GameBackGround::Draw()
{
	BackGroundDraw();
	GrassDraw();
}

void GameBackGround::MapLoad(const char* mapdata,int number)
{
	FILE*  fp;
	fopen_s(&fp, mapdata, "r");

	int num = number;

	for (int i = 0; i < Map_Height; i++)
	{
		for (int j = 0; j < Map_Width; j++)
		{
			switch (num)
			{
			case 1:
				fscanf_s(fp, "%d,", &Initmap1[i][j], _countof(map1));
				for (int i = 0; i < Map_Height; i++)
				{
					for (int j = 0; j < Map_Width; j++)
					{
						map1[i][j] = Initmap1[i][j];
					}
				}
				break;
			case 2:
				fscanf_s(fp, "%d,", &Initmap2[i][j], _countof(map2));
				for (int i = 0; i < Map_Height; i++)
				{
					for (int j = 0; j < Map_Width; j++)
					{
						map2[i][j] = Initmap2[i][j];
					}
				}
				break;
			case 3:
				fscanf_s(fp, "%d,", &Initmap3[i][j], _countof(map3));
				for (int i = 0; i < Map_Height; i++)
				{
					for (int j = 0; j < Map_Width; j++)
					{
						map3[i][j] = Initmap3[i][j];
					}
				}
				break;
			case 4:
				fscanf_s(fp, "%d,", &Initmap4[i][j], _countof(map3));
				break;
			case 5:
				fscanf_s(fp, "%d,", &Initmap5[i][j], _countof(map3));
				break;
			case 6:
				fscanf_s(fp, "%d,", &Initmap6[i][j], _countof(map3));
				break;
			case 7:
				fscanf_s(fp, "%d,", &Initmap7[i][j], _countof(map3));
				break;
			case 8:
				fscanf_s(fp, "%d,", &Initmap8[i][j], _countof(map3));
				break;
			case 9:
				fscanf_s(fp, "%d,", &Initmap9[i][j], _countof(map3));
				break;
			case 10:
				fscanf_s(fp, "%d,", &Initmap10[i][j], _countof(map3));
				break;
			}
		}
	}
	fclose(fp);
}

void GameBackGround::BackGroundDraw()
{
	TextureManager::GetInstance()->SetTexture(m_BackGroundTexture);
	DirectGraphics::GetInstance()->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_BackGround1, sizeof(CUSTOMVERTEX));
	DirectGraphics::GetInstance()->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_BackGround2, sizeof(CUSTOMVERTEX));
	DirectGraphics::GetInstance()->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_BackGround3, sizeof(CUSTOMVERTEX));
}

void GameBackGround::GrassDraw()
{
	TextureManager::GetInstance()->SetTexture(m_GrassTexture);

	for (int i = 0; i < Map_Width; i++)
	{
		for (int j = 0; j < Map_Height; j++)
		{
			CUSTOMVERTEX maptip[4];
			switch (map1[j][i])
			{
			case 0:
				for (int k = 0; k < 4; k++)
				{
					maptip[k] = m_Grass1[k];
					maptip[k].x = TipsizeWidth  * i;
					maptip[k].y = TipsizeHeight * j;
					maptip[k].y += m_BackGround1[0].y;
				}
				DirectGraphics::GetInstance()->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, maptip, sizeof(CUSTOMVERTEX));
				break;
			}

			switch (map2[j][i])
			{
			case 0:
				for (int k = 0; k < 4; k++)
				{
					maptip[k] = m_Grass2[k];
					maptip[k].x = TipsizeWidth  * i;
					maptip[k].y = TipsizeHeight * j;
					maptip[k].y += m_BackGround2[0].y;
				}
				DirectGraphics::GetInstance()->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, maptip, sizeof(CUSTOMVERTEX));
				break;
			}
			
			switch (map3[j][i])
			{
			case 0:
				for (int k = 0; k < 4; k++)
				{
					maptip[k] = m_Grass3[k];
					maptip[k].x = TipsizeWidth  * i;
					maptip[k].y = TipsizeHeight * j;
					maptip[k].y += m_BackGround3[0].y;
				}
				DirectGraphics::GetInstance()->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, maptip, sizeof(CUSTOMVERTEX));
				break;
			}
		}
	}
}