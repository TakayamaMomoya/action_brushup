//*****************************************************
//
// UI�}�l�[�W���[[UIManager.h]
// Author:���R����
//
//*****************************************************
#ifndef _UIMANAGER_H_	// ��d�C���N���[�h�h�~
#define _UIMANAGER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �O���錾
//*****************************************************
class CLife;
class CScore;
class CTimer;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CUIManager : public CObject
{
public:
	CUIManager();	// �R���X�g���N�^
	~CUIManager();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	// �ϐ��擾�E�ݒ�֐�
	bool IsDisp(void) { return m_bDisp; }	// �\���t���O
	void EnableDisp(bool bDisp) { m_bDisp = bDisp; }

	// �ÓI�����o�֐�
	static CUIManager *Create(void);	// ��������
	static CUIManager *GetInstance(void) { return m_pUIManager; }	// �C���X�^���X�̎擾

private:
	// �����o�ϐ�
	bool m_bDisp;	// UI��\�����邩�ǂ���
	CLife *m_pLife;	// ���C�t
	CScore *m_pScore;	// �X�R�A
	CTimer *m_pTimer;	// �^�C�}�[

	// �ÓI�����o�ϐ�
	static CUIManager *m_pUIManager;	// ���g�̃|�C���^
};

#endif
