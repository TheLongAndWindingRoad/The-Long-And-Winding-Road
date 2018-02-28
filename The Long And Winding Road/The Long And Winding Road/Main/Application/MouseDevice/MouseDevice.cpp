#include"MouseDevice.h"
#include"DirectX9\macro.h"

/* マウスのバッファーの大きさ */
#define BUFFER_SIZE 64

MouseDevice* MouseDevice::pInstance = NULL;

MouseDevice::MouseDevice(HWND hWnd) :m_hWnd(hWnd)
{
}

MouseDevice::~MouseDevice()
{
	if (m_pDIMouse)
	{
		m_pDIMouse->Unacquire();
	}
	SafeRelease(m_pDIMouse);
	DestroyMouseDevice();
}


void MouseDevice::InitDinput()
{
	/* DirectInputオブジェクトの作成 */
	if (FAILED(DirectInput8Create(
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(VOID**)&m_pDinput,
		NULL)))
	{
		MessageBox(0, "DirectInputの作成に失敗しました", NULL, MB_OK);
	}
}

bool MouseDevice::Initalize()
{
	/* マウスの初期化 */
	if (FAILED(m_pDinput->CreateDevice(
		GUID_SysMouse,
		&m_pDIMouse,
		NULL)))
	{
		MessageBox(0, "DirectInputの作成に失敗しました", NULL, MB_OK);
		return false;
	}

	/* データフォーマット */
	if (FAILED(m_pDIMouse->SetDataFormat(&c_dfDIMouse)))
	{
		MessageBox(0, "DirectInputの作成に失敗しました", NULL, MB_OK);
		return false;
	}

	/* 協調レベルの設定 */
	if (FAILED(m_pDIMouse->SetCooperativeLevel(m_hWnd,
		DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		MessageBox(0, "DirectInputの作成に失敗しました", NULL, MB_OK);
		return false;
	}

	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;

	if (FAILED(m_pDIMouse->SetProperty(
		DIPROP_AXISMODE,
		&diprop.diph)))
	{
		MessageBox(0, "DirectInputの作成に失敗しました", NULL, MB_OK);
		return false;
	}

	diprop.dwData = BUFFER_SIZE;

	if (FAILED(m_pDIMouse->SetProperty(
		DIPROP_BUFFERSIZE,
		&diprop.diph)))
	{
		MessageBox(0, "DirectInputの作成に失敗しました", NULL, MB_OK);
		return false;
	}
	m_pDIMouse->Acquire();
	return true;
}

void MouseDevice::MouseCheck(MOUSEKIND* Mouse)
{
	DIMOUSESTATE MouseState;

	m_pDIMouse->Acquire();
	HRESULT hr = m_pDIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &MouseState);
	if (SUCCEEDED(hr))
	{
		if (MouseState.rgbButtons[0])
		{
			Mouse->IsLeftClick = true;
		}
		else
		{
			Mouse->IsLeftClick = false;
		}

		if (MouseState.rgbButtons[1])
		{
			Mouse->IsRightClick = true;
		}
		else
		{
			Mouse->IsRightClick = false;
		}

		if (MouseState.lX)
		{
			Mouse->lx = MouseState.lX;
		}

		if (MouseState.lY)
		{
			Mouse->ly = MouseState.lY;
		}

		if (MouseState.lZ)
		{
			Mouse->lz = MouseState.lZ;
		}
	}
}

void MouseDevice::CreatepInstance(HWND hWnd)
{
	if (!pInstance)
	{
		pInstance = new MouseDevice(hWnd);
	}
}

void MouseDevice::DestroyMouseDevice()
{
	SafeDelete(pInstance);
}