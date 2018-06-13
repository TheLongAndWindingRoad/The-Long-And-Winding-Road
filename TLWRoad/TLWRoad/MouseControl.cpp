#include <windows.h>
#include <stdio.h>
#include <d3dx9.h>
#include <d3dx9tex.h>
#include <dinput.h>

#include "UNION.h"
#include "Control.h"
#include "Render.h"
#include "MouseControl.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")


BOOL bAppActive = FALSE;			// アプリケーションアクティブフラグ
RECT rcClip;           // new area for ClipCursor
RECT rcOldClip;        // previous area for ClipCursor

//-----------------------------------------------------------------------------
// DirectInputの初期化処理
//-----------------------------------------------------------------------------
bool InitDInput(HINSTANCE hInstApp)
{
	HRESULT ret = DirectInput8Create(hInstApp, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&pDInput, NULL);
	if (FAILED(ret)) {
		return false;	// 作成に失敗
	}

	GetClipCursor(&rcOldClip);
	GetWindowRect(hWnd, &rcClip);

	rcClip.left += 32.0f;
	rcClip.right -= 32.0f;
	rcClip.top += 32.0f;
	rcClip.bottom -= 32.0f;

	ClipCursor(&rcClip);

	ShowCursor(false);

	Mx = WIN_W / 2.0f;
	My = WIN_H / 2.0f;

	return true;
}
//-----------------------------------------------------------------------------
// DirectInputの終了処理
//-----------------------------------------------------------------------------
bool ReleaseDInput(void)
{
	// DirectInputのデバイスを開放
	if (pDInput) {
		pDInput->Release();
		pDInput = NULL;
	}

	ClipCursor(&rcOldClip);
	ShowCursor(true);
	return true;
}

//-----------------------------------------------------------------------------
// DirectInputのマウスデバイス用の初期化処理
//-----------------------------------------------------------------------------
bool InitDInputMouse(void)
{
	HRESULT ret = S_FALSE;
	if (pDInput == NULL) {
		return false;
	}

	// マウス用にデバイスオブジェクトを作成
	ret = pDInput->CreateDevice(GUID_SysMouse, &pDIMouse, NULL);
	if (FAILED(ret)) {
		// デバイスの作成に失敗
		return false;
	}

	// データフォーマットを設定
	ret = pDIMouse->SetDataFormat(&c_dfDIMouse);	// マウス用のデータ・フォーマットを設定
	if (FAILED(ret)) {
		// データフォーマットに失敗
		return false;
	}

	// モードを設定（フォアグラウンド＆非排他モード）
	ret = pDIMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(ret)) {
		// モードの設定に失敗
		return false;
	}

	// デバイスの設定
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	// 相対値モードで設定（絶対値はDIPROPAXISMODE_ABS）

	ret = pDIMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph);
	if (FAILED(ret)) {
		// デバイスの設定に失敗
		return false;
	}

	// 入力制御開始
	pDIMouse->Acquire();

	return true;
}
//-----------------------------------------------------------------------------
// DirectInputのマウスデバイス用の解放処理
//-----------------------------------------------------------------------------
bool ReleaseDInputMouse(void)
{
	// DirectInputのデバイスを開放
	if (pDIMouse) {
		pDIMouse->Release();
		pDIMouse = NULL;
	}

	return true;

}

//-----------------------------------------------------------------------------
// DirectInputのマウスデバイス状態取得処理
//-----------------------------------------------------------------------------
void GetMouseState(void)
{
	if (pDIMouse == NULL) {
		InitDInputMouse();
	}

	// 読取前の値を保持します
	memcpy(&MouseState_bak, &MouseState, sizeof(MouseState_bak));

	// マウスの状態を取得します
	HRESULT	hr = pDIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &MouseState);
	if (hr == DIERR_INPUTLOST) {
		pDIMouse->Acquire();
		hr = pDIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &MouseState);
	}
	Mx += (float)MouseState.lX;
	My += (float)MouseState.lY;

	if (Mx < 10.0f) Mx = 10.0f;
	if (Mx > WIN_W - 16.0f) Mx = WIN_W - 16.0f;
	if (My < 12.0f) My = 12.0f;
	if (My > WIN_H - 24.0f) My = WIN_H - 24.0f;

}

void DrawMouse(void)
{

	if (MouseState.rgbButtons[0] & 0x80) 
	{	//左クリックされたら
		DrawAnime(A_CURSOR2, Mx + 3.0, (My + 4.0) + BP.y, 1.0f, 0, 0.0f);
	}
	else
	{
		DrawAnime(A_CURSOR1, Mx + 3.0, (My + 4.0)+ BP.y, 1.0f, 0, 0.0f);
	}
}

bool MouseLButtonON(void)
{
	return (!(MouseState_bak.rgbButtons[0] & 0x80)) && (MouseState.rgbButtons[0] & 0x80);
}