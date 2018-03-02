#ifndef UIBASE_H
#define UIBASE_H
#include "Main\Object2DBase\object2DBase.h"
#include "DirectX9\DirectGraphics\DirectGraphics.h"
#include "DirectX9\TextureManager\TextureManager.h"
#include <d3dx9.h>


enum UIID
{
	NUMBEROFATTACKS,
	CREATEROAD,
};
struct UISIZE
{
	float Width, Hight;
};
struct CUSTOMVERTEX
{
	FLOAT	x, y, rhw;
	DWORD	color;
	FLOAT	tu, tv;
};


class UIBase : public Object2DBase
{
public:
	UIBase();
	~UIBase();
	virtual bool Initalize() { return true; }
	virtual void Finalize() {}
	virtual void Update() {}
	virtual void Draw() {}
	virtual void Control() {}
	virtual int* GetTexture() { return &m_TextureId; }
	virtual void SetTexture() {}
private:
	int m_TextureId;
	D3DXVECTOR2 WindowPos;

};




#endif