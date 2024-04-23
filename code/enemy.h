//*****************************************************
//
// �G�̏���[enemy.cpp]
// Author:���R����
//
//*****************************************************

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "motion.h"

//*****************************************************
// �O���錾
//*****************************************************
class CCollisionSphere;
class CCollisionCube;
class CShadow;

//*****************************************************
// �}�N����`
//*****************************************************
#define LOCKON_RANGE	(4000.0f)	// ���b�N�I������
#define AIM_LOCKON_RANGE	(LOCKON_RANGE * 2.0f)	// �G�C�����̃��b�N�I������

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CEnemy : public CMotion
{
public:
	typedef enum
	{// �G�̎��
		TYPE_NONE = 0,	// ���ł��Ȃ�
		TYPE_SHOT,	// �����Ă���G
		TYPE_DRONE,	// �h���[���G
		TYPE_BOSS,	// �{�X�G
		TYPE_TURRET,	// �^���b�g
		TYPE_MAX
	}TYPE;

	typedef enum
	{// ���
		STATE_NONE = 0,	// ���ł��Ȃ����
		STATE_NORMAL,	// �ʏ���
		STATE_DAMAGE,	// �_���[�W���
		STATE_DEATH,	// ���S���
		STATE_MAX
	}STATE;

	CEnemy();	// �R���X�g���N�^
	~CEnemy();	// �f�X�g���N�^

	static CEnemy *Create(D3DXVECTOR3 pos,TYPE type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static int GetNumAll(void) { return m_nNumAll; }
	void SetLife(float fLife);
	float GetLife(void) { return m_fLife; }
	void Hit(float fDamage);
	void Death(void);
	void SetSpherePosition(D3DXVECTOR3 pos);
	STATE GetState(void) { return m_state; }
	void SetState(STATE state) { m_state = state; }
	CCollisionSphere *GetClsnSphere(void) { return m_pCollisionSphere; }
	CEnemy *GetNext(void) { return m_pNext; }
	int GetScore(void) { return m_nScore; }
	void SetScore(int nScore) { m_nScore = nScore; }
	int GetCntState(void) { return m_nTimerState; }
	void SetCntState(int nCnt) { m_nTimerState = nCnt; }
	void DeleteCollision(void);

protected:
	void RotDest(void);
	CShadow *GetShadow(void) { return m_pShadow; }
	void ManageScore(void);

private:
	void ManageState(void);

	static int m_nNumAll;	// ����
	float m_fLife;	// �̗�
	int m_nTimerState;	// ��ԑJ�ڃJ�E���^�[
	CCollisionSphere *m_pCollisionSphere;	// ���̓����蔻��
	CCollisionCube *m_pCollisionCube;	// �����̂̓����蔻��
	CShadow *m_pShadow;	// �e�̃|�C���^
	STATE m_state;	// ���
	int m_nScore;	// �X�R�A�l

	CEnemy *m_pPrev;	// �O�̃A�h���X
	CEnemy *m_pNext;	// ���̃A�h���X
};

#endif
