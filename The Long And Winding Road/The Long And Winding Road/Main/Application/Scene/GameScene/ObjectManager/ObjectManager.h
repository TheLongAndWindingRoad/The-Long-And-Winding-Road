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
	/* Run関数も必要 */
	/* collision関数も必要 */
private:
	/* オブジェクトの格納するコンテナ */
	std::vector<ObjectBase*> m_pObjectManagers;

	Player* m_pPlayer;
	Enemy* m_pEnemy;
	GameBackGround* m_pGameBackGround;
	UIManager* m_pUIManager;

	/* 残りの作れる道の数 */
	int m_CreateRoad;
	/* 残りの斬撃数 */
	int m_PlayerAttack;
};

#endif