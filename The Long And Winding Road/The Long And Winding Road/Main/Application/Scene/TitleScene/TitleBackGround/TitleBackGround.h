#ifndef TITLEBACKGROUND_H
#define	TITLEBACKGROUND_H

#include"Main\Object2DBase\object2DBase.h"

class TitleBackGround : Object2DBase
{
public:
	TitleBackGround();
	~TitleBackGround();
	virtual bool Initialize();
	virtual void Finalize();
	virtual void Update();
	virtual void Draw();
};

#endif