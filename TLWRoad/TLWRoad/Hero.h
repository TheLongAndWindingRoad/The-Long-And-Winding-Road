#ifdef DECLARE
#define GLOBAL /**/
#else
#define GLOBAL extern
#endif

struct HeroStatas {

	int Hp;
	int Pos_X;
	int Pos_Y;
	int Direct;
	int rsvDirectX;
	int rsvDirectY;
	bool hub;
};

GLOBAL HeroStatas HState;


void HeroInit(void);
void HeroAct(void);
void DrawHero(void);