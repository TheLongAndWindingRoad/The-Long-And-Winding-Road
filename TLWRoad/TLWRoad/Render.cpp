#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include <d3dx9tex.h>

#include "UNION.h"
#include "Control.h"
#include "Render.h"

void SetRender(void)
{
	pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRCの設定
	pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD3Device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE,D3DMCS_COLOR1 );

	pD3Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pD3Device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);  

	pD3Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
}

void ClearScreen(void)
{
	pD3Device->Clear(0, NULL, 
						D3DCLEAR_TARGET,
						D3DCOLOR_XRGB(0xFF, 0xFF, 0xFF),
						1.0, 0);
}

int LoadTexture(LPCWSTR fname, int TexNo)
{
	int ret;

	ret = 0;
	if (FAILED(D3DXCreateTextureFromFileEx(
					pD3Device,
					fname,
					D3DX_DEFAULT_NONPOW2,
					D3DX_DEFAULT_NONPOW2,
					D3DX_DEFAULT,
					0,
					D3DFMT_UNKNOWN,
					D3DPOOL_MANAGED,
					D3DX_FILTER_NONE,
					D3DX_FILTER_NONE,
					D3DCOLOR_ARGB(255, 0, 255, 0),
					NULL, NULL,
					&pTexture[TexNo]))) {
						ret = -1;
	}
	return ret;
}

void Kaiten(float kakudo, CUSTOMVERTEX src[], CUSTOMVERTEX dest[])
{
	float cx, cy;
	float rad;

	rad = D3DXToRadian(kakudo);

	cx = (src[0].x + src[1].x) / 2.0f;
	cy = (src[0].y + src[3].y) / 2.0f;

	for (int i = 0 ; i < 4 ; i++) {
		src[i].x -= cx;
		src[i].y -= cy;

		dest[i] = src[i];
		dest[i].x = (FLOAT)(src[i].x * cos(rad) - src[i].y * sin(rad));
		dest[i].y = (FLOAT)(src[i].x * sin(rad) + src[i].y * cos(rad));
		src[i].x += cx;
		src[i].y += cy;
		dest[i].x += cx;
		dest[i].y += cy;
	}
}

void DrawObj(int TexNo, CUSTOMVERTEX cv[], float ang)
{
	CUSTOMVERTEX wk[4];

	Kaiten(ang, cv, wk);

	pD3Device->SetTexture(0, pTexture[TexNo]);
	pD3Device->DrawPrimitiveUP(
			D3DPT_TRIANGLEFAN,
			2,
			wk,
			sizeof(CUSTOMVERTEX));
}

void MakeVertex(CUSTOMVERTEX cv[], float w, float h, float tu, float tv, float tw, float th, DRAWDIRECT dd)
{
	cv[0].x = cv[3].x = 0.0f;
	cv[1].x = cv[2].x = w;
	cv[0].y = cv[1].y = 0.0f;
	cv[2].y = cv[3].y = h;
	for (int i = 0 ; i < 4 ; i++) {
		cv[i].z = 0.5f;
		cv[i].rhw = 1.0f;
		cv[i].color = 0xFFFFFFFF;
	}
	cv[0].tu = cv[3].tu = ((dd == NOR) ? tu : tu + w) / tw;
	cv[1].tu = cv[2].tu = ((dd == NOR) ? tu + w : tu) / tw;
	cv[0].tv = cv[1].tv = tv / th;
	cv[2].tv = cv[3].tv = (tv + h) / th;
}

void SetVertexPos(float x, float y, float dw, float dh, CUSTOMVERTEX result[])
{
	result[0].x = x - dw / 2;
	result[1].x = x + dw / 2;
	result[2].x = x + dw / 2;
	result[3].x = x - dw / 2;
	result[0].y = y - dh / 2;
	result[1].y = y - dh / 2;
	result[2].y = y + dh / 2;
	result[3].y = y + dh / 2;
}

void SetVertexAlpha(int alpha, CUSTOMVERTEX result[])
{
	for (int i = 0; i < 4; i++) {
		result[i].color &= 0xffffff;
		result[i].color += alpha * 0x1000000;
	}
}

CUSTOMVERTEX* SetVertex(float x, float y, DRAWDIRECT dd, int imgid)
{
	static CUSTOMVERTEX cv[4];
	float zw, zh;

	MakeVertex(cv, ImgInfo[imgid].w, ImgInfo[imgid].h, ImgInfo[imgid].sx, ImgInfo[imgid].sy, TexInfo[ImgInfo[imgid].texid].w, TexInfo[ImgInfo[imgid].texid].h, dd);
	zw = ImgInfo[imgid].w;
	zh = ImgInfo[imgid].h;

	SetVertexPos(x, y, zw, zh, cv);

	return cv;
}

