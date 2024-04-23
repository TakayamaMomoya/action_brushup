//*****************************************************
//
// �ʏ�G�̏���[enemyNormal.h]
// Author:���R����
//
//*****************************************************

#ifndef _ENEMYNORMAL_H_
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

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void Load(void);	// �Ǎ�
	static int GetNumAll(void) { return m_nNumAll; }
	float GetLife(void) { return m_fLife; }
	void SetSpherePosition(D3DXVECTOR3 pos);
	void Death(void);
	CCollisionSphere *GetClsnSphere(void) { return m_pCollisionSphere; }
	CEnemyNormal *GetNext(void) { return m_pNext; }
	int GetScore(void) { return m_nScore; }
	void SetScore(int nScore) { m_nScore = nScore; }
	int GetAttackCounter(void) { return m_nCntAttack; }
	void SetAttackCounter(int nCounter) { m_nCntAttack = nCounter; }

private:
	void ManageState(void);
	void ManageCollision(void);

	static int m_nNumAll;	// ����
	float m_fLife;	// �̗�
	int m_nTimerState;	// ��ԑJ�ڃJ�E���^�[
	CCollisionSphere *m_pCollisionSphere;	// ���̓����蔻��
	CCollisionCube *m_pCollisionCube;	// �����̂̓����蔻��
	int m_nScore;	// �X�R�A�l
	unsigned int m_nCntAttack;	// �U���J�E���^

	CEnemyNormal *m_pPrev;	// �O�̃A�h���X
	CEnemyNormal *m_pNext;	// ���̃A�h���X
};

#endif
