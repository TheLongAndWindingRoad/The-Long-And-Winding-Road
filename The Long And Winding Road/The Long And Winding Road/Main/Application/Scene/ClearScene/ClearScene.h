#ifndef CLEARSCENE_H
#define	CLEARSCENE_H

#include"DirectX9\SceneManager\SceaneBase\SceneBase.h"

class ClearBackGround;

class ClearScene : public SceneBase
{
public:
	ClearScene(int sceneId);
	virtual ~ClearScene();
	virtual bool Initialize();
	virtual void Finalize();
	virtual void Update();

private:
	ClearBackGround* m_pClearBackGround;
};

#endif