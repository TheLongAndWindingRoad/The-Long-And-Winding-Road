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
	void MapLoad(const char* mapdata);

	void BackGroundDraw();
	void GrassDraw();

	int* GetBackGroundTexture() { return &m_BackGroundTexture; }
	int* GetGrassTexture() { return &m_GrassTexture; }

private:

	struct CUSTOMVERTEX
	{
		FLOAT	x, y, z, rhw;
		DWORD	color;
		FLOAT	tu, tv;
	};

	static const int Map_Width = 11;
	static const int Map_Height = 22;
	const float Width = 550;
	const float Height = 550;
	const float TipsizeWidth = 50;
	const float TipsizeHeight = 25;
	int map[Map_Height][Map_Width];

	int m_BackGroundTexture;
	int m_GrassTexture;

	CUSTOMVERTEX m_BackGround1[4];
	CUSTOMVERTEX m_BackGround2[4];
	CUSTOMVERTEX m_BackGround3[4];
	CUSTOMVERTEX m_Grass1[4];
	CUSTOMVERTEX m_Grass2[4];
	CUSTOMVERTEX m_Grass3[4];
};


#endif