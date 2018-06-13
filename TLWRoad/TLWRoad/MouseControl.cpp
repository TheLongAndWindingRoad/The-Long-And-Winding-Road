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


BOOL bAppActive = FALSE;			// �A�v���P�[�V�����A�N�e�B�u�t���O
RECT rcClip;           // new area for ClipCursor
RECT rcOldClip;        // previous area for ClipCursor

//-----------------------------------------------------------------------------
// DirectInput�̏���������
//-----------------------------------------------------------------------------
bool InitDInput(HINSTANCE hInstApp)
{
	HRESULT ret = DirectInput8Create(hInstApp, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&pDInput, NULL);
	if (FAILED(ret)) {
		return false;	// �쐬�Ɏ��s
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
// DirectInput�̏I������
//-----------------------------------------------------------------------------
bool ReleaseDInput(void)
{
	// DirectInput�̃f�o�C�X���J��
	if (pDInput) {
		pDInput->Release();
		pDInput = NULL;
	}

	ClipCursor(&rcOldClip);
	ShowCursor(true);
	return true;
}

//-----------------------------------------------------------------------------
// DirectInput�̃}�E�X�f�o�C�X�p�̏���������
//-----------------------------------------------------------------------------
bool InitDInputMouse(void)
{
	HRESULT ret = S_FALSE;
	if (pDInput == NULL) {
		return false;
	}

	// �}�E�X�p�Ƀf�o�C�X�I�u�W�F�N�g���쐬
	ret = pDInput->CreateDevice(GUID_SysMouse, &pDIMouse, NULL);
	if (FAILED(ret)) {
		// �f�o�C�X�̍쐬�Ɏ��s
		return false;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	ret = pDIMouse->SetDataFormat(&c_dfDIMouse);	// �}�E�X�p�̃f�[�^�E�t�H�[�}�b�g��ݒ�
	if (FAILED(ret)) {
		// �f�[�^�t�H�[�}�b�g�Ɏ��s
		return false;
	}

	// ���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	ret = pDIMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(ret)) {
		// ���[�h�̐ݒ�Ɏ��s
		return false;
	}

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	// ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j

	ret = pDIMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph);
	if (FAILED(ret)) {
		// �f�o�C�X�̐ݒ�Ɏ��s
		return false;
	}

	// ���͐���J�n
	pDIMouse->Acquire();

	return true;
}
//-----------------------------------------------------------------------------
// DirectInput�̃}�E�X�f�o�C�X�p�̉������
//-----------------------------------------------------------------------------
bool ReleaseDInputMouse(void)
{
	// DirectInput�̃f�o�C�X���J��
	if (pDIMouse) {
		pDIMouse->Release();
		pDIMouse = NULL;
	}

	return true;

}

//-----------------------------------------------------------------------------
// DirectInput�̃}�E�X�f�o�C�X��Ԏ擾����
//-----------------------------------------------------------------------------
void GetMouseState(void)
{
	if (pDIMouse == NULL) {
		InitDInputMouse();
	}

	// �ǎ�O�̒l��ێ����܂�
	memcpy(&MouseState_bak, &MouseState, sizeof(MouseState_bak));

	// �}�E�X�̏�Ԃ��擾���܂�
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
	{	//���N���b�N���ꂽ��
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