//*****************************************************
//
// �����蔻�菈��[collision.h]
// Author:���R����
//
//*****************************************************
#ifndef _COLLISION_H_	// ��d�C���N���[�h�h�~
#define _COLLISION_H_

//*****************************************************
// �C���N���[�h
//****************************************************
#include "object.h"

//*****************************************************
// �O���錾
//****************************************************
class CObject2D;

//*****************************************************
// �N���X��`
//*****************************************************
class CCollision
{
public:
	// �񋓌^��`
	enum E_TAG
	{// ���ʃ^�O
		TAG_NONE = 0,	// ���ł��Ȃ�
		TAG_PLAYER,	// �v���C���[
		TAG_ENEMY,	// �G
		TAG_PLAYERBULLET,	// �v���C���[�̒e
		TAG_ENEMYBULLET,	// �G�̒e
		TAG_BLOCK,	// �u���b�N
		TAG_MAX
	};

	enum E_TYPE
	{// ���
		TYPE_NONE = 0, // ���ł��Ȃ�
		TYPE_SPHERE,	// ���̓����蔻��
		TYPE_CUBE,	// �����̂̓����蔻��
		TYPE_MAX
	};

	CCollision();	// �R���X�g���N�^
	~CCollision();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void ReleaseOther(void) { m_pObjectOther = nullptr; }	// �����������̂̉��
	bool TriggerCube(E_TAG tag);	// �L���[�u�̃g���K�[����
	bool ChckObstclBtwn(CObject *pObject, D3DXVECTOR3 vecDiff);	// �Ԃɏ�Q�������邩�̃`�F�b�N

	// �ϐ��擾�E�ݒ�֐�
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	// �ʒu
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; }	// �O��̈ʒu
	void SetPositionOld(D3DXVECTOR3 pos) { m_posOld = pos; }
	CCollision **GetCollision(void) { return &s_apCollision[0]; }	// �����蔻��̔z��
	E_TAG GetTag(void) { return m_tag; }	// �^�O
	void SetTag(E_TAG tag) { m_tag = tag; }
	E_TYPE GetType(void) { return m_type; }	// ���
	void SetType(E_TYPE type) { m_type = type; }
	virtual float GetRadius(void) { return 0.0f; }	// ���a
	void SetOwner(CObject *pObj) { m_pObjectOwner = pObj; }	// ������
	CObject *GetOwner(void) { return m_pObjectOwner; }
	void SetOther(CObject *pObj) { m_pObjectOther = pObj; }	// ������������
	CObject *GetOther(void) { return m_pObjectOther; }
	virtual D3DXVECTOR3 GetVtxMax(void) { return D3DXVECTOR3(0.0f,0.0f,0.0f); }	// �ő咸�_
	virtual D3DXVECTOR3 GetVtxMin(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }	// �ŏ����_

	// �ÓI�����o�֐�
	static bool IsCross(D3DXVECTOR3 posTarget, D3DXVECTOR3 vecSorce, D3DXVECTOR3 vecDest, float *fRate, D3DXVECTOR3 move = { 0.0f,0.0f,0.0f });	// �O�ς̔���
	static bool IsCrossTrigger(D3DXVECTOR3 posTarget, D3DXVECTOR3 posTargetOld, D3DXVECTOR3 vecSorce, D3DXVECTOR3 vecDest);	// �O�ς̃g���K�[����
	static int GetNumAll(void) { return s_nNumAll; }	// �����擾
	static void DeleteAll(void);	// �S�폜
	static CCollision *Create(E_TAG tag, E_TYPE type, CObject *obj);	// ��������

private:
	// �����o�ϐ�
	D3DXVECTOR3 m_pos;	// �ꏊ
	D3DXVECTOR3 m_posOld;	// �O��̏ꏊ
	E_TAG m_tag;	// ���ʗp�^�O
	E_TYPE m_type;	// ���
	int m_nID;	// �ԍ�
	CObject *m_pObjectOwner;	// ������
	CObject *m_pObjectOther;	// ������������

	// �ÓI�����o�ϐ�
	static CCollision *s_apCollision[NUM_OBJECT];	// �����蔻��̔z��
	static int s_nNumAll;	// ����
};

class CCollisionSphere : public CCollision
{// ���̓����蔻��
public:
	CCollisionSphere();	// �R���X�g���N�^
	~CCollisionSphere();	// �f�X�g���N�^
	
	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	bool SphereCollision(E_TAG tag);	// ���̔���	

	// �ϐ��擾�E�ݒ�֐�
	float GetRadius(void) { return m_fRadius; }	// ���a
	void SetRadius(float fRadius) { m_fRadius = fRadius; }
	bool IsTriggerExit(E_TAG tag);	// �g���K�[�ŏo������
	bool IsTriggerEnter(E_TAG tag);	// �g���K�[�œ���������

	// �ÓI�����o�֐�
	static CCollisionSphere *Create(E_TAG tag, E_TYPE type, CObject *obj);	// ��������

private:
	// �����o�ϐ�
	float m_fRadius;	// ���a
};

class CCollisionCube : public CCollision
{// �����̂̓����蔻��
public:
	CCollisionCube();	// �R���X�g���N�^
	~CCollisionCube();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	bool CollideCube(E_TAG tag, D3DXVECTOR3 *pMove);	// �L���[�u�̓����蔻��

	// �ϐ��擾�E�ݒ�֐�
	D3DXVECTOR3 GetVtxMax(void) { return m_vtxMax; }	// �ő咸�_
	D3DXVECTOR3 GetVtxMin(void) { return m_vtxMin; }	// �ŏ����_
	void SetVtx(D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin);	// �ő�E�ŏ����_
	D3DXVECTOR3 CollideVector(CObject *pObj);	// �x�N�g���Ƃ̔���

	// �ÓI�����o�֐�
	static CCollisionCube *Create(E_TAG tag, CObject *obj);	// ��������

private:
	// �����o�ϐ�
	D3DXVECTOR3 m_vtxMax;	// �ő咸�_
	D3DXVECTOR3 m_vtxMin;	// �ŏ����_
};


#endif