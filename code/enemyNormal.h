//*****************************************************
//
// �ʏ�G�̏���[enemyNormal.h]
// Author:���R����
//
//*****************************************************
#ifndef _ENEMYNORMAL_H_	// ��d�C���N���[�h�h�~
#define _ENEMYNORMAL_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "enemy.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CEnemyNormal : public CEnemy
{
public:
	CEnemyNormal();	// �R���X�g���N�^
	~CEnemyNormal();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��
	void Death(void);	// ���S����

	// �ϐ��擾�E�ݒ�֐�
	float GetLife(void) { return m_fLife; }	// �̗�
	void SetLife(float fLife) { m_fLife = fLife; }
	int GetScore(void) { return m_nScore; }	// �|�����Ƃ��ɓ�����X�R�A
	void SetScore(int nScore) { m_nScore = nScore; }
	float GetAttackCounter(void) { return m_fCntAttack; }	// �U���J�E���^�[
	void SetAttackCounter(float fCounter) { m_fCntAttack = fCounter; }
	void SetSpherePosition(D3DXVECTOR3 pos);	// ������̈ʒu
	CCollisionSphere *GetClsnSphere(void) { return m_pCollisionSphere; }	// ������̎擾
	CEnemyNormal *GetNext(void) { return m_pNext; }	// ���X�g�̎��̃|�C���^

	// �ÓI�����o�֐�
	static int GetNumAll(void) { return s_nNumAll; }	// �����擾

private:
	// �����o�֐�
	void ManageState(void);	// ��Ԃ̊Ǘ�
	void ManageCollision(void);	// �����蔻��̊Ǘ�

	// �����o�ϐ�
	float m_fLife;	// �̗�
	int m_nTimerState;	// ��ԑJ�ڃJ�E���^�[
	CCollisionSphere *m_pCollisionSphere;	// ���̓����蔻��
	CCollisionCube *m_pCollisionCube;	// �����̂̓����蔻��
	int m_nScore;	// �X�R�A�l
	float m_fCntAttack;	// �U���J�E���^
	CEnemyNormal *m_pPrev;	// �O�̃A�h���X
	CEnemyNormal *m_pNext;	// ���̃A�h���X

	// �ÓI�����o�ϐ�
	static int s_nNumAll;	// ����
};

#endif
