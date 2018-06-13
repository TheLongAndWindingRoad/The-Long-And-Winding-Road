#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include <d3dx9tex.h>

#include "UNION.h"
#include "Control.h"
#include "Render.h"

void InitGame(void)
{
}

void InitAnime(ANIMEPAT no)
{

	infoAnime[no].frameN = 0;
	infoAnime[no].animeNo = 0;
	infoAnime[no].addNo = 1;

}

int CtrlAnime(ANIMEPAT no) {

	infoAnime[no].round = false;
	//毎フレームインクリメント
	infoAnime[no].frameN++;
	//もしフレームNOが切り替えタイミングの数字以上になったら
	if (infoAnime[no].frameN >= infoAnime[no].frameEx) {

		//次の絵に切り替え
		infoAnime[no].animeNo += infoAnime[no].addNo;
		//トップアニメ番号がアニメ枚数の数字を超えるもしくは0を下回ったら
		if (infoAnime[no].animeNo >= infoAnime[no].animeNum ||
			infoAnime[no].animeNo < 0) {
			infoAnime[no].round = true;
			//ループパターンによって分岐
			if (infoAnime[no].repeatpat == LOOP) {
				infoAnime[no].animeNo = 0;
			}
			else if (infoAnime[no].repeatpat == REVERSE) {
				infoAnime[no].addNo *= -1;
				infoAnime[no].animeNo = infoAnime[no].animeNo + infoAnime[no].addNo * 2;
			}
		}
		//フレームを０に戻す
		infoAnime[no].frameN = 0;
	}
	int ret = infoAnime[no].topanime + infoAnime[no].animeNo;
	return ret;
}

int GetAnimeNo(ANIMEPAT no)
{
	return infoAnime[no].topanime + infoAnime[no].animeNo;
}

void MoveVertex(CUSTOMVERTEX cv[], float mx, float my)
{
	for (int i = 0 ; i < 4 ; i++) {
		cv[i].x += mx;
		cv[i].y += my;
	}
}

//アニメNoに対する素材情報を得る
ImageInfo GetImageInfo(ANIMEPAT ap)
{
	int imgId;
	ImageInfo imgInfo;

	imgId = imgNo[GetAnimeNo(ap)];	//アニメNoに対する素材番号を得る
	imgInfo = ImgInfo[imgId];

	return imgInfo;
}

//あたり判定
//　x,y座標　中央点
bool Collision(float px, float py, float pw, float ph, float ex, float ey, float ew, float eh)
{
	float px1, px2, py1, py2;
	float ex1, ex2, ey1, ey2;

	px1 = px - pw / 2.0f;
	px2 = px + pw / 2.0f;
	py1 = py - ph / 2.0f;
	py2 = py + ph / 2.0f;
	ex1 = ex - ew / 2.0f;
	ex2 = ex + ew / 2.0f;
	ey1 = ey - eh / 2.0f;
	ey2 = ey + eh / 2.0f;

	return (px1 <= ex2 && ex1 <= px2 && py1 <= ey2 && ey1 <= py2);
}

//　x,y座標　中央点 ｐの上側　ｅの下側
bool CollisionEx(float px, float py, float pw, float ph, float ex, float ey, float ew, float eh)
{
	float px1, px2, py1, py2;
	float ex1, ex2, ey1, ey2;

	px1 = px - pw / 2.0f;
	px2 = px + pw / 2.0f;
	py1 = py - ph / 2.0f;
	py2 = py + ph / 2.0f;
	ex1 = ex - ew / 2.0f;
	ex2 = ex + ew / 2.0f;
	ey2 = ey + eh / 2.0f;
	ey1 = ey2 - eh / 10.0f;

	return (px1 <= ex2 && ex1 <= px2 && py1 <= ey2 && ey1 <= py2);
}
//スクロール処理