// zp 0;中央　1:中央下
CUSTOMVERTEX* SetVertexEx(float x, float y, int imgid, float zoom, int zp, DRAWDIRECT dd, int alpha)
{
	static CUSTOMVERTEX cv[4];
	float zw, zh;

	MakeVertex(cv, ImgInfo[imgid].w, ImgInfo[imgid].h, ImgInfo[imgid].sx, ImgInfo[imgid].sy, TexInfo[ImgInfo[imgid].texid].w, TexInfo[ImgInfo[imgid].texid].h, dd);
	zw = ImgInfo[imgid].w;
	zh = ImgInfo[imgid].h;

	if (zp == 1) {
		y -= (zoom - 1.0f) * zh / 2.0f;
	}
	zw *= zoom;
	zh *= zoom;

	SetVertexPos(x, y, zw, zh, cv);
	SetVertexAlpha(alpha, cv);
	return cv;
}

// zp 0;中央　1:中央下
CUSTOMVERTEX* SetVertexExXYZ(float x, float y, int imgid, float xzoom, float yzoom, int zp, DRAWDIRECT dd, int alpha)
{
	static CUSTOMVERTEX cv[4];
	float zw, zh;

	MakeVertex(cv, ImgInfo[imgid].w, ImgInfo[imgid].h, ImgInfo[imgid].sx, ImgInfo[imgid].sy, TexInfo[ImgInfo[imgid].texid].w, TexInfo[ImgInfo[imgid].texid].h, dd);
	zw = ImgInfo[imgid].w;
	zh = ImgInfo[imgid].h;

	if (zp == 1) {
		y -= (yzoom - 1.0f) * zh / 2.0f;
	}
	zw *= xzoom;
	zh *= yzoom;

	SetVertexPos(x, y, zw, zh, cv);
	SetVertexAlpha(alpha, cv);
	return cv;
}

//X,Yはセンター
void DrawAnime(ANIMEPAT animeNo, float x, float y, float zoom, int zp, float angle, DRAWDIRECT dd, int alpha)
{
	int texId;
	int imgId;

	imgId = imgNo[CtrlAnime(animeNo)];
	texId = ImgInfo[imgId].texid;

	DrawObj(texId, SetVertexEx(x - BP.x, y - BP.y, imgId, zoom, zp, dd, alpha), angle);
}

//X,Yはセンター
void DrawAnimeXYZ(ANIMEPAT animeNo, float x, float y, float xzoom, float yzoom, int zp, float angle, DRAWDIRECT dd, int alpha)
{
	int texId;
	int imgId;

	imgId = imgNo[CtrlAnime(animeNo)];
	texId = ImgInfo[imgId].texid;

	DrawObj(texId, SetVertexExXYZ(x - BP.x, y - BP.y, imgId, xzoom, yzoom, zp, dd, alpha), angle);
}
//X,Yは左上
void DrawAnimeLT(ANIMEPAT animeNo, float x, float y, float zoom, int zp, float angle, DRAWDIRECT dd, int alpha)
{
	int texId;
	int imgId;

	imgId = imgNo[CtrlAnime(animeNo)];
	texId = ImgInfo[imgId].texid;

	DrawObj(texId, SetVertexEx(x + ImgInfo[imgId].w / 2.0f - BP.x, y + ImgInfo[imgId].h / 2.0f - BP.y, imgId, zoom, zp, dd, alpha), angle);
}

//X,Yは左上 Animation No Control
void DrawAnimeNCLT(int animeNo, int di, float x, float y, float zoom, int zp, float angle, DRAWDIRECT dd, int alpha)
{
	int texId;
	int imgId;

	imgId = imgNo[infoAnime[animeNo].topanime + di];
	texId = ImgInfo[imgId].texid;

	DrawObj(texId, SetVertexEx(x + ImgInfo[imgId].w / 2.0f - BP.x, y + ImgInfo[imgId].h / 2.0f - BP.y, imgId, zoom, zp, dd, alpha), angle);
}

//X,yは絶対値
void DrawUI(ANIMEPAT animeNo, float x, float y, float zoom, int zp, float angle, DRAWDIRECT dd, int alpha)
{
	int texId;
	int imgId;

	imgId = imgNo[CtrlAnime(animeNo)];
	texId = ImgInfo[imgId].texid;

	DrawObj(texId, SetVertexEx(x, y, imgId, zoom, zp, dd, alpha), angle);
}