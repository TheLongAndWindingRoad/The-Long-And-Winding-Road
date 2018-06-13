#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include <d3dx9tex.h>
#include <dinput.h>
#include <dsound.h>

#define DECLARE

#include "UNION.h"
#include "MouseControl.h"
#include "Control.h"	//Control.hがRender.hの手前
#include "Render.h"
#include "SceneManager.h"
#include "Maps.h"



#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#define GAMETITLE TEXT("The Long And Winding Road")

//-------------------------------------------------------------
//
//	初期化処理
//
//-------------------------------------------------------------
void Init(HINSTANCE hInstance)
{
	FILE *fp;

	InitDInput(hInstance);
	InitDInputMouse();

	InitScene();

	if ((fopen_s(&fp, "GS.dat", "r+b")) == NULL) {
		fread(&Score, sizeof(SCORE), 1, fp);
		fclose(fp);
	}
	else {
		Score.RCrash = 0;
		Score.RTime = 0;
		Score.RScore = 0;
		Score.HiRCrash = 0;
		Score.HiRTime = 0;
		Score.HiRScore = 0;
		Score.BestRCrash = 0;
		Score.BestRTime = 0;
	}

	UnitScore = 0;

	GameMainInit();
}

//-------------------------------------------------------------
//
//	制御処理
//
//-------------------------------------------------------------
void Control(void)
{
	GetMouseState();
	ControlScene();

}

//-------------------------------------------------------------
//
//	描画処理
//
//-------------------------------------------------------------
void Render(void)
{
	if (!pD3Device) return;

	//描画方法の設定
	SetRender();
	//画面の消去
	ClearScreen();
	//描画の開始
	pD3Device->BeginScene();
	//画像の描画
	pD3Device->SetFVF(D3DFVF_CUSTOMVERTEX);

	DrawScene();
	DrawMouse();

	//描画の終了
	pD3Device->EndScene();
	//表示
	pD3Device->Present(NULL, NULL, NULL, NULL);
}

//-------------------------------------------------------------
//
// 画面モードの変更
// 
//-------------------------------------------------------------
void ChangeDisplayMode(void)
{
	WinMode = !WinMode;

	if (WinMode) {
		d3dpp = d3dppWin;
	}
	else {
		d3dpp = d3dppFull;
		GetWindowRect(hWnd, &WinRect);
	}

	HRESULT hr = pD3Device->Reset(&d3dpp);
	if (FAILED(hr)) {
		if (hr == D3DERR_DEVICELOST) {
			DeviceLost = true;
		}
		else {
			DestroyWindow(hWnd);
		}
		return;
	}

	if (WinMode) {
		SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
		SetWindowPos(hWnd, HWND_NOTOPMOST,
			WinRect.left, WinRect.top,
			WinRect.right - WinRect.left,
			WinRect.bottom - WinRect.top,
			SWP_SHOWWINDOW);
	}
	else {
		SetWindowLong(hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
	}
}
//-------------------------------------------------------------
//
// ウインドウ・サイズの変更
//
//-------------------------------------------------------------
HRESULT ChangeWindowSize(void)
{
	// ウインドウのクライアント領域に合わせる

	HRESULT hr = pD3Device->Reset(&d3dpp);
	if (FAILED(hr)) {
		if (hr == D3DERR_DEVICELOST) {
			DeviceLost = true;
		}
	}
	else {
		DestroyWindow(hWnd);
	}
 
	// ビューポートの設定
	D3DVIEWPORT9 vp;
	vp.X  = 0;
	vp.Y  = 0;
	vp.Width = d3dpp.BackBufferWidth;
	vp.Height = d3dpp.BackBufferHeight;
	vp.MinZ  = 0.0f;
	vp.MaxZ  = 1.0f;
	hr = pD3Device->SetViewport(&vp);
	if (FAILED(hr)) {
		DestroyWindow(hWnd);
	}
	return hr;
}

//-------------------------------------------------------------
//
//	メッセージ処理
//
//-------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd , UINT msg , WPARAM wp , LPARAM lp) {

	switch (msg) {
	case WM_ACTIVATE:
		ReleaseDInputMouse();  //Added 12/27
		WinAct = (LOWORD(wp) != 0);
		break;

	case WM_DESTROY:
		ReleaseDInputMouse();	// DirectInput(Mouse)オブジェクトの開放
		ReleaseDInput();		// DirectInputオブジェクトの開放

		RELEASE(pD3Device);
		RELEASE(pDirect3D);

		PostQuitMessage(0);
		hWnd = NULL;
		return 0;

	case WM_SIZE:
		ReleaseDInputMouse();	//Added 12/27
		if (d3dpp.Windowed != TRUE)
			break;

		if (pD3Device || wp == SIZE_MINIMIZED)
			break;
		d3dpp.BackBufferWidth = LOWORD(lp);
		d3dpp.BackBufferHeight = HIWORD(lp);
		if (DeviceLost)
			break;
		if (wp == SIZE_MAXIMIZED || wp == SIZE_RESTORED)
			ChangeWindowSize();
		break;

	case WM_SETCURSOR:
		if (d3dpp.Windowed != TRUE) {
			SetCursor(NULL);
			return 1;
		}
		break;

	case WM_KEYDOWN:
		// キー入力の処理
		switch (wp) {
			case VK_ESCAPE: // [ESCAPE]キーでウインドウを閉じる
				PostMessage(hWnd, WM_CLOSE, 0, 0);
				break;
			}
			break;
	case WM_SYSKEYDOWN:     // Alt + 特殊キーの処理に使う
		switch (wp) {
		case VK_RETURN:     // Alt + Enterを押すと切り替え
			ChangeDisplayMode();
			break;
		default:
			break;
		}
		break;

	}
	return DefWindowProc(hWnd , msg , wp , lp);
}

