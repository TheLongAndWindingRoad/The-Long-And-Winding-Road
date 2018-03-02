#ifndef GAMESCENE_H
#define	GAMESCENE_H

#include"DirectX9\SceneManager\SceaneBase\SceneBase.h"
#include"ObjectManager\ObjectManager.h"

class GameScene : public SceneBase
{
public:
	GameScene(int sceneId);
	virtual ~GameScene();
	virtual bool Initialize();
	virtual void Finalize();
	virtual void Update();

private:
	ObjectManager*	m_pObjectManager;
	/* 描画初期化色 */
	int r = 0;
	int g = 0;
	int b = 0;
	/* StateをFinalに持っていけるように */
	bool IsClear = false;
};

#endif