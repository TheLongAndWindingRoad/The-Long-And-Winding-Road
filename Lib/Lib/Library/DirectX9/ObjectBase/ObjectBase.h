#ifndef OBJECTBASE_H
#define	OBJECTBASE_H

/*�I�u�W�F�N�g�̊��̊��N���X*/

class ObjectBase
{
public:
	/* �R���X�g���N�^ */
	ObjectBase() {};

	/* �f�X�g���N�^ */
	virtual ~ObjectBase() {};

	/* �������֐� */
	virtual bool Initalize() = 0;

	/* �I���֐� */
	virtual void Finalize() = 0;

	/* �I�u�W�F�N�g�̓���(�X�V(����)) */
	virtual void Update() = 0;

	/* �I�u�W�F�N�g�̕`�� */
	virtual void Draw() = 0;

private:

};

#endif