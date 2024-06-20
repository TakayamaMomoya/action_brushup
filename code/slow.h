//*****************************************************
//
// �X���[�̏���[slow.h]
// Author:���R����
//
//*****************************************************
#ifndef _SLOW_H_	// ��d�C���N���[�h�h�~
#define _SLOW_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CSlow : public CObject
{
public:
	CSlow();	// �R���X�g���N�^
	~CSlow();	// �f�X�g���N�^

	// �����o�ϐ�
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	// �ϐ��擾�E�ݒ�֐�
	float GetScale(void) { return m_fTimeScale; }	// �^�C���X�P�[��
	void SetScale(float fScale);
	void SetSlowTime(float fTime, float fScale);	// ��莞�ԃX���[�ɂ��鏈��

	// �ÓI�����o�ϐ�
	static CSlow *Create(void);
	static CSlow *GetInstance(void) { return s_pSlow; }

private:
	// �����o�ϐ�
	float m_fTimeScale;	// �^�C���X�P�[��
	float m_fTimeSlow;	// �X���[�ɂ��鎞��

	// �ÓI�����o�ϐ�
	static CSlow *s_pSlow;	// ���g�̃|�C���^
};

namespace Slow
{
//*****************************************************
// �V���[�g�J�b�g�֐�
//*****************************************************
float GetTimeScale(void);	// �^�C���X�P�[���̎擾
}

#endif