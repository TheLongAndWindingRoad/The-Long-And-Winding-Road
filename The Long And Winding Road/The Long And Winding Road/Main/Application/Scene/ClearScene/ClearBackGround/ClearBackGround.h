#ifndef CLEARBACKGROUND_H
#define	CLEARBACKGROUND_H

#include"Main\Object2DBase\object2DBase.h"

class ClearBackGround : public Object2DBase
{
public:
	ClearBackGround();
	~ClearBackGround();
	virtual bool Initialize();
	virtual void Finalize();
	virtual void Update();
	virtual void Draw();
};

#endif