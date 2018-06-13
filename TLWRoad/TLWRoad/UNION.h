#ifdef DECLARE
#define GLOBAL /**/
#else
#define GLOBAL extern
#endif

#define RELEASE(x) if(x){x->Release();x=NULL;}

#define WIN_W 1440
#define WIN_H 810

struct SCORE {
	int RCrash;
	int RTime;
	int RScore;

	int HiRCrash;
	int HiRTime;
	int HiRScore;

	int BestRCrash;
	int BestRTime;
};

GLOBAL HWND hWnd;

GLOBAL D3DPRESENT_PARAMETERS d3dppWin, d3dppFull;
GLOBAL	RECT WinRect;			//Window Mode Ç≈ÇÃà íuëÂÇ´Ç≥
GLOBAL	bool WinAct;
GLOBAL	bool WinMode;	//true:WindowÅ@false:Full
GLOBAL	bool DeviceLost;

GLOBAL SCORE Score;
GLOBAL int UnitScore;

enum SNDKIND {
	S_BGM,
	S_GLASS,
	SOUNDMAX,
};