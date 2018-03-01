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

	/* csvƒtƒ@ƒCƒ‹‚ğ“Ç‚İ‚Ş‚½‚ß‚ÌŠÖ” */ 
	void MapLoad(const char* mapdata,int number);

	/* ”wŒi•`‰æ */
	void BackGroundDraw();
	/* ‘‚Ì•`‰æ */
	void GrassDraw();

	/* ‰æ‘œ”Ô†‚ğ•Ô‚·ŠÖ” */
	int* GetBackGroundTexture() { return &m_BackGroundTexture; }
	int* GetGrassTexture() { return &m_GrassTexture; }

private:

	struct CUSTOMVERTEX
	{
		FLOAT	x, y, z, rhw;
		DWORD	color;
		FLOAT	tu, tv;
	};

	/* Maptip‚Ì” */
	static const int Map_Width = 13;
	static const int Map_Height = 26;
	/* ”wŒi‚Ì‘å‚«‚³ */
	const float Width  = 650;
	const float Height = 650;
	/* Maptip‚Ì‘å‚«‚³ */
	const float TipsizeWidth = 50;
	const float TipsizeHeight = 25;

	/* ”wŒi‚Ìƒf[ƒ^ */
	int map1[Map_Height][Map_Width];
	int map2[Map_Height][Map_Width];
	int map3[Map_Height][Map_Width];

	/* ‚±‚±‚ğ10ŒÂ‚É‘‚â‚· */
	/* Maptip‚©‚ç“Ç‚İ‚ñ‚¾ƒf[ƒ^‚ğ‚±‚±‚ÉŠi”[‚·‚é */
	int Initmap1[Map_Height][Map_Width];
	int Initmap2[Map_Height][Map_Width];
	int Initmap3[Map_Height][Map_Width];

	/* ”wŒi‚Ì”Ô† */
	int m_BackGroundTexture;
	/* ‘‚Ì”Ô† */
	int m_GrassTexture;

	CUSTOMVERTEX m_BackGround1[4];
	CUSTOMVERTEX m_BackGround2[4];
	CUSTOMVERTEX m_BackGround3[4];
	CUSTOMVERTEX m_Grass1[4];
	CUSTOMVERTEX m_Grass2[4];
	CUSTOMVERTEX m_Grass3[4];
};


#endif