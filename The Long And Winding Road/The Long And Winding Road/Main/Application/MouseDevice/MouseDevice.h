#ifndef MOUSEDEVICE_H 
#define	MOUSEDEVICE_H

#include <dinput.h>

typedef struct
{
	bool IsLeftClick, IsRightClick;	//!< クリック情報(クリックされていればtrue).
	int lx, ly, lz;					//!< マウスの移動量.

} MOUSEKIND;

class MouseDevice
{
public:
	/* デストラクタ関数 */
	~MouseDevice();

	/* Dinutオブジェクトの作成 */
	void InitDinput();

	/* 初期化関数 */
	bool Initialize();

	/* マウスのチェック関数 */
	void MouseCheck(MOUSEKIND* Mouse);

	/* MouseDeviceの生成 */
	static void CreatepInstance(HWND hWnd);

	/* インスタンスのdelete */
	static void DestroyMouseDevice();

	/* インスタンスを返す */
	static MouseDevice*	GetpInstance() { return pInstance; }

	/* マウスの座標を返す */
	inline POINT GetMousePos() { GetCursorPos(&m_po); return m_po; }
private:
	/* 隠しコンストラクタ */
	MouseDevice(HWND hWnd);

	/* 唯一のインスタンス */
	static MouseDevice* pInstance;

	LPDIRECTINPUT8 m_pDinput = NULL; //設定

	/* マウスデバイス */
	LPDIRECTINPUTDEVICE8 m_pDIMouse = NULL;

	HWND m_hWnd;

	POINT m_po;
};


#endif 