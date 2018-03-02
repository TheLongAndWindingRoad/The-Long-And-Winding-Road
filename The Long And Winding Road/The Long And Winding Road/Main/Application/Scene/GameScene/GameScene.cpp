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
		MessageBox(0, "�I�u�W�F�N�g�Ǘ��N���X�쐬�Ɏ��s���܂���", NULL, MB_OK);
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


/* �Q�[���V�[���̑J�ڐ�͏オ���Ă��Ă���̔���ŏ��������� */
void GameScene::Update()
{
	DirectGraphics::GetInstance()->BeginScene(r, g, b);
	/* ������ObjectManager��Update�֐����Ă� */
	DirectGraphics::GetInstance()->EndScene();
}