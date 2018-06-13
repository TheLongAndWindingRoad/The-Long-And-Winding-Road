#ifdef DECLARE
#define GLOBAL /**/
#else
#define GLOBAL extern
#endif


#ifdef DECLARE
LPDIRECTINPUT8       pDInput = NULL;	// DirectInputオブジェクト
LPDIRECTINPUTDEVICE8 pDIMouse = NULL;	// マウスデバイス
#else
extern LPDIRECTINPUT8       pDInput;
extern LPDIRECTINPUTDEVICE8 pDIMouse;
#endif

GLOBAL DIMOUSESTATE MouseState;			// マウス状態
GLOBAL DIMOUSESTATE MouseState_bak;	// マウス情報(変化検知用)

GLOBAL float Mx, My;


bool InitDInput(HINSTANCE hInstApp);
bool ReleaseDInput(void);
bool InitDInputMouse(void);
bool ReleaseDInputMouse(void);
void GetMouseState(void);

void DrawMouse(void);
bool MouseLButtonON(void);
