#include "CreateRoaad.h"

CreateRoaad::CreateRoaad()
{
	m_AnimationNum = ROAD_MAX;
	m_TextureId = NUMBEROFATTACKS;
}
CreateRoaad::~CreateRoaad()
{

}

bool CreateRoaad::Initalize()
{
	return true;
}
void CreateRoaad::Finalize()
{

}
void CreateRoaad::Update()
{

}
void CreateRoaad::Draw()
{
	
}
void CreateRoaad::Control(int CreateRoaad)
{
	switch (CreateRoaad)
	{
	case ROAD_0:
		m_AnimationNum = ROAD_0;
		break;
	case ROAD_1:
		m_AnimationNum = ROAD_1;
		break;
	case ROAD_2:
		m_AnimationNum = ROAD_2;
		break;
	case ROAD_MAX:
		m_AnimationNum = ROAD_MAX;
		break;
	default:
		break;
	}

}
void CreateRoaad::SetTexture(int tex, CUSTOMVERTEX vertex[])
{
	TextureManager::GetInstance()->SetTexture(GetTextureId());

	DirectGraphics::GetInstance()->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertex, sizeof(CUSTOMVERTEX));
}