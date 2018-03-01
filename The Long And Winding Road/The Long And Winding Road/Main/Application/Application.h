#ifndef APPLICATION_H
#define	APPLICATION_H

#include"Windows\Windows.h"
#include"DirectX9\SceneManager\SceneManager.h"
#include"DirectX9\DirectGraphics\DirectGraphics.h"
#include"MouseDevice\MouseDevice.h"
#include"DirectX9\TextureManager\TextureManager.h"

class ClearScene;
class GameScene;
class TitleScene;
class OverScene;

class Application
{
public:
	enum SCENE_ID
	{
		TITLE_SCENE_ID,
		GAME_SCENE_ID,
		CLEAR_SCENE_ID,
		OVER_SCENE_ID,
		END_SCENE_ID
	};
	
	Application();
	~Application();
	bool Initialize();
	void Finalize();
	void Run();
	
	static const int m_WindowWidth;
	static const int m_WindowHeight;
private:
	/*
	*	クラス生成関数群
	*	成功すればtrue
	*	失敗すればfalse
	*/
	/* メインウインドウの生成 */
	bool CreateMainWindow();
	/* ダイレクトグラフィックオブジェクトの生成 */
	bool CreateDirectGraphics();
	/* マウスデバイスの生成 */
	bool CreateMouseDevice();
	/* シーン管理オブジェクトの生成 */
	bool CreateSceneManager();
	/* 画像管理オブジェクトの生成 */
	bool CreateTextureManager();

	/* メインウィンドウの破棄 */
	void DestroyMainWindow();
	/* ダイレクトグラフィックオブジェクトの破棄 */
	void DestroyDirectGraphics();
	/* マウスデバイスの破棄 */
	void DestroyMouseDevice();
	/* シーン管理オブジェクトの破棄 */
	void DestroySceneManager();
	/* 画像管理オブジェクトの破棄 */
	void DestroyTextureManager();

	/* クラス */

	Window* m_pMainWindow;
	DirectGraphics* m_pDirectGraphics;
	MouseDevice* m_pMouseDevice;
	SceneManager* m_pSceneManager;
	TextureManager* m_pTextureManager;

	ClearScene* m_pClearScene;
	GameScene*	m_pGameScene;
	OverScene*	m_pOverScene;
	TitleScene*	m_pTitleScene;
};

#endif