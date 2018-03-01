#ifndef DIRECTGRAPHICS_H
#define	DIRECTGRAPHICS_H

#define D3DFVF_CUSTOMVERTEX ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#include<d3dx9.h>
#include<d3d9.h>

/* ここはシングルトン化させる */

class DirectGraphics
{
public:
	/* 解放関数 */
	~DirectGraphics();

	static void CreateInstance(HWND hWnd, float h, float w,bool b);

	void SetRenderlingConfiguration();
	bool Initialize();
	void Finalize();
	void BeginScene(int r, int g, int b);
	void EndScene();

	inline LPDIRECT3DDEVICE9 GetDevice() { return m_pD3Device; }

	/* インスタンスの取得をstatic関数にすることでグローバルアクセスにしている */
	static DirectGraphics* GetInstance() { return pInstance; }
private:
	LPDIRECT3D9 m_pDirect3D;
	LPDIRECT3DDEVICE9 m_pD3Device;
	D3DPRESENT_PARAMETERS m_D3dpp;
	D3DPRESENT_PARAMETERS m_D3dppwnd;
	D3DPRESENT_PARAMETERS m_D3dppfull;
	D3DDISPLAYMODE		  m_D3DdisplayMode;
	HWND m_hWnd;
	float m_gWidth;
	float m_gHeight;
	bool m_fullscreen;
	void InitD3Dpp();

	/* 隠しコンストラクタ */
	DirectGraphics() {};
	DirectGraphics(HWND hWnd,float h,float w,bool b);
	/* DirectGraphics 唯一のインスタンス */
	static DirectGraphics* pInstance;
};
#endif