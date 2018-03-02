#include"Application.h"
#include"DirectX9\macro.h"
#include"Main\Application\Scene\ClearScene\ClearScene.h"
#include"Main\Application\Scene\GameScene\GameScene.h"
#include"Main\Application\Scene\OverScene\OverScene.h"
#include"Main\Application\Scene\TitleScene\TitleScene.h"
#include"DirectX9\DirectGraphics\DirectGraphics.h"
#include"MouseDevice\MouseDevice.h"
#include"DirectX9\TextureManager\TextureManager.h"

/* Windowの大きさ */
const int Application::m_WindowWidth = 1280;
const int Application::m_WindowHeight = 720;

Application::Application():
	m_pMainWindow(nullptr),
	m_pSceneManager(nullptr)
{
}

Application::~Application()
{
	Finalize();
}

bool Application::Initialize()
{
	if (!CreateMainWindow())
	{
		Finalize();
		return false;
	}

	if (!CreateDirectGraphics())
	{
		Finalize();
		return false;
	}

	if (!CreateMouseDevice())
	{
		Finalize();
		return false;
	}

	if (!CreateSceneManager())
	{
		Finalize();
		return false;
	}

	if (!CreateTextureManager())
	{
		Finalize();
		return false;
	}

	return true;
}

void Application::Finalize()
{
	DestroyTextureManager();
	DestroySceneManager();
	DestroyMouseDevice();
	DestroyDirectGraphics();
	DestroyMainWindow();
}

void Application::Run()
{
	while (1)
	{
		if (!m_pMainWindow->Update())
		{
			if (m_pSceneManager->Update())
			{
				break;
			}
		}
		else
		{
			break;
		}
	}
}

/* private関数 */
bool Application::CreateMainWindow()
{
	m_pMainWindow = new Window();
	if (!m_pMainWindow->Initialize("The-Long-And-Winding-Road", m_WindowWidth, m_WindowHeight))
	{
		MessageBox(0, "メインウィンドウの作成に失敗しました", NULL, MB_OK);
		SafeDelete(m_pMainWindow);
		return false;
	}

	return true;
}

bool Application::CreateDirectGraphics()
{
	/*全画面表示ができない状態になっている */

	DirectGraphics::CreateInstance(m_pMainWindow->GetWndHandle(), m_WindowWidth,m_WindowHeight,false);
	if (!DirectGraphics::GetInstance()->Initialize())
	{
		//MessageBox(0, "ダイレクトグラフィックの作成に失敗しました", NULL, MB_OK);
		return false;
	}

	return true;
}

bool Application::CreateMouseDevice()
{
	MouseDevice::CreatepInstance(m_pMainWindow->GetWndHandle());
	MouseDevice::GetpInstance()->InitDinput();
	if (!MouseDevice::GetpInstance()->Initialize())
	{
		MessageBox(0, "マウスデバイスの作成に失敗しました", NULL, MB_OK);
		return false;
	}

	return true;
}

bool Application::CreateSceneManager()
{
	m_pSceneManager = new SceneManager();
	if (!m_pSceneManager->Initialize())
	{
		SafeDelete(m_pSceneManager);
		return false;
	}

	m_pTitleScene = new TitleScene(TITLE_SCENE_ID);
	m_pSceneManager->AddScene(m_pTitleScene);

	m_pGameScene = new GameScene(GAME_SCENE_ID);
	m_pSceneManager->AddScene(m_pGameScene);

	m_pClearScene = new ClearScene(CLEAR_SCENE_ID);
	m_pSceneManager->AddScene(m_pClearScene);

	m_pOverScene = new OverScene(OVER_SCENE_ID);
	m_pSceneManager->AddScene(m_pOverScene);

	m_pSceneManager->SetEntryScene(m_pTitleScene);

	return true;
}

bool Application::CreateTextureManager()
{
	TextureManager::CreateInstance();

	return true;
}

void Application::DestroyMainWindow() {
	if (m_pMainWindow != nullptr)
	{
		m_pMainWindow->Finalize();
		SafeDelete(m_pMainWindow);
	}
}

void Application::DestroyDirectGraphics()
{
	if (DirectGraphics::GetInstance() != nullptr) 
	{
		DirectGraphics::GetInstance()->Finalize();
	}
}

void Application::DestroyMouseDevice()
{
	if (MouseDevice::GetpInstance() != nullptr)
	{
		MouseDevice::GetpInstance()->DestroyMouseDevice();
	}
}

void Application::DestroySceneManager()
{
	if (m_pSceneManager != nullptr)
	{
		/* 生成したのと逆の順で破棄する */
		m_pSceneManager->DeleteScene(m_pTitleScene);
		SafeDelete(m_pTitleScene);

		m_pSceneManager->DeleteScene(m_pGameScene);
		SafeDelete(m_pGameScene);

		m_pSceneManager->DeleteScene(m_pClearScene);
		SafeDelete(m_pClearScene);

		m_pSceneManager->DeleteScene(m_pOverScene);
		SafeDelete(m_pOverScene);

		m_pSceneManager->Finalize();
		SafeDelete(m_pSceneManager);
	}
}

void Application::DestroyTextureManager()
{
	if (TextureManager::GetInstance() != nullptr)
	{
		TextureManager::GetInstance()->DestroyInstance();
	}
}