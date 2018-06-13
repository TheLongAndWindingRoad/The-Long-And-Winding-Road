#ifdef DECLARE
#define GLOBAL /**/
#else
#define GLOBAL extern
#endif


#ifdef DECLARE
LPDIRECTINPUT8       pDInput = NULL;	// DirectInput�I�u�W�F�N�g
LPDIRECTINPUTDEVICE8 pDIMouse = NULL;	// �}�E�X�f�o�C�X
#else
extern LPDIRECTINPUT8       pDInput;
extern LPDIRECTINPUTDEVICE8 pDIMouse;
#endif

GLOBAL DIMOUSESTATE MouseState;			// �}�E�X���
GLOBAL DIMOUSESTATE MouseState_bak;	// �}�E�X���(�ω����m�p)

GLOBAL float Mx, My;


bool InitDInput(HINSTANCE hInstApp);
bool ReleaseDInput(void);
bool InitDInputMouse(void);
bool ReleaseDInputMouse(void);
void GetMouseState(void);

void DrawMouse(void);
bool MouseLButtonON(void);
