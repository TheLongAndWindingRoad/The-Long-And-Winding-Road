#include"TitleBackGround.h"
#include "DirectX9\TextureManager\TextureManager.h"
#include "DirectX9\DirectGraphics\DirectGraphics.h"
#include "Main\Application\MouseDevice\MouseDevice.h"

TitleBackGround::TitleBackGround()
{

}

TitleBackGround::~TitleBackGround()
{

}

bool TitleBackGround::Initialize()
{
	CUSTOMVERTEX Title[]
	{
		{ 0.f,	0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ 0.f,	w_Width, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ w_Height,	w_Width, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ w_Height,	0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	for (int i = 0; i < 4; i++)
	{
		m_Title[i] = Title[i];
	}


	/* ファイルの名前を入れる */
	TextureManager::GetInstance()->LoadTexture("Texture//window.png", &m_TitleTexture);

	return true;
}

void TitleBackGround::Finalize()
{

}

void TitleBackGround::Update()
{
}

void TitleBackGround::Draw()
{
	TextureManager::GetInstance()->SetTexture(m_TitleTexture);
	DirectGraphics::GetInstance()->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_Title, sizeof(CUSTOMVERTEX));
}