#ifdef DECLARE
#define GLOBAL /**/
#else
#define GLOBAL extern
#endif

struct DragonStatas {

	int Hp;
	int Pos_X;
	int Pos_Y;
	int Direct;
	int rsvDirectX;
	int rsvDirectY;
	int count;
	bool revers;
	bool fire;
};

GLOBAL DragonStatas DState;

void DragonInit();
void DragonAct(void);
void DrawDragon();