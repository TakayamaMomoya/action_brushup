//*****************************************************
//
// ���[�V�����̏���[motion.h]
// Author:���R����
//
//*****************************************************

#ifndef _MOTION_H_
#define _MOTION_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "parts.h"
#include "object.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define MAX_PARTS	(20)	// �p�[�c�̍ő吔
#define MAX_MOTION	(20)	// ���[�V�����̍ő吔

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CMotion : public CObject
{
public:
	// �\���̒�`
	struct S_Key
	{//�L�[�̍\����
		float fPosX;				//�ʒuX
		float fPosY;				//�ʒuY
		float fPosZ;				//�ʒuZ
		float fRotX;				//����X
		float fRotY;				//����Y
		float fRotZ;				//����Z
	};

	struct S_InfoKey
	{//�L�[���\����
		int nFrame;					//�Đ��t���[��
		S_Key aKey[MAX_PARTS];			//�e���f���̃L�[�v�f
	};

	struct S_InfoParticle
	{// �p�[�e�B�N�����\����
		int nKey;	//��������L�[
		int nFrame;	//��������t���[��
		int nType;	// ���
		D3DXVECTOR3 offset;	// �I�t�Z�b�g�ʒu
		int nIdxParent;	// �e�ƂȂ�p�[�c�̔ԍ�
	};
	
	struct S_InfoCollision
	{// �����蔻����\����
		int nKey;	//��������L�[
		int nFrame;	//��������t���[��
		D3DXVECTOR3 offset;	// �I�t�Z�b�g�ʒu
		int nIdxParent;	// �e�ƂȂ�p�[�c�̔ԍ�
	};

	struct S_InfoMotion
	{//���[�V�������̍\����
		bool bLoop;						//���[�v���邩�ǂ���
		int nNumKey;					//�L�[�̑���
		S_InfoKey aKeyInfo[MAX_PARTS];	//�L�[���
		int nNumParticle;	// �p�[�e�B�N���̐�
		int nNumCollision;	// �����蔻��̐�
		S_InfoParticle *pParticle;	// �p�[�e�B�N���̃|�C���^
		S_InfoCollision *pCollision;	// �����蔻��̃|�C���^
	};

	struct S_Part
	{// �p�[�c�̍\����
		int nIdx;
		int nIdxParent;
		CParts *m_pParts;
	};

	CMotion(int nPriority = 5);	// �R���X�g���N�^
	~CMotion();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	void Load(char *pPath);	// �Ǎ�
	void MultiplyMtx(void);	// �}�g���b�N�X���������킹�鏈��
	void SetMatrix(void);	// �}�g���b�N�X�ݒ�
	void CreateAfterImage(D3DXCOLOR col = { 0.0f,0.0f,0.0f,0.0f }, int m_nLife = 10);	// �c���̐���
	void InitPose(int nMotion);	// �|�[�Y�̏�����

	// �ϐ��擾�E�ݒ�֐�
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	// �ʒu
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 *GetPosAddress(void) { return &m_pos; }	// �ʒu�̃A�h���X
	void SetPosShadow(D3DXVECTOR3 pos) { m_posShadow = pos; }	// �e�̈ʒu
	void SetPositionOld(D3DXVECTOR3 pos) { m_posOld = pos; }	// �O��̈ʒu
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; }
	D3DXVECTOR3 GetPosPart(int nIdx);	// �p�[�c�̈ʒu
	void SetMove(D3DXVECTOR3 move) { m_move = move; }	// �ړ���
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }	// ����
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	void SetMotion(int nMotionType);	// ���[�V�����̎��
	int GetMotion(void) { return m_motionType; }
	void SetKeyOld(void);	// �O��̃L�[
	S_Part *GetParts(int nIdx) { return m_apParts[nIdx]; }	// �p�[�c���
	D3DXMATRIX *GetMatrix(void) { return &m_mtxWorld; }	// �}�g���b�N�X
	bool IsFinish(void) { return m_bFinish; }	// ���[�V�����I���t���O
	float GetRadiusMax(void);	// �ő唼�a
	int GetKey(void) { return m_nKey; }	// ���݂̃L�[
	float GetFrame(void) { return m_fCounterMotion; }	// ���[�V�����J�E���^�[
	void SetAllCol(D3DXCOLOR col);	// �S�p�[�c�̐F
	void ResetAllCol(void);
	void EnableShadow(bool bShadow) { m_bShadow = bShadow; }	// ���f���e�L���t���O

	// �ÓI�����o�֐�
	static CMotion *Create(char *pPath);	// ��������

private:
	// �����o�ϐ�
	S_Part *m_apParts[MAX_PARTS];	// �p�[�c�̍\����
	S_InfoMotion m_aMotionInfo[MAX_MOTION];	//���[�V�������̍\����
	S_Key m_aKeyOld[MAX_PARTS];	// �O��̃L�[���̍\����
	int m_nNumMotion;	//���[�V�����̑���
	int m_motionType;	//���[�V�����̎��
	int m_motionTypeOld;	//�O��̃��[�V�����̎��
	bool m_bLoopMotion;	//���[�v���邩�ǂ���
	int m_nNumKey;	//�L�[�̑���
	int m_nKey;	//���݂̃L�[
	float m_fCounterMotion;	//���[�V�����J�E���^�[
	int m_nNumParts;	// �p�[�c�̐�
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_posOld;	// �O��̈ʒu
	D3DXVECTOR3 m_posShadow;	// �e�̈ʒu
	D3DXVECTOR3 m_move;	// �ړ���
	D3DXVECTOR3 m_rot;							//����
	D3DXMATRIX m_mtxWorld;	// �}�g���b�N�X
	bool m_bFinish;	// ���[�V�������I��������ǂ���
	bool m_bShadow;	// �e��`�悷�邩�ǂ���
};

#endif