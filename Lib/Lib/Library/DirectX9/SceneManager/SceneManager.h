#ifndef SCENEMANAGER_H
#define	SCENEMANAGER_H

#include<vector>

class SceneBase;

class SceneManager
{
public:
	/* コンストラクタ */
	SceneManager();

	/* デストラクタ */
	~SceneManager();

	/* 初期化関数 */
	bool Initalize();

	/* 終了関数 */
	void Finalize();

	/* シーンの更新関数 */
	bool Update();

	/* シーンの追加 */
	bool AddScene(SceneBase* _pScene);

	/* 現在のシーンに設定 */
	void SetEntryScene(SceneBase* _pScene);

	/* シーンの削除 */
	void DeleteScene(SceneBase* _pScene);

private:
	/* 空シーンのID */
	static const int		m_EmptySceneID;

	/* シーンを格納しているコンテナ */
	std::vector<SceneBase*> m_pSceneDate;

	/* 現在のシーン */
	SceneBase*				m_pCurrentScene;
};


#endif