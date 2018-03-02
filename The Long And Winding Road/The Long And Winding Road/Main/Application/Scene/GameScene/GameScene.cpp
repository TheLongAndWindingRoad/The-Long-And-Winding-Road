#include<Windows.h>
#include"GameScene.h"
#include"DirectX9\macro.h"
#include"DirectX9\TextureManager\TextureManager.h"
#include"DirectX9\DirectGraphics\DirectGraphics.h"

GameScene::GameScene(int sceneId) :
	SceneBase(sceneId)
{
}

GameScene::~GameScene()
{
}

bool GameScene::Initialize()
{
	m_pObjectManager = new ObjectManager;
	if (!m_pObjectManager->Initialize())
	{
		MessageBox(0, "オブジェクト管理クラス作成に失敗しました", NULL, MB_OK);
		return false;
	}

	m_State = UPDATE_STATE;

	return true;
}

void GameScene::Finalize()
{
	if (m_pObjectManager != nullptr) 
	{
		m_pObjectManager->Finalize();
		SafeDelete(m_pObjectManager);
	}

	m_State = INIT_STATE;
}


/* ゲームシーンの遷移先は上がってきてからの判定で処理をする */
void GameScene::Update()
{
	DirectGraphics::GetInstance()->BeginScene(r, g, b);
	/* ここにObjectManagerのUpdate関数を呼ぶ */
	DirectGraphics::GetInstance()->EndScene();
}