#ifndef OVERBACKGROUND_H
#define	OVERBACKGROUND_H

#include"Main\Object2DBase\object2DBase.h"

class OverBackGround : public Object2DBase
{
public:
	OverBackGround(int sceneId);
	~OverBackGround();
	virtual bool Initialize();
	virtual void Finalize();
	virtual void Update();
	virtual void Draw();
};

#endif