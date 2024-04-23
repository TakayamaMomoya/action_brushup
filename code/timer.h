//*****************************************************
//
// �^�C�}�[�̏���[timer.h]
// Author:���R����
//
//*****************************************************

#ifndef _TIMER_H_
#define _TIMER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
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

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CTimer *Create(void);
	void AddTimer(int nValue);
	void SetPosition(D3DXVECTOR3 pos) {};
	D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(); }
	D3DXVECTOR3 GetPositionOld(void) { return D3DXVECTOR3(); };	// �ʒu�擾����
	float GetWidth(void) { return 0.0f; }	// �T�C�Y�擾
	float GetHeight(void) { return 0.0f; }	// �T�C�Y�擾
	int GetSecond(void) { return m_nSecond; }	// ���Ԏ擾
	void EnableStop(bool bStop) { m_bStop = bStop; }
	static CTimer *GetInstance(void) { return m_pTimer; }

private:
	CNumber *m_pObjMinute;	// ���\���̃|�C���^
	CNumber *m_pObjSecond;	// �b�\���̃|�C���^
	int m_nSecond;	// ���݂̎���(�b)
	int m_nCntSecond;	// ��b�v���p�J�E���^�[
	int m_nIdxTexture;	// �e�N�X�`���ԍ�
	static CTimer *m_pTimer;	// ���g�̃|�C���^
	bool m_bStop;	// �~�߂邩�ǂ���
};

#endif
