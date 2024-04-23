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
#include <stdio.h>

//*****************************************************
// �O���錾
//*****************************************************
class CCollisionCube;
class CCollisionSphere;
class CShadow;

//*****************************************************
// �}�N����`
//*****************************************************
#define INITIAL_LIFE_PLAYER	(100)	// �����̗�

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CPlayer : public CObject
{
public:
	CPlayer(int nPriority = 4);	// �R���X�g���N�^
	~CPlayer();	// �f�X�g���N�^

	static CPlayer *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(float fDamage);
	void SetPosition(D3DXVECTOR3 pos) { m_info.pos = pos; }
	D3DXVECTOR3 GetPosition(void) { return m_info.pos; }
	void SetMove(D3DXVECTOR3 move) { m_info.move = move; }
	D3DXVECTOR3 GetMove(void) { return m_info.move; }
	void SetPositionOld(D3DXVECTOR3 pos) { m_info.posOld = pos; }
	D3DXVECTOR3 GetPositionOld(void) { return m_info.posOld; }
	void SetRot(D3DXVECTOR3 rot) { m_info.rot = rot; }
	D3DXVECTOR3 GetRot(void) { return m_info.rot; }
	static CPlayer *GetInstance(void) { return m_pPlayer; }
	int GetLife(void) { return m_info.nLife; }
	int GetinitialLife(void) { return m_info.nInitialLife; }
	CMotion *GetBody(void) { return m_info.pBody; }

private:
	enum STATE
	{
		STATE_NONE = 0,	// ���ł��Ȃ����
		STATE_NORMAL,	// �ʏ���
		STATE_DAMAGE,	// �_���[�W���
		STATE_MAX
	};
	enum MOTION
	{
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
	struct AttackInfo
	{// �U���̏��
		int nIdxMotion;	// ���[�V�����ԍ�
		int nIdxParent;	// �e�p�[�c�ԍ�
		D3DXVECTOR3 pos;	// �I�t�Z�b�g�ʒu
		int nKey;	// �L�[�ԍ�
		int nFrame;	// ��������t���[��
		float fRadius;	// ���a
	};
	enum JUMPSTATE
	{// �W�����v���
		JUMPSTATE_NONE = 0,
		JUMPSTATE_NORMAL,
		JUMPSTATE_ATTACK,
		JUMPSTATE_MAX
	};
	struct SInfo
	{
		int nLife;	// �̗�
		int nInitialLife;	// �����̗�
		int nCntAfterImage;	// �c�����o���J�E���^�[
		int nCntState;	// ��ԑJ�ڃJ�E���^�[
		int nTimeParry;	// �p���B�p������
		int nCntParry;	// �p���B�̃J�E���^�[
		int nTimeDash;	// �_�b�V���̃N�[���^�C��
		int nCntDash;	// �_�b�V���̃J�E���^�[
		int nTimeDamage;	// �_���[�W��Ԃ̎���
		float fSpeedDash;	// �_�b�V���̑��x
		float fPowJump;	// �W�����v��
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
		CShadow *pShadow;	// �e�̃|�C���^
		CCollisionCube *pCollisionCube;	// �����̂̓����蔻��
		CCollisionSphere *pClsnAttack;	// �U���̓����蔻��
		CCollisionSphere *pClsnHit;	// ��e�����蔻��
		int nNumAttack;	// �U������̐�
		AttackInfo *pAttackInfo;	// �U���̏��|�C���^
		STATE state;	// ���
		JUMPSTATE jump;	// �W�����v���
	};

	void Load(void);
	void LoadParam(FILE *pFile,char *pTemp);
	void ManageState(void);
	void Input(void);
	void InputMove(void);
	void InputAttack(void);
	void Parry(void);
	void InputCamera(void);
	void ManageMotion(void);
	void ManageCollision(void);
	void RotDest(void);
	void ManageAttack(void);
	void Death(void);
	void SetMotion(MOTION motion);

	SInfo m_info;	// ���g�̏��

	static CPlayer *m_pPlayer;	// ���g�̃|�C���^
};

#endif