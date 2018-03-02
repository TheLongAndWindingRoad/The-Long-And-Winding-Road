#include "UIManager.h"

UIManager::UIManager()
{
	pNumberOfAttacks = new NumberOfAttacks();
	pCreateRoaad = new CreateRoaad();
}
UIManager::~UIManager()
{
	Finalize();
}
bool UIManager::Initalize()
{
	return true;
}
void UIManager::Finalize()
{
	delete pNumberOfAttacks;
	delete pCreateRoaad;

}
void UIManager::Update(int NumberOfAttacks, int CreateRoaad)
{
	Draw();
	Control(NumberOfAttacks, CreateRoaad);
}
void UIManager::Draw()
{
	pNumberOfAttacks->Draw();
	pCreateRoaad->Draw();

}

void UIManager::Control(int NumberOfAttacks, int CreateRoaad)
{
	pNumberOfAttacks->Control(NumberOfAttacks);
	pCreateRoaad->Control(CreateRoaad);
}