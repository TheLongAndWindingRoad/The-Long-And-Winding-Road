#include"TextureManager.h"
#include"..\DirectGraphics\DirectGraphics.h"
#include"..\macro.h"

TextureManager* TextureManager::pInstance = NULL;

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

void TextureManager::CreateInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new TextureManager;
	}
}

void TextureManager::DestroyInstance()
{
	if (pInstance != NULL)
	{
		delete pInstance;
		pInstance = nullptr;
	}

}

//Object�͎�����ID��������
bool TextureManager::LoadTexture(LPCTSTR fname, int* Texture)
{
	LPDIRECT3DTEXTURE9 tex;

	if (FAILED(D3DXCreateTextureFromFileEx(
		DirectGraphics::GetInstance()->GetDevice(),
		fname,              // �t�@�C����
		0,
		0,
		0,
		0,
		D3DFMT_A1R5G5B5,                // �F�������\��
		D3DPOOL_MANAGED,
		D3DX_FILTER_LINEAR,
		D3DX_FILTER_LINEAR,
		D3DCOLOR_ARGB(255, 0, 255, 0),  //�΂𓧉�
		NULL,
		NULL,
		&tex)))
	{
		return false;
	}

	/* �C���f�b�N�X�ԍ���Ԃ��Ă��� */
	*Texture = m_pTexture.size();
	m_pTexture.push_back(tex);

	return true;
}

void TextureManager::SetTexture(int* tex)
{
	DirectGraphics::GetInstance()->GetDevice()->SetTexture(0,GetTexture(tex));
}

LPDIRECT3DTEXTURE9 TextureManager::GetTexture(int* tex)
{
	return m_pTexture[*tex];
}

void TextureManager::Release()
{
	for (auto itr = m_pTexture.begin(); itr != m_pTexture.end(); itr++)
	{
		SafeRelease(*itr);
	}

	//11�ł�vector�̉񂵕�
	//for (auto pTexture : m_pTexture)
	//{
	//	SafeRelease(pTexture);
	//}
}