//-------------------------------------------------------------
//
//	メインルーチン
//
//-------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance , HINSTANCE hPrevInstance ,
			PSTR lpCmdLine , int nCmdShow) {
	MSG msg;
	WNDCLASS winc;
	D3DDISPLAYMODE d3ddm;

//	ImmDisableIME(-1); // このスレッドでIME禁止
	WinAct = false;
	WinMode = true;	//true:Window　false:Full
	DeviceLost = false;


	//DirectX オブジェクトの生成
	pDirect3D = Direct3DCreate9(
		        D3D_SDK_VERSION);
	//Display Mode の設定
	pDirect3D->GetAdapterDisplayMode(
				D3DADAPTER_DEFAULT,
				&d3ddm);

	//Windows情報の設定
	winc.style 			= CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc	= WndProc;
	winc.cbClsExtra		= winc.cbWndExtra = 0;
	winc.hInstance		= hInstance;
	winc.hIcon			= LoadIcon(NULL , IDI_APPLICATION);
	winc.hCursor		= LoadCursor(NULL , IDC_ARROW);
	winc.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName	= NULL;
	winc.lpszClassName	= GAMETITLE;
	//Windowsの登録
	if (!RegisterClass(&winc)) return 0;

	int dH = GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYFRAME) * 4;
	int dW = GetSystemMetrics(SM_CYFRAME) * 5;

	if (WinMode) {
		hWnd = CreateWindow(
			GAMETITLE,
			GAMETITLE,
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT,		// x
			CW_USEDEFAULT,		// y
			WIN_W + dW,		// Width
			WIN_H + dH,		// Height
			NULL, NULL, hInstance, NULL
		);
	}
	else {
		hWnd = CreateWindow(
			GAMETITLE,
			GAMETITLE,
			WS_POPUP | WS_VISIBLE,
			0,		// x
			0,		// y
			WIN_W,		// Width
			WIN_H,		// Height
			NULL, NULL, hInstance, NULL
		);
	}
	if (!hWnd) return 0;

	//Window
	ZeroMemory(&d3dppWin, sizeof(D3DPRESENT_PARAMETERS));
	d3dppWin.BackBufferWidth = 0;
	d3dppWin.BackBufferHeight = 0;
	d3dppWin.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dppWin.BackBufferCount = 1;
	d3dppWin.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dppWin.MultiSampleQuality = 0;
	d3dppWin.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dppWin.hDeviceWindow = hWnd;
	d3dppWin.Windowed = TRUE;
	d3dppWin.EnableAutoDepthStencil = FALSE;
	d3dppWin.AutoDepthStencilFormat = D3DFMT_A1R5G5B5;
	d3dppWin.Flags = 0;
	d3dppWin.FullScreen_RefreshRateInHz = 0;
	d3dppWin.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	//Full
	ZeroMemory(&d3dppFull, sizeof(D3DPRESENT_PARAMETERS));
	d3dppFull.BackBufferWidth = WIN_W;
	d3dppFull.BackBufferHeight = WIN_H;
	d3dppFull.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dppFull.BackBufferCount = 1;
	d3dppFull.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dppFull.MultiSampleQuality = 0;
	d3dppFull.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dppFull.hDeviceWindow = hWnd;
	d3dppFull.Windowed = FALSE;
	d3dppFull.EnableAutoDepthStencil = FALSE;
	d3dppFull.AutoDepthStencilFormat = D3DFMT_A1R5G5B5;
	d3dppFull.Flags = 0;
	d3dppFull.FullScreen_RefreshRateInHz = 0;
	d3dppFull.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	d3dpp = (WinMode) ? d3dppWin : d3dppFull;

	HRESULT hr = pDirect3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &pD3Device);
	if (FAILED(hr)) {
		hr = pDirect3D->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_REF,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &pD3Device);
		if (FAILED(hr)) {
			return 1;
		}
	}
	// ビューポートの設定
	D3DVIEWPORT9 vp;
	vp.X = 0;
	vp.Y = 0;
	vp.Width = d3dpp.BackBufferWidth;
	vp.Height = d3dpp.BackBufferHeight;
	vp.MinZ = 0.0f;
	vp.MaxZ = 1.0f;
	hr = pD3Device->SetViewport(&vp);
	if (FAILED(hr)) {
		return 2;
	}

	for (int i = 0; i < TEXMAX; i++) {
		if (LoadTexture(TexInfo[i].fname, i)) {
			return 0;
		}
	}

	Init(hInstance);

	DWORD SyncOld = timeGetTime();
	DWORD SyncNow;

	timeBeginPeriod(1);

	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT) {
		Sleep(1);
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			SyncNow = timeGetTime();
			if (SyncNow - SyncOld >= 1000 / 60) {
				Control();
				Render();
				SyncOld = SyncNow;
			}
		}
	}

	timeEndPeriod(1);

	FILE *fp;
	if (fopen_s(&fp, "GS.dat", "w+b") == NULL) {
		fwrite(&Score, sizeof(SCORE), 1, fp);
		fclose(fp);
	}


	// ウインドウ・クラスの登録解除
	UnregisterClass(GAMETITLE, hInstance);

	return (int)msg.wParam;
}
