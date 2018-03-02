#ifndef OVERBACKGROUND_H
#define	OVERBACKGROUND_H

#include<Windows.h>
#include"Main\Object2DBase\object2DBase.h"

class OverBackGround : public Object2DBase
{
public:
	OverBackGround();
	~OverBackGround();
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

	CUSTOMVERTEX m_Over[4];

	float w_Width;
	float w_Height;
	int m_OverTexture;
};

#endif