#ifndef OVERSCENE_H
#define	OVERSCENE_H

#include"DirectX9\SceneManager\SceaneBase\SceneBase.h"

class OverBackGround;

class OverScene : public SceneBase 
{
public:
	OverScene(int sceneId);
	~OverScene();
	virtual bool Initialize();
	virtual void Finalize();
	virtual void Update();
private:
	OverBackGround* m_pOverBackGround;

	int r = 0;
	int g = 0;
	int b = 0;
};

#endif