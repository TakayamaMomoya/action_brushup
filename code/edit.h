//*****************************************************
//
// �G�f�B�^�[�̏���[edit.h]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
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
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	// �ÓI�����o�֐�
	static CEdit *Create(void);
	static CEdit *GetInstatnce(void) { return s_pEdit; }

private:
	// �����o�ϐ�
	CObjectX *m_pObjectCursor;	// �J�[�\���̃I�u�W�F�N�gX�ւ̃|�C���^
	int m_nIdxObject;
	CBlock::TYPE m_type;

	// �ÓI�����o�ϐ�
	static CEdit *s_pEdit;	// ���g�̃|�C���^
};