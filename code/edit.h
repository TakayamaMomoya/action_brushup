//*****************************************************
//
// �G�f�B�^�[�̏���[edit.h]
// Author:���R����
//
//*****************************************************
#ifndef _EDIT_H_	// ��d�C���N���[�h�h�~
#define _EDIT_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "block.h"

//*****************************************************
// �O���錾
//*****************************************************
class CObjectX;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CEdit : public CObject
{
public:
	CEdit();	// �R���X�g���N�^
	~CEdit();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V

	// �ÓI�����o�֐�
	static CEdit *Create(void);	// ��������
	static CEdit *GetInstatnce(void) { return s_pEdit; }	// �C���X�^���X�̎擾

private:
	// �����o�ϐ�
	CObjectX *m_pObjectCursor;	// �J�[�\���̃��f���ւ̃|�C���^
	int m_nIdxModel;	// ���f���̔ԍ�
	CBlock::E_TYPE m_type;	// �ݒu����u���b�N�̎��

	// �ÓI�����o�ϐ�
	static CEdit *s_pEdit;	// ���g�̃|�C���^
};

#endif