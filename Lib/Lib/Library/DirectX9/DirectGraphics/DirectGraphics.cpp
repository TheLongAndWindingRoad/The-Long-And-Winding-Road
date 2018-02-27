#include"DirectGraphics.h"
#include "..\macro.h"

/* DirectX9なのでここで初期化などを行えるが普通は毎回毎回設定するので純粋仮想関数にするべき */

/* 唯一のインスタンスをNULLで初期化 */
DirectGraphics* DirectGraphics::pInstance = NULL;

DirectGraphics::DirectGraphics(HWND hWnd,float h,float w,bool b):m_hWnd(hWnd),m_pD3Device(nullptr),m_pDirect3D(nullptr),m_gHeight(h),m_gWidth(w),m_fullscreen(b)
{
	Initalize();
}

DirectGraphics::~DirectGraphics()
{
	Finalize();
}

void DirectGraphics::CreateInstance(HWND hWnd, float h, float w,bool b)
{
	if (pInstance == NULL)
	{
		pInstance = new DirectGraphics(hWnd,h,w,b);
	}
}

/* GetRenderState */
void DirectGraphics::SetRenderlingConfiguration()
{
	m_pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_pD3Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
}

void DirectGraphics::InitD3Dpp()
{
	ZeroMemory(&m_D3dpp, sizeof(D3DPRESENT_PARAMETERS));
	m_D3dpp.BackBufferWidth = m_gWidth;
	m_D3dpp.BackBufferHeight = m_gHeight;
	m_D3dpp.BackBufferFormat = m_D3DdisplayMode.Format;
	m_D3dpp.BackBufferCount = 1;
	m_D3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_D3dpp.Windowed = TRUE;
}

bool DirectGraphics::Initalize()
{
	m_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);
	m_pDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &m_D3DdisplayMode);

	if (m_pDirect3D == nullptr)
	{
		return false;
	}

	InitD3Dpp();

	/* HALMode */
	if (FAILED(m_pDirect3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		m_hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&m_D3dpp, &m_pD3Device)))
	{
		/* REFmode */
		if (FAILED(m_pDirect3D->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_REF,
			m_hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&m_D3dpp, &m_pD3Device)))
		{
			return false;
		}
	}

	SetRenderlingConfiguration();

	return true;
}

void DirectGraphics::Finalize()
{
	SafeDelete(pInstance);
	SafeRelease(m_pD3Device);
	SafeRelease(m_pDirect3D);
}

/* デフォルトは0,0,0で真っ白 */
void DirectGraphics::BeginScene(int r ,int g, int b)
{
	m_pD3Device->SetFVF(D3DFVF_CUSTOMVERTEX);
	m_pD3Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(r, g, b), 1.0f, 0);
	m_pD3Device->BeginScene();
}

void DirectGraphics::EndScene()
{
	m_pD3Device->EndScene();
	m_pD3Device->Present(NULL, NULL, NULL, NULL);
}
