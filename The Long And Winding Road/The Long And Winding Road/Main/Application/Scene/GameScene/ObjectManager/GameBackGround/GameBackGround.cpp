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

bool GameBackGround::Initalize()
{

	CUSTOMVERTEX BackGround[]
	{
		{ 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ Width, 0.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ Width, Height, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ 0.f, Height, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
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
		/* 初期化の時のx,y座標が全部同じでいいのか */
		/* y座標はずらす */
		m_BackGround1[i] = BackGround[i];
		m_BackGround2[i] = BackGround[i];
		m_BackGround3[i] = BackGround[i];
		/* 草の位置は別に変えなくてもいい */
		m_Grass1[i] = Grass[i];
		m_Grass2[i] = Grass[i];
		m_Grass3[i] = Grass[i];
	}

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

	/* 下まで行った時の処理 */
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
				/* 乱数 */
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
				}
			}
		}
	}

	// 2,3でも同じ処理をする
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
				}
			}
		}
	}

	/* マウスとMaptipの当たり判定 */
	MOUSEKIND mouse;
	MouseDevice::GetpInstance()->MouseCheck(&mouse);
	int mouse_x = MouseDevice::GetpInstance()->GetMousePos().x / TipsizeWidth;
	int mouse_y = MouseDevice::GetpInstance()->GetMousePos().y / TipsizeHeight;

	/* カーソルが1,2,3の何処にいるか確認する */
	if ((mouse_y > m_BackGround1[0].y) && (mouse_y < m_BackGround1[2].y))
	{
		/* ここの0もみて草かどうかわかるように */
		if (map1[mouse_y][mouse_x] == 0)
		{
			map1[mouse_y][mouse_x] = 1;
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

	int i = number;

	for (int i = 0; i < Map_Height; i++)
	{
		for (int j = 0; j < Map_Width; j++)
		{
			switch (i)
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