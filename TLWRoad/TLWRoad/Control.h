#ifdef DECLARE
#define GLOBAL /**/
#else
#define GLOBAL extern
#endif

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define GRAV (1.0f)

struct CUSTOMVERTEX
{
	float	x, y, z, rhw;
	unsigned long	color;
	float	tu, tv;
};

//素材の情報
struct ImageInfo {
	float sx;	//素材　u
	float sy;	//素材　v
	float w;
	float h;
	int clsn;
	int texid;
};

//アニメ関係
enum ANIMEPAT {
#include "animepat.dat"
	ANIMEMAX
};

//アニメーション繰り返しパターン
enum REPEATPAT {
	LOOP,
	REVERSE
};

struct InfoAnime {
	int topanime;
	int animeNum;        //枚数
	int frameEx;         //切り替えタイミング
	int frameN;          //現カウント数
	int animeNo;         //現アニメNo
	REPEATPAT repeatpat; //繰り返しパターン 0に戻るのか引き返すのか
	int addNo;           //+1か-1 
	bool round;			// true １周
};

enum CHARDIST
{
	CH_LEFT,
	CH_RIGHT,
};

struct CHARA {
	float x;
	float y;
	float mvx;	//移動量
	float mvy;	//移動量
	ANIMEPAT ap;
	float ang;
	CHARDIST dist;
	float Jumping;	//y方向の移動量　ー：上昇　＋：下降　０：着地
	int	HP;
};

enum CHARSTATE
{
	WAIT,
	JUMP,
	UPING,
	DWING,
	LABEL,
	ITEM
};

struct BasePoint {
	float x;
	float y;
};

GLOBAL BasePoint BP;

struct FadeIO {
	int Fadeval;	// フェード間隔
	int FadeCnt;	// 現在の透明度
	DWORD FadeCol;	// 最終色
};

#ifdef DECLARE
InfoAnime infoAnime[] = 
{
	#include "anime.dat" 
};
#else
InfoAnime infoAnime[];
#endif

//AnimeNoを添え字として、素材Noを取得する配列
#ifdef DECLARE
int imgNo[] = 
{
#include "AnimeSozai.dat"
};
#else
extern int imgNo[];
#endif

GLOBAL int SelHand; // 手札の選択　-1:未選択
GLOBAL int SelFieldX;
GLOBAL int SelFieldY;

//プロトタイプ
void InitGame(void);
void InitAnime(enum ANIMEPAT no);
int  CtrlAnime(enum ANIMEPAT no);
int GetAnimeNo(ANIMEPAT no);
void MoveVertex(CUSTOMVERTEX cv[], float mx, float my);
ImageInfo GetImageInfo(ANIMEPAT ap);
bool Collision(float px, float py, float pw, float ph, float ex, float ey, float ew, float eh);
bool CollisionEx(float px, float py, float pw, float ph, float ex, float ey, float ew, float eh);
