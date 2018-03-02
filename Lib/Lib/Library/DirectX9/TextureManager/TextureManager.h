#ifndef TEXTUREMANAGER_H
#define	TEXTUREMANAGER_H

#include<vector>
#include<d3d9.h>

//ƒVƒ“ƒOƒ‹ƒgƒ“‰»‚³‚¹‚é‚×‚«

class TextureManager
{
public:
	virtual ~TextureManager();
	void Release();
	bool LoadTexture(LPCTSTR fname,int* Texture);
	void SetTexture(int* tex);

	static TextureManager* GetInstance() { return pInstance; }
	static void CreateInstance();
	static void DestroyInstance();

	LPDIRECT3DTEXTURE9 GetTexture(int* tex);
private:
	TextureManager();
	static TextureManager* pInstance;
	std::vector<LPDIRECT3DTEXTURE9> m_pTexture;
	
};

#endif