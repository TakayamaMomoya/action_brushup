//*****************************************************
//
// �{�X�̃X�e�C�g�̏���[enemybossState.h]
// Author:���R����
//
//*****************************************************

#ifndef _ENEMYBOSSSTATE_H_
#define _ENEMYBOSSSTATE_H_

//*****************************************************
// �O���錾
//*****************************************************
class CEnemyBoss;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CEnemyBossState
{
public:
	CEnemyBossState() {}	// �R���X�g���N�^
	~CEnemyBossState() {}	// �f�X�g���N�^

	// �����o�֐�
	virtual void Init(CEnemyBoss *pBoss) = 0;	// ����������
	virtual void Update(CEnemyBoss *pBoss) = 0;	// �X�V����

private:
};

class CEnemyBossStateApper : public CEnemyBossState
{// �o�����
public:
	CEnemyBossStateApper();	// �R���X�g���N�^
	~CEnemyBossStateApper();	// �f�X�g���N�^

	// �����o�֐�
	void Init(CEnemyBoss *pBoss) override;	// ����������
	void Update(CEnemyBoss *pBoss) override;	// �X�V����

private:
};

class CEnemyBossStateMissile : public CEnemyBossState
{// �~�T�C���U��
public:
	CEnemyBossStateMissile();	// �R���X�g���N�^
	~CEnemyBossStateMissile();	// �f�X�g���N�^

	// �����o�֐�
	void Init(CEnemyBoss *pBoss) override;	// ����������
	void Update(CEnemyBoss *pBoss) override;	// �X�V����

private:
	// �����o�ϐ�
	float m_fTimerAttack;	// �U���^�C�}�[
	int m_nCntAttack;	// �U���J�E���^�[
};

class CEnemyBossStateDash : public CEnemyBossState
{// �ːi�U��
public:
	CEnemyBossStateDash();	// �R���X�g���N�^
	~CEnemyBossStateDash();	// �f�X�g���N�^

	// �����o�֐�
	void Init(CEnemyBoss *pBoss) override;	// ����������
	void Update(CEnemyBoss *pBoss) override;	// �X�V����

private:
};

class CEnemyBossStateShot : public CEnemyBossState
{// �ˌ��U��
public:
	CEnemyBossStateShot();	// �R���X�g���N�^
	~CEnemyBossStateShot();	// �f�X�g���N�^

	// �����o�֐�
	void Init(CEnemyBoss *pBoss) override;	// ����������
	void Update(CEnemyBoss *pBoss) override;	// �X�V����

private:
	// �����o�ϐ�
	float m_fTimerAttack;	// �U���^�C�}�[
};

#endif
