//*****************************************************
//
// �{�X�G�̏���[enemyboss.h]
// Author:���R����
//
//*****************************************************

#ifndef _ENEMYBOSS_H_
#define _ENEMYBOSS_H_

#include "enemy.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CEnemyBoss : public CEnemy
{// �����Ă���G
public:
	// �񋓌^��`
	enum IDXPARTS
	{// �p�[�c�̔ԍ�
		IDX_WAIST = 0,	// ��
		IDX_BODY,	// ��
		IDX_HEAD,	// ��
		IDX_SHOULDER_L,	// ����
		IDX_ARM_L,	// ���r
		IDX_HAND_L,	// ����
		IDX_SHOULDER_R,	// �E��
		IDX_ARM_R,	// �E��
		IDX_HAND_R,	// �E��
		IDX_LEG_L,	// ����
		IDX_FOOT_L,	// ����
		IDX_TOE_L,	// ������
		IDX_LEG_R,	// �E��
		IDX_FOOT_R,	// �E��
		IDX_TOE_R,	// �E����
		IDX_WEAPON,	// ����
		IDX_MAX
	};

	CEnemyBoss();	// �R���X�g���N�^
	~CEnemyBoss();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��
	void Hit(float fDamage);	// �q�b�g����

	// �ÓI�����o�֐�
	static CEnemyBoss *Create(void);	// ��������
	static CEnemyBoss *GetInstance(void) { return m_pEnemyBoss; }	// �C���X�^���X�̎擾

private:
	// �񋓌^��`
	enum STATE
	{// ���
		STATE_NONE = 0,	// �������Ă��Ȃ����
		STATE_APPER,	// �o�����
		STATE_BATTLE,	// �퓬���
		STATE_MAX
	};
	enum ATTACKSTATE
	{// �U�����
		ATTACK_MISSILE = 0,	// �~�T�C���U��
		ATTACK_DASH,	// �ːi�U��
		ATTACK_SHOT_UNDER,	// ������ˌ��U��
		ATTACK_MAX
	};
	enum MOTION
	{// ���[�V����
		MOTION_APPER = 0,	// �o�����[�V����
		MOTION_MISSILE,	// �~�T�C�����[�V����
		MOTION_DASH,	// �ːi���[�V����
		MOTION_SHOT_UNDER,	// �ˌ����[�V����
		MOTION_SHOT_UPPER,	// ���]�ˌ����[�V����
		MOTION_DEATH,	// ���S���[�V����
		MOTION_MAX
	};

	// �\���̒�`
	struct Sinfo
	{// ���g�̏��
		STATE state;	// ���
		ATTACKSTATE attackState;	// �U�����
		D3DXVECTOR3 posDest;	// �ڕW�ʒu
		float fTimerAttack;	// �U���^�C�}�[
		int nNumAttack;	// �U��������
		float fTimerState;	// ��ԑJ�ڃ^�C�}�[
	};
	
	// �����o�֐�
	void ManageState(void);	// ��Ԃ̊Ǘ�
	void UpdateState(void);	// ��Ԃ��Ƃ̍X�V
	// ��Ԃ��Ƃ̍X�V======
	void UpdateApper(void);	// �o�����̍X�V
	void UpdateAttackState(void);
	//=====================
	// �U����Ԃ��Ƃ̍X�V==
	void UpdateMissile(void);
	void UpdateDash(void);
	void UpdateShotUnder(void);
	//=====================
	void ManageAttack(void);
	void ManageCollision(void);
	void FollowCollision(void);
	bool FollowDest(void);
	void SwitchState(void);

	// �����o�ϐ�
	Sinfo m_info;	// ���g�̏��

	// �ÓI�����o�ϐ�
	static CEnemyBoss *m_pEnemyBoss;	// ���g�̃|�C���^
};

#endif
