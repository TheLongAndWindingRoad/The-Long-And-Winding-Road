#ifndef GAMEBACKGROUND_H
#define	GAMEBACKGROUND_H

#include<Windows.h>
#include"Main\Object2DBase\object2DBase.h"

class GameBackGround:public Object2DBase
{
public:

	GameBackGround();
	virtual ~GameBackGround();
	virtual bool Initalize();
	virtual void Finalize();
	virtual void Update();
	virtual void Draw();

	/* csvファイルを読み込むための関数 */ 
	void MapLoad(const char* mapdata,int number);

	/* 背景描画 */
	void BackGroundDraw();
	/* 草の描画 */
	void GrassDraw();

	/* 画像番号を返す関数 */
	int* GetBackGroundTexture() { return &m_BackGroundTexture; }
	int* GetGrassTexture() { return &m_GrassTexture; }

private:

	struct CUSTOMVERTEX
	{
		FLOAT	x, y, z, rhw;
		DWORD	color;
		FLOAT	tu, tv;
	};

	/* Maptipの数 */
	static const int Map_Width = 13;
	static const int Map_Height = 26;
	/* 背景の大きさ */
	const float Width  = 650;
	const float Height = 650;
	/* Maptipの大きさ */
	const float TipsizeWidth = 50;
	const float TipsizeHeight = 25;

	/* 背景のデータ */
	int map1[Map_Height][Map_Width];
	int map2[Map_Height][Map_Width];
	int map3[Map_Height][Map_Width];

	/* Maptipから読み込んだデータをここに格納する */
	int Initmap1[Map_Height][Map_Width];
	int Initmap2[Map_Height][Map_Width];
	int Initmap3[Map_Height][Map_Width];

	/* 背景の番号 */
	int m_BackGroundTexture;
	/* 草の番号 */
	int m_GrassTexture;

	CUSTOMVERTEX m_BackGround1[4];
	CUSTOMVERTEX m_BackGround2[4];
	CUSTOMVERTEX m_BackGround3[4];
	CUSTOMVERTEX m_Grass1[4];
	CUSTOMVERTEX m_Grass2[4];
	CUSTOMVERTEX m_Grass3[4];
};


#endif