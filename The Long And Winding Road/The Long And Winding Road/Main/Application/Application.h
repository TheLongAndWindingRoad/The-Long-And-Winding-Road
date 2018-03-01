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
	*	�N���X�����֐��Q
	*	���������true
	*	���s�����false
	*/
	/* ���C���E�C���h�E�̐��� */
	bool CreateMainWindow();
	/* �_�C���N�g�O���t�B�b�N�I�u�W�F�N�g�̐��� */
	bool CreateDirectGraphics();
	/* �}�E�X�f�o�C�X�̐��� */
	bool CreateMouseDevice();
	/* �V�[���Ǘ��I�u�W�F�N�g�̐��� */
	bool CreateSceneManager();
	/* �摜�Ǘ��I�u�W�F�N�g�̐��� */
	bool CreateTextureManager();

	/* ���C���E�B���h�E�̔j�� */
	void DestroyMainWindow();
	/* �_�C���N�g�O���t�B�b�N�I�u�W�F�N�g�̔j�� */
	void DestroyDirectGraphics();
	/* �}�E�X�f�o�C�X�̔j�� */
	void DestroyMouseDevice();
	/* �V�[���Ǘ��I�u�W�F�N�g�̔j�� */
	void DestroySceneManager();
	/* �摜�Ǘ��I�u�W�F�N�g�̔j�� */
	void DestroyTextureManager();

	/* �N���X */

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