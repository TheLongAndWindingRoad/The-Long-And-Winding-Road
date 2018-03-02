#include"DirectGraphics.h"
#include "..\macro.h"

/* DirectX9なのでここで初期化などを行えるが普通は毎回毎回設定するので純粋仮想関数にするべき */

/* 唯一のインスタンスをNULLで初期化 */
DirectGraphics* DirectGraphics::pInstance = NULL;

DirectGraphics::DirectGraphics(HWND hWnd,float h,float w,bool b):m_hWnd(hWnd),m_pD3Device(nullptr),m_pDirect3D(nullptr),m_gHeight(h),m_gWidth(w),m_fullscreen(b)
{
}

DirectGraphics::~DirectGraphics()
{
}

void DirectGraphics::CreateInstance(HWND hWnd, float h, float w,bool b)
{
	if (pInstance == NULL)
	{
		pInstance = new DirectGraphics(hWnd,h,w,b);
	}
}

void DirectGraphics::DestroyInstance()
{
	if (pInstance != nullptr)
	{
		SafeDelete(pInstance);
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
	ZeroMemory(&m_D3dppwnd, sizeof(D3DPRESENT_PARAMETERS));
	m_D3dppwnd.BackBufferWidth = m_gWidth;
	m_D3dppwnd.BackBufferHeight = m_gHeight;
	m_D3dppwnd.BackBufferFormat = m_D3DdisplayMode.Format;
	m_D3dppwnd.BackBufferCount = 1;
	m_D3dppwnd.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_D3dppwnd.Windowed = TRUE;

	ZeroMemory(&m_D3dppfull, sizeof(D3DPRESENT_PARAMETERS));
	m_D3dppfull.BackBufferWidth = m_gWidth;			// 幅
	m_D3dppfull.BackBufferHeight = m_gHeight;			// 高さ
	m_D3dppfull.BackBufferFormat = m_D3DdisplayMode.Format;
	m_D3dppfull.BackBufferCount = 1;
	m_D3dppfull.MultiSampleType = D3DMULTISAMPLE_NONE;
	m_D3dppfull.MultiSampleQuality = 0;
	m_D3dppfull.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_D3dppfull.hDeviceWindow = m_hWnd;
	m_D3dppfull.Windowed = FALSE;
	m_D3dppfull.EnableAutoDepthStencil = FALSE;
	m_D3dppfull.AutoDepthStencilFormat = D3DFMT_A1R5G5B5;
	m_D3dppfull.Flags = 0;
	m_D3dppfull.FullScreen_RefreshRateInHz = 0;
	m_D3dppfull.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;


	m_D3dpp = m_fullscreen ? m_D3dppfull : m_D3dppwnd;
}

bool DirectGraphics::Initialize()
{
	if (FAILED(m_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		MessageBox(0, "DirectXオブジェクトの生成に失敗しました", NULL, MB_OK);
	}

	if (FAILED(m_pDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &m_D3DdisplayMode)))
	{
		MessageBox(0, "DisplayModeの取得に失敗しました", NULL, MB_OK);
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
			MessageBox(0, "DirectXのデバイス生成に失敗しました", NULL, MB_OK);
			return false;
		}
	}

	SetRenderlingConfiguration();

	return true;
}

void DirectGraphics::Finalize()
{
	SafeRelease(m_pD3Device);
	SafeRelease(m_pDirect3D);
}

/* デフォルトは0,0,0で真っ白 */
void DirectGraphics::BeginScene(int r ,int g, int b)
{
	m_pD3Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(r, g, b), 1.0f, 0);
	m_pD3Device->BeginScene();
	m_pD3Device->SetFVF(D3DFVF_CUSTOMVERTEX);
}

void DirectGraphics::EndScene()
{
	m_pD3Device->EndScene();
	m_pD3Device->Present(NULL, NULL, NULL, NULL);
}
