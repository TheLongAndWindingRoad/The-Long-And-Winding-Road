#ifndef OBJECTMANAGER_H
#define	OBJECTMANAGER_H

#include"Main\Object2DBase\object2DBase.h"
#include<vector>

class Player;
class Enemy;
class GameBackGround;
class UIManager;

class ObjectManager
{
public:
	ObjectManager();
	virtual~ObjectManager();
	bool Initialize();
	void Finalize();
	/* Run�֐����K�v */
	/* collision�֐����K�v */
private:
	/* �I�u�W�F�N�g�̊i�[����R���e�i */
	std::vector<ObjectBase*> m_pObjectManagers;

	Player* m_pPlayer;
	Enemy* m_pEnemy;
	GameBackGround* m_pGameBackGround;
	UIManager* m_pUIManager;

	/* �c��̍��铹�̐� */
	int m_CreateRoad;
	/* �c��̎a���� */
	int m_PlayerAttack;
};

#endif