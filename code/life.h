//*****************************************************
//
// ���C�t�Ǘ��̏���[life.h]
// Author:���R����
//
//*****************************************************
#ifndef _LIFE_H_	// ��d�C���N���[�h�h�~
#define _LIFE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �O���錾
//*****************************************************
class CUI;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CLife : public CObject
{
public:
	CLife(int nPriority = 6);	// �R���X�g���N�^
	~CLife();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void) {};	// �`��

	// �ÓI�����o�֐�
	static CLife *Create(void);	// ��������

private:
	enum E_PULSESTATE
	{// �g�`�̏��
		PULSESTATE_IN = 0,	// �t�F�[�h�C�����
		PULSESTATE_OUT,	// �t�F�[�h�A�E�g���
		PULSESTATE_MAX,
	};

	// �����o�֐�
	void UpdatePulse(void);	// �g�`�̍X�V
	void FadePulse(void);	// �g�`�̃t�F�[�h

	// �����o�ϐ�
	CUI *m_pFrame;	// �t���[���̃|�C���^
	CUI *m_pPulse;	// �g�`�̃|�C���^
	E_PULSESTATE m_pulseState;	// �g�`�̏��
	int m_nCntPulse;	// �g�`�̃J�E���^�[
};

#endif
