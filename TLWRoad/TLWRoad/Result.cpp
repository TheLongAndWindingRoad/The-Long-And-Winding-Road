#include"SceneManager.h"




int ResultControl()
{

	/*
	if (CheckMouseL() == PUSH)
	{
	if (420 < pt.x && 1020 > pt.x && 450 < pt.y && 550 > pt.y)
	{
	Scene = TITLE;
	}

	}


	*/



	return Scene;

}





int Result()
{

	/*
	//�I�v�V������ʂ̒��_�����쐬����
	CUSTOMVERTEX  drawresult[4]
	{
	{ 320.f , 200.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 1120.f, 200.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 1120.f, 400.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 320.f, 400.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};



	// ���_���̎w��
	g_pDirect3DDevice->SetFVF(D3DFVF_CUSTOMVERTEX);

	// ��ʂ̏���
	g_pDirect3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0x00, 0x00, 0x00), 1.0, 0);
	// �`����J�n
	g_pDirect3DDevice->BeginScene();

	GameMainControl();


	// �e�N�X�`�����X�e�[�W�Ɋ��蓖�Ă�
	g_pDirect3DDevice->SetTexture(0, g_pGameTexture[RESULT_TEX]);
	// �`��
	g_pDirect3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, drawresult, sizeof(CUSTOMVERTEX));

	// �`����I��
	g_pDirect3DDevice->EndScene();
	// ��ʂɕ\��
	g_pDirect3DDevice->Present(NULL, NULL, NULL, NULL);


	*/


	return Scene;

}