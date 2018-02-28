#include"GameBackGround.h"
#include"DirectX9\TextureManager\TextureManager.h"
#include"DirectX9\DirectGraphics\DirectGraphics.h"
#include<stdio.h>
#include<stdlib.h>

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
		m_BackGround1[i] = BackGround[i];
		m_Grass1[i] = Grass[i];
	}
	return true;
}

void GameBackGround::Finalize()
{

}

void GameBackGround::Update()
{
	for (int i = 0; i < 4; i++)
	{
		m_BackGround1[i].y += 5;
		m_BackGround1[i].y += 5;
		m_BackGround2[i].y += 5;
		m_BackGround2[i].y += 5;
		m_BackGround3[i].y += 5;
		m_BackGround3[i].y += 5;

		m_Grass1[i].y += 5;
		m_Grass1[i].y += 5;
		m_Grass2[i].y += 5;
		m_Grass2[i].y += 5;
		m_Grass3[i].y += 5;
		m_Grass3[i].y += 5;
	}

	if (m_BackGround1[2].y > Height)
	{
		for (int i = 0; i < 4; i++)
		{
			// 問題がある.
			// バルーンの時みたいにはみ出した分を余剰で計算
			m_BackGround1[i].y -= Height * 3;
			m_Grass1[i].y -= Height * 3;

			// マップ初期化
			// バックグラウンドと草に合わせて初期化

		}
	}

	// 2,3でも同じ処理をする




}

void GameBackGround::Draw()
{
	BackGroundDraw();
	GrassDraw();
}

void GameBackGround::MapLoad(const char* mapdata)
{
	FILE*  fp;
	fopen_s(&fp, mapdata, "r");


	for (int i = 0; i < Map_Height; i++)
	{
		for (int j = 0; j < Map_Width; j++)
		{
			fscanf_s(fp, "%d,", &map[i][j], _countof(map));
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
	DirectGraphics::GetInstance()->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_Grass1, sizeof(CUSTOMVERTEX));
	DirectGraphics::GetInstance()->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_Grass2, sizeof(CUSTOMVERTEX));
	DirectGraphics::GetInstance()->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_Grass3, sizeof(CUSTOMVERTEX));
}