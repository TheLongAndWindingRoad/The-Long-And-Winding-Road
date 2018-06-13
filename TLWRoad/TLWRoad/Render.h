#ifdef DECLARE
#define GLOBAL /**/
#else
#define GLOBAL extern
#endif

#define TEXMAX 1

GLOBAL IDirect3D9*			pDirect3D;
GLOBAL IDirect3DDevice9*	pD3Device;
GLOBAL LPDIRECT3DTEXTURE9	pTexture[TEXMAX];

GLOBAL D3DPRESENT_PARAMETERS d3dpp;

//描画向き
enum DRAWDIRECT {
	NOR,
	REV,
};

//テクスチャの情報
struct TextureInfo{
	LPCWSTR fname;
	float w;
	float h;
};

#ifdef DECLARE
TextureInfo TexInfo[TEXMAX] =
{
	{ TEXT("0.png"), 2048.0f, 4096.0f },
};
#else
extern TextureInfo TexInfo[];
#endif

//素材の情報
#ifdef DECLARE
ImageInfo ImgInfo[] =
{
	#include "image.dat"
};
#else
extern ImageInfo ImgInfo[];
#endif

//プロトタイプ
int LoadTexture(LPCWSTR fname, int TexNo);
void Kaiten(float kakudo, CUSTOMVERTEX src[], CUSTOMVERTEX dest[]);
void DrawObj(int TexNo, CUSTOMVERTEX cv[], float ang);
void SetRender(void);
void ClearScreen(void);
void SetVertexPos(float x, float y, float dw, float dh, CUSTOMVERTEX result[]);
void MakeVertex(CUSTOMVERTEX cv[], float w, float h, float tu, float tv, float tw, float th, DRAWDIRECT dd);
CUSTOMVERTEX* SetVertex(float x, float y, DRAWDIRECT dd, int imgid);
CUSTOMVERTEX* SetVertexEx(float x, float y, int imgid, float zoom, int zp, DRAWDIRECT dd, int alpha);
CUSTOMVERTEX* SetVertexExXYZ(float x, float y, int imgid, float xzoom, float yzoom, int zp, DRAWDIRECT dd, int alpha);
void DrawAnime(ANIMEPAT animeNo, float x, float y, float zoom, int zp, float angle, DRAWDIRECT dd = NOR, int alpha = 255);
void DrawAnimeXYZ(ANIMEPAT animeNo, float x, float y, float xzoom, float yzoom, int zp, float angle, DRAWDIRECT dd = NOR, int alpha = 255);
void DrawAnimeLT(ANIMEPAT animeNo, float x, float y, float zoom, int zp, float angle, DRAWDIRECT dd = NOR, int alpha = 255);
void DrawAnimeNCLT(int animeNo, int di, float x, float y, float zoom, int zp, float angle, DRAWDIRECT dd, int alpha);
void DrawUI(ANIMEPAT animeNo, float x, float y, float zoom, int zp, float angle, DRAWDIRECT dd = NOR, int alpha = 255);



