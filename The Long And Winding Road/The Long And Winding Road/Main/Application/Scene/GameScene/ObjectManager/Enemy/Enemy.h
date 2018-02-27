#ifndef ENEMY_H
#define	ENEMY_H

#include"Main\Object2DBase\object2DBase.h"

class Enemy:public Object2DBase
{
public:
	Enemy();
	virtual ~Enemy();
	virtual bool Initalize();
	virtual void Finalize();
	virtual void Update();
	virtual void Draw();
private:

};

#endif