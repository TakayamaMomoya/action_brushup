//*****************************************************
//
// �~�T�C���̏���[missile.cpp]
// Author:���R����
//
//*****************************************************
#ifndef _MISSILE_H_	// ��d�C���N���[�h�h�~
#define _MISSILE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "objectX.h"

//*****************************************************
// �O���錾
//*****************************************************
class CCollisionSphere;
class COrbit;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CMissile : public CObjectX
{// �v���C���[�Ɍ������G
public:
	CMissile();	// �R���X�g���N�^
	~CMissile();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	void Hit(float fDamage) { Death(); }	// �q�b�g����

	// �ÓI�����o�֐�
	static CMissile *Create(D3DXVECTOR3 pos);

private:
	// �����o�֐�
	void ChasePlayer(void);	// �ǐՏ���
	void Tilt(void);	// �X������
	void Death(void);	// ���S����

	// �����o�ϐ�
	float m_fDeathTimer;	// ���S�J�E���^�[
	CCollisionSphere *m_pCollisionSphere;	// ���̓����蔻��
	COrbit *m_pOrbit;	// �O�Ղ̃|�C���^
};

#endif
