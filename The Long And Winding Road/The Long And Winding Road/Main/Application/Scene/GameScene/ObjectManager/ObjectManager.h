#ifndef OBJECTMANAGER_H
#define	OBJECTMANAGER_H

#include"Main\Object2DBase\object2DBase.h"
#include<vector>

class ObjectManager
{
public:
	ObjectManager();
	virtual~ObjectManager();

	bool Initialize();
	void Finalize();

private:
	std::vector<ObjectBase*> m_pObjectManagers;
};

#endif