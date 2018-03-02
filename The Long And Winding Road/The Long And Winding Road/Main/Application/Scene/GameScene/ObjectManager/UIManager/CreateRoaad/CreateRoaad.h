#ifndef CREATEROAAD_H
#define CREATEROAAD_H

#include "Main\Application\Scene\GameScene\ObjectManager\UIBase\UIBase.h"

enum CREATEROAAD
{
	ROAD_0,
	ROAD_1,
	ROAD_2,
	ROAD_MAX,
};



class CreateRoaad :public UIBase
{
public:
	CreateRoaad();
	~CreateRoaad();
	virtual bool Initalize();
	virtual void Finalize();
	virtual void Update();
	virtual void Draw();
	void Control(int CreateRoaad);
	int* GetTexture() { return &m_TextureId; }
	int GetTextureId() { return m_TextureId; }
	virtual void SetTexture(int tex, CUSTOMVERTEX vertex[]);
private:
	CREATEROAAD m_AnimationNum;
	int m_TextureId;
	const float m_Tu = 150.f;
	const float m_Tv = 75.f;
	UISIZE m_Size;
};

#endif
