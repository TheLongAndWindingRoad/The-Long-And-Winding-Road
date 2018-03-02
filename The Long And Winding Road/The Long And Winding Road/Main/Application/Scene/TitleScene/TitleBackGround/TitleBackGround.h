#ifndef TITLEBACKGROUND_H
#define	TITLEBACKGROUND_H

#include"Main\Object2DBase\object2DBase.h"
#include<Windows.h>

class TitleBackGround : Object2DBase
{
public:
	TitleBackGround();
	~TitleBackGround();
	virtual bool Initialize();
	virtual void Finalize();
	virtual void Update();
	virtual void Draw();
private:

	struct CUSTOMVERTEX
	{
		FLOAT	x, y, z, rhw;
		DWORD	color;
		FLOAT	tu, tv;
	};

	CUSTOMVERTEX m_Title[4];
	float w_Width = 1280;
	float w_Height = 720;
	int m_TitleTexture;
};

#endif