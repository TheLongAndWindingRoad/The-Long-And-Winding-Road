#include"ObjectManager.h"
#include"Player\Player.h"
#include"GameBackGround\GameBackGround.h"
#include"Enemy\Enemy.h"
#include"UIManager\UIManager.h"
#include"DirectX9\macro.h"

ObjectManager::ObjectManager()
{
	//m_pPlayer = new Player;
	//m_pObjectManagers.push_back(m_pPlayer);
	//
	//m_pEnemy = new Enemy;
	//m_pObjectManagers.push_back(m_pEnemy);

	m_pGameBackGround = new GameBackGround;
	m_pObjectManagers.push_back(m_pGameBackGround);

	/* –¾“úã‚ª‚Á‚Ä‚«‚½ƒ\[ƒX‚ðŒ©‚Ä•Ï‚¦‚é */
	//m_pUIManager = new UIManager;
	//m_pObjectManagers.push_back(m_pUIManager);
}

ObjectManager::~ObjectManager()
{
	for (auto itr = m_pObjectManagers.begin(); itr != m_pObjectManagers.end(); itr++)
	{
		SafeDelete(*itr);
	}
}

bool ObjectManager::Initialize()
{
	for (auto itr = m_pObjectManagers.begin(); itr != m_pObjectManagers.end(); itr++)
	{
		if (!(*itr)->Initialize())
		{
			return false;
		}
	}

	return true;
}

void ObjectManager::Finalize()
{
	for (auto itr = m_pObjectManagers.begin(); itr != m_pObjectManagers.end(); itr++)
	{
		(*itr)->Finalize();
	}
}

void ObjectManager::Run()
{
	for (auto itr = m_pObjectManagers.begin(); itr != m_pObjectManagers.end(); itr++)
	{
		(*itr)->Update();
	}

	for (auto itr = m_pObjectManagers.begin(); itr != m_pObjectManagers.end(); itr++)
	{
		(*itr)->Draw();
	}
}