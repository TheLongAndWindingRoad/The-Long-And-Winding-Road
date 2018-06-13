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
	//オプション画面の頂点情報を作成する
	CUSTOMVERTEX  drawresult[4]
	{
	{ 320.f , 200.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 1120.f, 200.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 1120.f, 400.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 320.f, 400.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};



	// 頂点情報の指定
	g_pDirect3DDevice->SetFVF(D3DFVF_CUSTOMVERTEX);

	// 画面の消去
	g_pDirect3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0x00, 0x00, 0x00), 1.0, 0);
	// 描画を開始
	g_pDirect3DDevice->BeginScene();

	GameMainControl();


	// テクスチャをステージに割り当てる
	g_pDirect3DDevice->SetTexture(0, g_pGameTexture[RESULT_TEX]);
	// 描画
	g_pDirect3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, drawresult, sizeof(CUSTOMVERTEX));

	// 描画を終了
	g_pDirect3DDevice->EndScene();
	// 画面に表示
	g_pDirect3DDevice->Present(NULL, NULL, NULL, NULL);


	*/


	return Scene;

}