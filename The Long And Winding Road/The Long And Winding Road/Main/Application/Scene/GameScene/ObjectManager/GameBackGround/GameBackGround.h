#ifndef GAMEBACKGROUND_H
#define	GAMEBACKGROUND_H

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
private:

};


#endif