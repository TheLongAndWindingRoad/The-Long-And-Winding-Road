#ifndef OBJECTBASE_H
#define	OBJECTBASE_H

/*オブジェクトの基底の基底クラス*/

class ObjectBase
{
public:
	/* コンストラクタ */
	ObjectBase() {};

	/* デストラクタ */
	virtual ~ObjectBase() {};

	/* 初期化関数 */
	virtual bool Initalize() = 0;

	/* 終了関数 */
	virtual void Finalize() = 0;

	/* オブジェクトの動き(更新(制御)) */
	virtual void Update() = 0;

	/* オブジェクトの描画 */
	virtual void Draw() = 0;

private:

};

#endif