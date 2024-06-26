//*****************************************************
//
// �X�J�C�{�b�N�X�̏���[skybox.h]
// Author:���R����
//
//*****************************************************
#ifndef _SKYBOX_H_	// ��d�C���N���[�h�h�~
#define _SKYBOX_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "objectX.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CSkybox : public CObjectX
{
public:
	CSkybox(int nPriority = 3);	// �R���X�g���N�^
	~CSkybox();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��

	// �ÓI�����o�֐�
	static CSkybox *Create();	// ��������

private:
};

#endif

