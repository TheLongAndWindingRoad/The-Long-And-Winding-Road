#ifndef SCENEBASE_H
#define	SCENEBASE_H

class SceneBase
{
public:
	/* �V�[���̏�ԗ� */
	enum STATE
	{
		/* ��������� */
		INIT_STATE,
		/* �X�V��� */
		UPDATE_STATE,
		/* �I����� */
		FAINAL_STATE
	};

	/* 
	*	�R���X�g���N�^
	*	�����Ōp����͉��̃V�[�������킩��悤��
	*/
	SceneBase(int _sceneID);

	/* �f�X�g���N�^ */
	virtual ~SceneBase();

	/*	�������֐�
	*	����������true ���s������false
	*/
	virtual bool Initialize();

	/* �I���֐� */
	virtual void Finalize();

	/* �V�[���̍X�V */
	virtual void Update();

	/* ���݂̏�ԏ���Ԃ� */
	inline STATE GetState() const
	{
		return m_State;
	}

	/* ���݂̃V�[����ID(���)��Ԃ� */
	inline int GetSceneID() const
	{
		return m_SceneID;
	}

	/* �J�ڐ�(��)�̃V�[��ID��Ԃ� */
	inline int GetNextSceneID() const
	{
		return m_NextSceneID;
	}

protected:
	/* �V�[���̏��(���) */
	STATE m_State;
	/* �V�[����ID */
	int m_SceneID;
	/* ���̃V�[��ID */
	int m_NextSceneID;
};

#endif