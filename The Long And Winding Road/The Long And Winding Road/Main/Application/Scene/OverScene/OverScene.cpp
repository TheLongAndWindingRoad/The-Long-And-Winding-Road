#include"OverScene.h"
#include"OverBackGround\OverBackGround.h"
#include"DirectX9\macro.h"
#include"DirectX9\TextureManager\TextureManager.h"
#include"DirectX9\DirectGraphics\DirectGraphics.h"
#include"..\..\Application.h"
#include"Main\Application\MouseDevice\MouseDevice.h"
#include<Windows.h>

OverScene::OverScene(int sceneId):
	SceneBase(sceneId)
{
}

OverScene::~OverScene()
{
}

bool OverScene::Initialize()
{
	m_pOverBackGround = new OverBackGround;
	if (!m_pOverBackGround->Initialize())
	{
		MessageBox(0, "ゲームオーバーの作成に失敗しました", NULL, MB_OK);
		return false;
	}

	m_State = UPDATE_STATE;

	return true;
}

void OverScene::Finalize()
{
	if (m_pOverBackGround != nullptr)
	{
		m_pOverBackGround->Finalize();
		SafeDelete(m_pOverBackGround);
	}

	m_State = INIT_STATE;
}

void OverScene::Update()
{
	MOUSEKIND mouse;
	MouseDevice::GetpInstance()->MouseCheck(&mouse);

	if (mouse.IsLeftClick)
	{
		m_State = FAINAL_STATE;
		m_NextSceneID = Application::TITLE_SCENE_ID;
	}
	DirectGraphics::GetInstance()->BeginScene(r, g, b);
	m_pOverBackGround->Update();
	DirectGraphics::GetInstance()->EndScene();
}