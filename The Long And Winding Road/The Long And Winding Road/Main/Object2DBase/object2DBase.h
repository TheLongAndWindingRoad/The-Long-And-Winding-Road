#ifndef OBJECT2DBASE_H
#define	OBJECT2DBASE_H

#include"DirectX9\ObjectBase\ObjectBase.h"

class Object2DBase:public ObjectBase
{
public:
	Object2DBase() {};
	virtual ~Object2DBase() {};
	virtual bool Initalize();
	virtual void Finalize();
	virtual void Update();
	virtual void Draw();
private:

};

#endif