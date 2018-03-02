#ifndef NUMBER_OF_ATTACKS_H
#define NUMBER_OF_ATTACKS_H
#include "Main\Application\Scene\GameScene\ObjectManager\UIBase\UIBase.h"


enum NUMBER_OF_ATTACK
{
	ATK_0,
	ATK_1,
	ATK_2,
	ATK_3,
	ATK_4,
	ATK_MAX,
};



class NumberOfAttacks:public UIBase
{
public:
	NumberOfAttacks();
	~NumberOfAttacks();
	virtual bool Initalize();
	virtual void Finalize();
	virtual void Update();
	virtual void Draw();
	void Control(int NumberOfAttacks);
	int* GetTexture() { return &m_TextureId; }
	int GetTextureId() { return m_TextureId; }
	virtual void SetTexture(int tex, CUSTOMVERTEX vertex[]);
private:
	NUMBER_OF_ATTACK m_AnimationNum;
	int m_TextureId;
	UISIZE Size;
	const float m_Tu=150.f;
	const float m_Tv=75.f;
};

#endif