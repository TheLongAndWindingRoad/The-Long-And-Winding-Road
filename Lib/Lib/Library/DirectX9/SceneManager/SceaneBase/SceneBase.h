#ifndef SCENEBASE_H
#define	SCENEBASE_H

class SceneBase
{
public:
	/* シーンの状態列挙 */
	enum STATE
	{
		/* 初期化状態 */
		INIT_STATE,
		/* 更新状態 */
		UPDATE_STATE,
		/* 終了状態 */
		FAINAL_STATE
	};

	/* 
	*	コンストラクタ
	*	引数で継承先は何のシーンかをわかるように
	*/
	SceneBase(int _sceneID);

	/* デストラクタ */
	virtual ~SceneBase();

	/*	初期化関数
	*	成功したらtrue 失敗したらfalse
	*/
	virtual bool Initialize();

	/* 終了関数 */
	virtual void Finalize();

	/* シーンの更新 */
	virtual void Update();

	/* 現在の状態情報を返す */
	inline STATE GetState() const
	{
		return m_State;
	}

	/* 現在のシーンのID(種類)を返す */
	inline int GetSceneID() const
	{
		return m_SceneID;
	}

	/* 遷移先(次)のシーンIDを返す */
	inline int GetNextSceneID() const
	{
		return m_NextSceneID;
	}

protected:
	/* シーンの状態(種類) */
	STATE m_State;
	/* シーンのID */
	int m_SceneID;
	/* 次のシーンID */
	int m_NextSceneID;
};

#endif