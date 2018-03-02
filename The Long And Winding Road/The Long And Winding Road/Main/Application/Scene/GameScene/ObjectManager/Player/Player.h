#ifndef PLAYER_H
#define	PLAYER_H

#include "Main\Object2DBase\object2DBase.h"

class Player:public Object2DBase
{
public:
	Player();
	virtual ~Player();
	virtual bool Initalize();
	virtual void Finalize();
	virtual void Update();
	virtual void Draw();
private:

};
#endif