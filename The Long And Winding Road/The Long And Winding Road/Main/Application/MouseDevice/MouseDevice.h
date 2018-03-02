#ifndef MOUSEDEVICE_H 
#define	MOUSEDEVICE_H

#include <dinput.h>

typedef struct
{
	bool IsLeftClick, IsRightClick;	//!< �N���b�N���(�N���b�N����Ă����true).
	int lx, ly, lz;					//!< �}�E�X�̈ړ���.

} MOUSEKIND;

class MouseDevice
{
public:
	/* �f�X�g���N�^�֐� */
	~MouseDevice();

	/* Dinut�I�u�W�F�N�g�̍쐬 */
	void InitDinput();

	/* �������֐� */
	bool Initialize();

	/* �}�E�X�̃`�F�b�N�֐� */
	void MouseCheck(MOUSEKIND* Mouse);

	/* MouseDevice�̐��� */
	static void CreatepInstance(HWND hWnd);

	/* �C���X�^���X��delete */
	static void DestroyMouseDevice();

	/* �C���X�^���X��Ԃ� */
	static MouseDevice*	GetpInstance() { return pInstance; }

	/* �}�E�X�̍��W��Ԃ� */
	inline POINT GetMousePos() { GetCursorPos(&m_po); return m_po; }
private:
	/* �B���R���X�g���N�^ */
	MouseDevice(HWND hWnd);

	/* �B��̃C���X�^���X */
	static MouseDevice* pInstance;

	LPDIRECTINPUT8 m_pDinput = NULL; //�ݒ�

	/* �}�E�X�f�o�C�X */
	LPDIRECTINPUTDEVICE8 m_pDIMouse = NULL;

	HWND m_hWnd;

	POINT m_po;
};


#endif 