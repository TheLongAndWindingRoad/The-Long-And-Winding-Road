#ifndef TITLESCENE_H
#define	TITLESCENE_H

#include"DirectX9\SceneManager\SceaneBase\SceneBase.h"

class TitleBackGround;

class TitleScene : public SceneBase
{
public:
	TitleScene(int sceneId);
	~TitleScene();
	virtual bool Initialize();
	virtual void Finalize();
	virtual void Update();
private:
	TitleBackGround* m_pTitleBackGround;
	const int r = 100;
	const int g =   0;
	const int b = 100;
};

#endif