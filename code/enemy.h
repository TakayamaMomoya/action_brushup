//*****************************************************
//
// �G�̏���[enemy.cpp]
// Author:���R����
//
//*****************************************************
#ifndef _ENEMY_H_	// ��d�C���N���[�h�h�~
#define _ENEMY_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "motion.h"

//*****************************************************
// �O���錾
//*****************************************************
class CCollisionSphere;
class CCollisionCube;
class CShadow;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CEnemy : public CMotion
{
public:
	// �񋓌^��`
	enum E_TYPE
	{// �G�̎��
		TYPE_NONE = 0,	// ���ł��Ȃ�
		TYPE_SHOT,	// �����Ă���G
		TYPE_DRONE,	// �h���[���G
		TYPE_BOSS,	// �{�X�G
		TYPE_TURRET,	// �^���b�g
		TYPE_MAX
	};

	enum E_STATE
	{// ���
		STATE_NONE = 0,	// ���ł��Ȃ����
		STATE_NORMAL,	// �ʏ���
		STATE_DAMAGE,	// �_���[�W���
		STATE_DEATH,	// ���S���
		STATE_MAX
	};

	CEnemy();	// �R���X�g���N�^
	~CEnemy();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��
	void DeleteCollision(void);	// �����蔻��̍폜
	void RotDest(void);	// �ڕW�Ƀ��f���������鏈��
	virtual void Death(void);	// ���S���̏���
	void Hit(float fDamage);	// �q�b�g����

	// �ϐ��擾�E�ݒ�֐�
	void SetLife(float fLife);	// �̗�
	float GetLife(void) { return m_fLife; }
	void SetSpherePosition(D3DXVECTOR3 pos);	// �����蔻��̈ʒu
	CCollisionSphere *GetClsnSphere(void) { return m_pCollisionSphere; }	// �����蔻��
	E_STATE GetState(void) { return m_state; }	// ���
	void SetState(E_STATE state) { m_state = state; }
	int GetScore(void) { return m_nScore; }	// �X�R�A
	void SetScore(int nScore) { m_nScore = nScore; }
	float GetCntState(void) { return m_fTimerState; }	// ��ԃJ�E���^�[
	void SetCntState(float fCnt) { m_fTimerState = fCnt; }
	CEnemy *GetNext(void) { return m_pNext; }	// ���X�g�̎��̃|�C���^

	// �ÓI�����o�֐�
	static CEnemy *Create(D3DXVECTOR3 pos, E_TYPE type);	// ��������
	static int GetNumAll(void) { return s_nNumAll; }	// �����擾

protected:
	// �����o�֐�
	CShadow *GetShadow(void) { return m_pShadow; }	// �e�擾
	void ManageScore(void);	// �X�R�A�Ǘ�

private:
	// �����o�֐�
	void ManageState(void);

	// �����o�ϐ�
	float m_fLife;	// �̗�
	float m_fTimerState;	// ��ԑJ�ڃJ�E���^�[
	CCollisionSphere *m_pCollisionSphere;	// ���̓����蔻��
	CCollisionCube *m_pCollisionCube;	// �����̂̓����蔻��
	CShadow *m_pShadow;	// �e�̃|�C���^
	E_STATE m_state;	// ���
	int m_nScore;	// �X�R�A�l
	CEnemy *m_pPrev;	// �O�̃A�h���X
	CEnemy *m_pNext;	// ���̃A�h���X

	// �ÓI�����o�ϐ�
	static int s_nNumAll;	// ����
};

#endif
