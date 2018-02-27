#ifndef SCENEMANAGER_H
#define	SCENEMANAGER_H

#include<vector>

class SceneBase;

class SceneManager
{
public:
	/* �R���X�g���N�^ */
	SceneManager();

	/* �f�X�g���N�^ */
	~SceneManager();

	/* �������֐� */
	bool Initalize();

	/* �I���֐� */
	void Finalize();

	/* �V�[���̍X�V�֐� */
	bool Update();

	/* �V�[���̒ǉ� */
	bool AddScene(SceneBase* _pScene);

	/* ���݂̃V�[���ɐݒ� */
	void SetEntryScene(SceneBase* _pScene);

	/* �V�[���̍폜 */
	void DeleteScene(SceneBase* _pScene);

private:
	/* ��V�[����ID */
	static const int		m_EmptySceneID;

	/* �V�[�����i�[���Ă���R���e�i */
	std::vector<SceneBase*> m_pSceneDate;

	/* ���݂̃V�[�� */
	SceneBase*				m_pCurrentScene;
};


#endif