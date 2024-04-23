//*****************************************************
//
// ���C�t�Ǘ��̏���[life.h]
// Author:���R����
//
//*****************************************************

#ifndef _LIFE_H_
#define _LIFE_H_

#include "Object.h"

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

	static CLife *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void) {};

private:
	enum PULSESTATE
	{
		PULSESTATE_IN = 0,	// �t�F�[�h�C�����
		PULSESTATE_OUT,	// �t�F�[�h�A�E�g���
		PULSESTATE_MAX,
	};

	void UpdatePulse(void);
	void FadePulse(void);

	CUI *m_pFrame;	// �t���[���̃|�C���^
	CUI *m_pPulse;	// �g�`�̃|�C���^
	PULSESTATE m_pulseState;	// �g�`�̏��
	int m_nCntPulse;	// �g�`�̃J�E���^�[
};

#endif
