#include <minwindef.h>


#ifdef DECLARE
#define GLOBAL /**/
#else
#define GLOBAL extern
#endif



enum {

	NONE,
	TITLESCENE,
	GAMEMAIN,
	OPTION,
	CLEAR,
	RESULT,
	END
};

GLOBAL int PrevScene;
GLOBAL int Scene;
GLOBAL FadeIO SceneFade;

void GameMainInit();


void InitScene(void);
void ControlScene(void);
void DrawScene(void);

void TitleInit();
void TitleDraw();

int TitleControl();

int GameMainControl();
int OptionControl();
int ClearControl();
//int ResultControl();

int Title();
int GameMain();
int Option();
int Clear();
//int Result();

void InitFadeScene(DWORD FadeCol);
void StartFadeScene(int FadeVal);
bool FadeScene(void);
