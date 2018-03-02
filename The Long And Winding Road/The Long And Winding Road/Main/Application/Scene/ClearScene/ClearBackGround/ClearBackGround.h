#ifndef CLEARBACKGROUND_H
#define	CLEARBACKGROUND_H

#include"Main\Object2DBase\object2DBase.h"
#include<Windows.h>

class ClearBackGround : public Object2DBase
{
public:
	ClearBackGround();
	~ClearBackGround();
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

	CUSTOMVERTEX m_Clear[4];

	float w_Width;
	float w_Height;
	int m_ClearTexture;
};

#endif