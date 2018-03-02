#include "Number_of_attacks.h"

NumberOfAttacks::NumberOfAttacks()
{
	m_AnimationNum = ATK_MAX;
	m_TextureId = CREATEROAD;
	TextureManager::GetInstance()->LoadTexture("êîéöâÊëúÉpÉX", GetTexture());


}
NumberOfAttacks::~NumberOfAttacks()
{

}

bool NumberOfAttacks::Initalize()
{
	return true;
}
void NumberOfAttacks::Finalize()
{

}
void NumberOfAttacks::Update()
{

}
void NumberOfAttacks::Draw()
{
	CUSTOMVERTEX Number[4];
	static CUSTOMVERTEX NumberVertex[4]
	{
		{ -Size.Width / 2,-Size.Hight / 2,1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ +Size.Width / 2,-Size.Hight / 2,1.f, 0xFFFFFFFF, m_Tu, 0.f },
		{ +Size.Width / 2,+Size.Hight / 2,1.f, 0xFFFFFFFF, m_Tu, m_Tv },
		{ -Size.Width / 2,+Size.Hight / 2,1.f, 0xFFFFFFFF, 0.f, m_Tv }
	};
	for (int i = 0; i < 4; ++i)
	{
		Number[i] = NumberVertex[i];
		Number[i].x = NumberVertex[i].x;
		Number[i].y = NumberVertex[i].y;
	}
	switch (m_AnimationNum)
	{
	case ATK_0:
		for (int i = 0; i < 0; ++i)
		{
			Number[i].tu += m_Tu * 0;
		}
		break;
	case ATK_1:
		for (int i = 0; i < 0; ++i)
		{
			Number[i].tu += m_Tu * 1;
		}
		break;
	case ATK_2:
		for (int i = 0; i < 0; ++i)
		{
			Number[i].tu += m_Tu * 2;
		}
		break;
	case ATK_3:
		for (int i = 0; i < 0; ++i)
		{
			Number[i].tu += m_Tu * 3;
		}
		break;
	case ATK_4:
		for (int i = 0; i < 0; ++i)
		{
			Number[i].tu += m_Tu * 4;
		}
		break;
	case ATK_MAX:
		for (int i = 0; i < 0; ++i)
		{
			Number[i].tu += m_Tu * 5;
		}
		break;
	default:
		break;
	}
	SetTexture(GetTextureId(), Number);
}
void NumberOfAttacks::Control(int NumberOfAttacks)
{
	switch (NumberOfAttacks)
	{
	case ATK_0:
		m_AnimationNum = ATK_0;
		break;
	case ATK_1:
		m_AnimationNum = ATK_1;
		break;
	case ATK_2:
		m_AnimationNum = ATK_2;
		break;
	case ATK_3:
		m_AnimationNum = ATK_3;
		break;
	case ATK_4:
		m_AnimationNum = ATK_4;
		break;
	case ATK_MAX:
		m_AnimationNum = ATK_MAX;
	default:
		break;
	}
}

void NumberOfAttacks::SetTexture(int tex, CUSTOMVERTEX vertex[])
{
	TextureManager::GetInstance()->SetTexture(GetTextureId());

	DirectGraphics::GetInstance()->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertex, sizeof(CUSTOMVERTEX));
}