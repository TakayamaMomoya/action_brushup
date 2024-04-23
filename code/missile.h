//*****************************************************
//
// �~�T�C���̏���[enemymissile.cpp]
// Author:���R����
//
//*****************************************************

#ifndef _MISSILE_H_
#define _MISSILE_H_

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

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMissile *Create(D3DXVECTOR3 pos);
	void Hit(float fDamage) { Death(); }

private:
	void ChasePlayer(void);	// �ǐՏ���
	void Tilt(void);	// �X������
	void Death(void);	// ���S����

	int m_nDeathTimer;	// ���S�J�E���^�[
	CCollisionSphere *m_pCollisionSphere;	// ���̓����蔻��
	COrbit *m_pOrbit;	// �O�Ղ̃|�C���^
};

#endif
