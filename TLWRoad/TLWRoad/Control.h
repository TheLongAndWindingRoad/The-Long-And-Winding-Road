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

//�f�ނ̏��
struct ImageInfo {
	float sx;	//�f�ށ@u
	float sy;	//�f�ށ@v
	float w;
	float h;
	int clsn;
	int texid;
};

//�A�j���֌W
enum ANIMEPAT {
#include "animepat.dat"
	ANIMEMAX
};

//�A�j���[�V�����J��Ԃ��p�^�[��
enum REPEATPAT {
	LOOP,
	REVERSE
};

struct InfoAnime {
	int topanime;
	int animeNum;        //����
	int frameEx;         //�؂�ւ��^�C�~���O
	int frameN;          //���J�E���g��
	int animeNo;         //���A�j��No
	REPEATPAT repeatpat; //�J��Ԃ��p�^�[�� 0�ɖ߂�̂������Ԃ��̂�
	int addNo;           //+1��-1 
	bool round;			// true �P��
};

enum CHARDIST
{
	CH_LEFT,
	CH_RIGHT,
};

struct CHARA {
	float x;
	float y;
	float mvx;	//�ړ���
	float mvy;	//�ړ���
	ANIMEPAT ap;
	float ang;
	CHARDIST dist;
	float Jumping;	//y�����̈ړ��ʁ@�[�F�㏸�@�{�F���~�@�O�F���n
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
	int Fadeval;	// �t�F�[�h�Ԋu
	int FadeCnt;	// ���݂̓����x
	DWORD FadeCol;	// �ŏI�F
};

#ifdef DECLARE
InfoAnime infoAnime[] = 
{
	#include "anime.dat" 
};
#else
InfoAnime infoAnime[];
#endif

//AnimeNo��Y�����Ƃ��āA�f��No���擾����z��
#ifdef DECLARE
int imgNo[] = 
{
#include "AnimeSozai.dat"
};
#else
extern int imgNo[];
#endif

GLOBAL int SelHand; // ��D�̑I���@-1:���I��
GLOBAL int SelFieldX;
GLOBAL int SelFieldY;

//�v���g�^�C�v
void InitGame(void);
void InitAnime(enum ANIMEPAT no);
int  CtrlAnime(enum ANIMEPAT no);
int GetAnimeNo(ANIMEPAT no);
void MoveVertex(CUSTOMVERTEX cv[], float mx, float my);
ImageInfo GetImageInfo(ANIMEPAT ap);
bool Collision(float px, float py, float pw, float ph, float ex, float ey, float ew, float eh);
bool CollisionEx(float px, float py, float pw, float ph, float ex, float ey, float ew, float eh);
