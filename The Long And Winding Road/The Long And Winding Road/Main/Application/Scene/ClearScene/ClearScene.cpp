#include"ClearScene.h"
#include"ClearBackGround\ClearBackGround.h"
#include"DirectX9\macro.h"
#include"DirectX9\TextureManager\TextureManager.h"
#include"DirectX9\DirectGraphics\DirectGraphics.h"

ClearScene::ClearScene(int sceneId):
	SceneBase(sceneId)
{

}

ClearScene::~ClearScene()
{

}

bool ClearScene::Initialize()
{
	m_pClearBackGround = new ClearBackGround;
	if (!m_pClearBackGround->Initialize())
	{
		MessageBox(0, "�Q�[���N���A�V�[���̍쐬�Ɏ��s���܂���", NULL, MB_OK);
		return false;
	}

	m_State = UPDATE_STATE;

	return true;
}

void ClearScene::Finalize()
{
	if (m_pClearBackGround != nullptr)
	{
		m_pClearBackGround->Finalize();
		SafeDelete(m_pClearBackGround);
	}

	m_State = INIT_STATE;
}

void ClearScene::Update()
{
	DirectGraphics::GetInstance()->BeginScene(r, g, b);
	m_pClearBackGround->Draw();
	DirectGraphics::GetInstance()->EndScene();
}