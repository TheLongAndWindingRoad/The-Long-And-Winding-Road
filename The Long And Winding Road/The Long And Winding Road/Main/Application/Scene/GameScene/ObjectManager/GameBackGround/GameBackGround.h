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

	/* csv�t�@�C����ǂݍ��ނ��߂̊֐� */ 
	void MapLoad(const char* mapdata,int number);

	/* �w�i�`�� */
	void BackGroundDraw();
	/* ���̕`�� */
	void GrassDraw();

	/* �摜�ԍ���Ԃ��֐� */
	int* GetBackGroundTexture() { return &m_BackGroundTexture; }
	int* GetGrassTexture() { return &m_GrassTexture; }

private:

	struct CUSTOMVERTEX
	{
		FLOAT	x, y, z, rhw;
		DWORD	color;
		FLOAT	tu, tv;
	};

	/* Maptip�̐� */
	static const int Map_Width = 13;
	static const int Map_Height = 26;
	/* �w�i�̑傫�� */
	const float Width  = 650;
	const float Height = 650;
	/* Maptip�̑傫�� */
	const float TipsizeWidth = 50;
	const float TipsizeHeight = 25;

	/* �w�i�̃f�[�^ */
	int map1[Map_Height][Map_Width];
	int map2[Map_Height][Map_Width];
	int map3[Map_Height][Map_Width];

	/* ������10�ɑ��₷ */
	/* Maptip����ǂݍ��񂾃f�[�^�������Ɋi�[���� */
	int Initmap1[Map_Height][Map_Width];
	int Initmap2[Map_Height][Map_Width];
	int Initmap3[Map_Height][Map_Width];

	/* �w�i�̔ԍ� */
	int m_BackGroundTexture;
	/* ���̔ԍ� */
	int m_GrassTexture;

	CUSTOMVERTEX m_BackGround1[4];
	CUSTOMVERTEX m_BackGround2[4];
	CUSTOMVERTEX m_BackGround3[4];
	CUSTOMVERTEX m_Grass1[4];
	CUSTOMVERTEX m_Grass2[4];
	CUSTOMVERTEX m_Grass3[4];
};


#endif