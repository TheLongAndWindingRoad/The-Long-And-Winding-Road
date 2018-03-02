#ifndef UIMANAGER_H
#define UIMANAGER_H
#include "Main\Object2DBase\object2DBase.h"
#include "Number_of_attacks\Number_of_attacks.h"
#include "CreateRoaad\CreateRoaad.h"

class NumberOfAttacks;
class CreateRoaad;

class UIManager :public Object2DBase
{
public:
	UIManager();
	~UIManager();
	virtual bool Initalize();
	virtual void Finalize();
	virtual void Update(int NumberOfAttacks, int CreateRoaad);
	virtual void Draw();
	virtual void Control(int NumberOfAttacks, int CreateRoaad);

private:
	NumberOfAttacks* pNumberOfAttacks;
	CreateRoaad* pCreateRoaad;

};



#endif