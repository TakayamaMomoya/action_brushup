//*****************************************************
//
// �{�X�G�̏���[enemyboss.h]
// Author:���R����
//
//*****************************************************
#ifndef _ENEMYBOSS_H_	// ��d�C���N���[�h�h�~
#define _ENEMYBOSS_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "enemy.h"
#include "enemybossState.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CEnemyBoss : public CEnemy
{
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

	CEnemyBoss();	// �R���X�g���N�^
	~CEnemyBoss();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��
	void Hit(float fDamage);	// �q�b�g����
	bool FollowDest(void);	// �ڕW�Ɍ���������
	void SwitchState(void);	// ��Ԃ̕ύX
	void FollowCollision(void);	// �����蔻��̒Ǐ]
	void Death(void) override;	// ���S���̏���

	// �ϐ��擾�E�ݒ�֐�
	void SetPosDest(D3DXVECTOR3 posDest) { m_info.posDest = posDest; }	// �ڕW�ʒu
	D3DXVECTOR3 GetPosDest(void) { return m_info.posDest; }

	// �ÓI�����o�֐�
	static CEnemyBoss *Create(void);	// ��������
	static CEnemyBoss *GetInstance(void) { return s_pEnemyBoss; }	// �C���X�^���X�̎擾

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
		ATTACK_SHOT,	// �ˌ��U��
		ATTACK_MAX
	};

	// �\���̒�`
	struct S_Info
	{// ���g�̏��
		STATE state;	// ���
		ATTACKSTATE attackState;	// �U�����
		D3DXVECTOR3 posDest;	// �ڕW�ʒu
		float fTimerState;	// ��ԑJ�ڃ^�C�}�[
		// �R���X�g���N�^
		S_Info() : state(CEnemyBoss::STATE::STATE_NONE), attackState(ATTACKSTATE::ATTACK_MISSILE),
			posDest{}, fTimerState(0.0f) {}
	};
	
	// �����o�֐�
	void ManageState(void);	// ��Ԃ̊Ǘ�
	void ManageCollision(void);	// �����蔻��Ǘ�
	void ChangeState(CEnemyBossState *pState);	// �X�e�C�g�̐؂�ւ�

	// �����o�ϐ�
	S_Info m_info;	// ���g�̏��
	CEnemyBossState *m_pState;	// �X�e�C�g�̃|�C���^

	// �ÓI�����o�ϐ�
	static CEnemyBoss *s_pEnemyBoss;	// ���g�̃|�C���^
};

#endif
