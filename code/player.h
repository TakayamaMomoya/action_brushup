//*****************************************************
//
// �v���C���[�̏���[player.cpp]
// Author:���R����
//
//*****************************************************

#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"
#include "motion.h"

//*****************************************************
// �O���錾
//*****************************************************
class CCollisionCube;
class CCollisionSphere;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CPlayer : public CObject
{
public:
	// �񋓌^��`
	enum E_MOTION
	{// ���[�V�����̎��
		MOTION_NEUTRAL = 0,	// �ҋ@���
		MOTION_MOVE,	// �ړ����[�V����
		MOTION_JUMP,	// �W�����v���[�V����
		MOTION_FALL,	// �������[�V����
		MOTION_ATTACK,	// �U�����[�V����
		MOTION_ATTACKTURN,	// ���]�U�����[�V����
		MOTION_AIRATTACK,	// �󒆍U�����[�V����
		MOTION_PARRY,	// �p���B���[�V����
		MOTION_DASH,	// �_�b�V�����[�V����
		MOTION_TITLE_NEUTRAL,	// �^�C�g���ҋ@
		MOTION_TITLE_STANDUP,	// �^�C�g�������オ��
		MOTION_APPER,	// �o�����[�V����
		MOTION_MAX
	};
	
	// �\���̒�`
	struct S_Param
	{// �p�����[�^�[
		int nInitialLife;	// �����̗�
		float fSpeedMove;	// �ړ����x
		float fGravity;	// �d��
		float fFactMove;	// �ړ������W��
		float fFactRoll;	// ��]�W��
		float fSpeedDash;	// �_�b�V���̑��x
		float fPowJump;	// �W�����v��
		float fPowAttackJump;	// ��i�W�����v��
		int nTimeDamage;	// �_���[�W��Ԃ̎���
		int nTimeDash;	// �_�b�V���̃N�[���^�C��
	};

	CPlayer(int nPriority = 4);	// �R���X�g���N�^
	~CPlayer();	// �f�X�g���N�^
	
	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	void Hit(float fDamage);	// �q�b�g����

	// �ϐ��擾�E�ݒ�֐�
	void SetPosition(D3DXVECTOR3 pos) { m_info.pos = pos; }	// �ʒu
	D3DXVECTOR3 GetPosition(void) { return m_info.pos; }
	void SetMove(D3DXVECTOR3 move) { m_info.move = move; }	// �ړ���
	D3DXVECTOR3 GetMove(void) { return m_info.move; }
	void SetPositionOld(D3DXVECTOR3 pos) { m_info.posOld = pos; }	// �O��̈ʒu
	D3DXVECTOR3 GetPositionOld(void) { return m_info.posOld; }
	void SetRot(D3DXVECTOR3 rot) { m_info.rot = rot; }	// ����
	D3DXVECTOR3 GetRot(void) { return m_info.rot; }
	int GetLife(void) { return m_info.nLife; }	// ���C�t
	S_Param GetParam(void) { return m_param; }	// �p�����[�^�[
	CMotion *GetBody(void) { return m_info.pBody; }	// ������

	// �ÓI�����o�֐�
	static CPlayer *Create(void);	// ��������
	static CPlayer *GetInstance(void) { return s_pPlayer; }	// �C���X�^���X�̎擾

private:
	// �񋓌^��`
	enum E_STATE
	{// ���
		STATE_NONE = 0,	// ���ł��Ȃ����
		STATE_NORMAL,	// �ʏ���
		STATE_DAMAGE,	// �_���[�W���
		STATE_MAX
	};
	enum E_JUMPSTATE
	{// �W�����v���
		JUMPSTATE_NONE = 0,
		JUMPSTATE_NORMAL,
		JUMPSTATE_ATTACK,
		JUMPSTATE_MAX
	};

	// �\���̒�`
	struct S_AttackInfo
	{// �U���̏��
		int nIdxMotion;	// ���[�V�����ԍ�
		int nIdxParent;	// �e�p�[�c�ԍ�
		D3DXVECTOR3 pos;	// �I�t�Z�b�g�ʒu
		int nKey;	// �L�[�ԍ�
		int nFrame;	// ��������t���[��
		float fRadius;	// ���a
		float fScaleHitStop;	// �q�b�g�X�g�b�v�̃^�C���X�P�[��
		float fTimeHitStop;	// �q�b�g�X�g�b�v�̎�������
	};
	struct S_Info
	{// �X�e�[�^�X���
		int nLife;	// �̗�
		int nCntAfterImage;	// �c�����o���J�E���^�[
		int nCntState;	// ��ԑJ�ڃJ�E���^�[
		int nTimeParry;	// �p���B�p������
		int nCntParry;	// �p���B�̃J�E���^�[
		int nCntDash;	// �_�b�V���̃J�E���^�[
		bool bSprint;	// �_�b�V����Ԃ��ǂ���
		bool bAttack;	// �U���t���O
		float fRadiusParry;	// �p���B����̔��a
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 posOld;	// �O��̈ʒu
		D3DXVECTOR3 offsetParry;	// �p���B����̃I�t�Z�b�g
		D3DXVECTOR3 move;	// �ړ���
		D3DXVECTOR3 rot;	// ����
		D3DXVECTOR3 rotDest;	// �ڕW�̌���
		CMotion *pBody;	// �̂̃|�C���^
		CCollisionCube *pCollisionCube;	// �����̂̓����蔻��
		CCollisionSphere *pClsnAttack;	// �U���̓����蔻��
		CCollisionSphere *pClsnHit;	// ��e�����蔻��
		int nNumAttack;	// �U������̐�
		S_AttackInfo *pAttackInfo;	// �U���̏��|�C���^
		E_STATE state;	// ���
		E_JUMPSTATE jump;	// �W�����v���
	};

	// �����o�֐�
	void Load(void);	// �Ǎ�
	void LoadParam(FILE *pFile,char *pTemp);	// �p�����[�^�Ǎ�
	void ManageState(void);	// ��ԊǗ�
	void Input(void);	// ����
	void InputMove(void);	// �ړ��̓���
	void InputAttack(void);	// �U���̓���
	void Parry(void);	// �p���B�̑���
	void ManageMotion(void);	// ���[�V�����̊Ǘ�
	void ManageCollision(void);	// �����蔻��̊Ǘ�
	void RotDest(void);	// �ڕW����������
	void ManageAttack(void);	// �U���̊Ǘ�
	void SetAttackCollision(S_AttackInfo attackInfo);	// �U������̐ݒ�
	void Death(void);	// ���S����
	void SetMotion(E_MOTION motion);	// ���[�V�����̐ݒ�

	// �����o�ϐ�
	S_Info m_info;	// ���g�̏��
	S_Param m_param;	// �p�����[�^�[

	// �ÓI�����o�ϐ�
	static CPlayer *s_pPlayer;	// ���g�̃|�C���^
};

#endif