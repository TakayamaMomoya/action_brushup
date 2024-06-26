//*****************************************************
//
// �^�C�}�[�̏���[timer.h]
// Author:���R����
//
//*****************************************************
#ifndef _TIMER_H_	// ��d�C���N���[�h�h�~
#define _TIMER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �O���錾
//*****************************************************
class CNumber;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CTimer : public CObject
{
public:
	CTimer();	// �R���X�g���N�^
	~CTimer();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	void AddTimer(int nValue);	// �^�C�}�[�̉��Z

	// �ϐ��擾�E�ݒ�֐�
	int GetSecond(void) { return m_nSecond; }	// ���Ԏ擾
	void EnableStop(bool bStop) { m_bStop = bStop; }	// ��~���

	// �ÓI�����o�֐�
	static CTimer *Create(void);	// ��������
	static CTimer *GetInstance(void) { return m_pTimer; }	// �C���X�^���X�̎擾

private:
	// �����o�ϐ�
	CNumber *m_pObjMinute;	// ���\���̃|�C���^
	CNumber *m_pObjSecond;	// �b�\���̃|�C���^
	int m_nSecond;	// ���݂̎���(�b)
	int m_nCntSecond;	// ��b�v���p�J�E���^�[
	int m_nIdxTexture;	// �e�N�X�`���ԍ�
	bool m_bStop;	// �~�߂邩�ǂ���

	// �ÓI�����o�ϐ�
	static CTimer *m_pTimer;	// ���g�̃|�C���^
};

#endif
