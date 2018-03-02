#include"ClearBackGround.h"
#include "DirectX9\TextureManager\TextureManager.h"
#include "DirectX9\DirectGraphics\DirectGraphics.h"
#include "Main\Application\MouseDevice\MouseDevice.h"


ClearBackGround::ClearBackGround()
{

}

ClearBackGround::~ClearBackGround()
{

}

bool ClearBackGround::Initialize()
{
	CUSTOMVERTEX Clear[]
	{
		{ 0.f,	0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ 0.f,	w_Width, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ w_Height,	w_Width, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ w_Height,	0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	for (int i = 0; i < 4; i++)
	{
		m_Clear[i] = Clear[i];
	}


	/* ファイルの名前を入れる */
	TextureManager::GetInstance()->LoadTexture("", &m_ClearTexture);

	return true;
}

void ClearBackGround::Finalize()
{

}

void ClearBackGround::Update()
{

}

void ClearBackGround::Draw()
{
	TextureManager::GetInstance()->SetTexture(m_ClearTexture);
	DirectGraphics::GetInstance()->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_Clear, sizeof(CUSTOMVERTEX));
}