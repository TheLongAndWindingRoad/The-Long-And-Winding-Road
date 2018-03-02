#include"TitleScene.h"
#include"DirectX9\macro.h"
#include"DirectX9\TextureManager\TextureManager.h"
#include"DirectX9\DirectGraphics\DirectGraphics.h"
#include"TitleBackGround\TitleBackGround.h"
#include"..\..\Application.h"
#include"Main\Application\MouseDevice\MouseDevice.h"
#include<Windows.h>

TitleScene::TitleScene(int sceneId) :
	SceneBase(sceneId)
{
}

TitleScene::~TitleScene()
{
}

bool TitleScene::Initialize()
{
	m_pTitleBackGround = new TitleBackGround;
	if (!m_pTitleBackGround->Initialize())
	{
		MessageBox(0, "ƒ^ƒCƒgƒ‹‚Ìì¬‚ÉŽ¸”s‚µ‚Ü‚µ‚½", NULL, MB_OK);
		return false;
	}

	m_State = UPDATE_STATE;

	return true;
}

void TitleScene::Finalize()
{
	if (m_pTitleBackGround != nullptr)
	{
		m_pTitleBackGround->Finalize();
		SafeDelete(m_pTitleBackGround);
	}

	m_State = INIT_STATE;
}

void TitleScene::Update()
{
	MOUSEKIND mouse;
	MouseDevice::GetpInstance()->MouseCheck(&mouse);

	if (mouse.IsLeftClick)
	{
		m_State = FAINAL_STATE;
		m_NextSceneID = Application::GAME_SCENE_ID;
	}
	DirectGraphics::GetInstance()->BeginScene(r, g, b);
	m_pTitleBackGround->Draw();
	DirectGraphics::GetInstance()->EndScene();
}