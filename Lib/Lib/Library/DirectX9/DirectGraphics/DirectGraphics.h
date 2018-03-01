#ifndef DIRECTGRAPHICS_H
#define	DIRECTGRAPHICS_H

#define D3DFVF_CUSTOMVERTEX ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#include<d3dx9.h>
#include<d3d9.h>

/* �����̓V���O���g���������� */

class DirectGraphics
{
public:
	/* ����֐� */
	~DirectGraphics();

	static void CreateInstance(HWND hWnd, float h, float w,bool b);

	void SetRenderlingConfiguration();
	bool Initialize();
	void Finalize();
	void BeginScene(int r, int g, int b);
	void EndScene();

	inline LPDIRECT3DDEVICE9 GetDevice() { return m_pD3Device; }

	/* �C���X�^���X�̎擾��static�֐��ɂ��邱�ƂŃO���[�o���A�N�Z�X�ɂ��Ă��� */
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

	/* �B���R���X�g���N�^ */
	DirectGraphics() {};
	DirectGraphics(HWND hWnd,float h,float w,bool b);
	/* DirectGraphics �B��̃C���X�^���X */
	static DirectGraphics* pInstance;
};
#endif