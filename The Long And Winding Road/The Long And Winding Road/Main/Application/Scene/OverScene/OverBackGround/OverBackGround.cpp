#include"OverBackGround.h"
#include "DirectX9\TextureManager\TextureManager.h"
#include "DirectX9\DirectGraphics\DirectGraphics.h"
#include "Main\Application\MouseDevice\MouseDevice.h"

OverBackGround::OverBackGround() 
{

}

OverBackGround::~OverBackGround()
{

}

bool OverBackGround::Initialize()
{


	CUSTOMVERTEX Over[]
	{
		{ 0.f,	0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ 0.f,	w_Width, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ w_Height,	w_Width, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ w_Height,	0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	for (int i = 0; i < 4; i++)
	{
		m_Over[i] = Over[i];
	}

	/* ファイルの名前を入れる */
	TextureManager::GetInstance()->LoadTexture("", &m_OverTexture);
	
	return true;
}

void OverBackGround::Finalize()
{

}

void OverBackGround::Update()
{

}

void OverBackGround::Draw()
{
	TextureManager::GetInstance()->SetTexture(m_OverTexture);
	DirectGraphics::GetInstance()->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_Over, sizeof(CUSTOMVERTEX));
}