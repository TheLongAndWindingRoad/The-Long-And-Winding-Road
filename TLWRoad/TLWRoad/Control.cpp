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
	//���t���[���C���N�������g
	infoAnime[no].frameN++;
	//�����t���[��NO���؂�ւ��^�C�~���O�̐����ȏ�ɂȂ�����
	if (infoAnime[no].frameN >= infoAnime[no].frameEx) {

		//���̊G�ɐ؂�ւ�
		infoAnime[no].animeNo += infoAnime[no].addNo;
		//�g�b�v�A�j���ԍ����A�j�������̐����𒴂����������0�����������
		if (infoAnime[no].animeNo >= infoAnime[no].animeNum ||
			infoAnime[no].animeNo < 0) {
			infoAnime[no].round = true;
			//���[�v�p�^�[���ɂ���ĕ���
			if (infoAnime[no].repeatpat == LOOP) {
				infoAnime[no].animeNo = 0;
			}
			else if (infoAnime[no].repeatpat == REVERSE) {
				infoAnime[no].addNo *= -1;
				infoAnime[no].animeNo = infoAnime[no].animeNo + infoAnime[no].addNo * 2;
			}
		}
		//�t���[�����O�ɖ߂�
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

//�A�j��No�ɑ΂���f�ޏ��𓾂�
ImageInfo GetImageInfo(ANIMEPAT ap)
{
	int imgId;
	ImageInfo imgInfo;

	imgId = imgNo[GetAnimeNo(ap)];	//�A�j��No�ɑ΂���f�ޔԍ��𓾂�
	imgInfo = ImgInfo[imgId];

	return imgInfo;
}

//�����蔻��
//�@x,y���W�@�����_
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

//�@x,y���W�@�����_ ���̏㑤�@���̉���
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
//�X�N���[������



