#include"Application.h"
#include"DirectX9\macro.h"
#include"Main\Application\Scene\ClearScene\ClearScene.h"
#include"Main\Application\Scene\GameScene\GameScene.h"
#include"Main\Application\Scene\OverScene\OverScene.h"
#include"Main\Application\Scene\TitleScene\TitleScene.h"

/* Windowの大きさ */
const int Application::m_WindowWidth = 1280;
const int Application::m_WindowHeight = 720;

Application::Application():
	m_pMainWindow(nullptr),
	m_pDirectGraphics(nullptr),
	m_pMouseDevice(nullptr),
	m_pSceneManager(nullptr),
	m_pTextureManager(nullptr)
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
	DirectGraphics::CreateInstance(m_pMainWindow->GetWndHandle(), m_WindowWidth,m_WindowHeight,true);
	if (!DirectGraphics::GetInstance()->Initialize())
	{
		MessageBox(0, "ダイレクトグラフィックの作成に失敗しました", NULL, MB_OK);
		SafeDelete(m_pDirectGraphics);
		return false;
	}

	return true;
}

bool Application::CreateMouseDevice()
{
	MouseDevice::CreatepInstance(m_pMainWindow->GetWndHandle());
	if (!MouseDevice::GetpInstance()->Initialize())
	{
		MessageBox(0, "マウスデバイスの作成に失敗しました", NULL, MB_OK);
		SafeDelete(m_pMouseDevice);
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

	m_pGameScene = new GameScene(GAME_SCENE_ID);
	m_pSceneManager->AddScene(m_pGameScene);

	return true;
}

bool Application::CreateTextureManager()
{
	TextureManager::CreateInstance();

	return true;
}