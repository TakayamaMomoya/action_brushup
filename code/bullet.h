//*****************************************************
//
// �e����[bullet.h]
// Author:���R����
//
//*****************************************************

#ifndef _BULLET_H_
#define _BULLET_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object2D.h"
#include "collision.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define NUM_ORBIT	(4)	// �O�Ղ̐�
#define MAX_HIT	(54)	// �ő�Ŋo�����閽�������I�u�W�F�N�g

//*****************************************************
// �O���錾
//*****************************************************
class CCollisionSphere;
class COrbit;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CBullet : public CObject
{
public:
	typedef enum
	{
		TYPE_NONE = 0,	// ���ł��Ȃ�
		TYPE_PLAYER,	// �v���C���[�̒e
		TYPE_ENEMY,	// �G�̒e
		TYPE_MAX
	}TYPE;

	CBullet(int nPriority = 6);	// �R���X�g���N�^
	~CBullet();	// �f�X�g���N�^

	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, TYPE type, bool bPierce = false, float fRadius = 10.0f, float fDamage = 5.0f, D3DXCOLOR col = { 1.0f,1.0f,1.0f,1.0f });
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static int GetNumAll(void) { return m_nNumAll; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; }

private:
	bool BulletHit(CCollision::TAG tag);
	void Death(void);

	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_move;	// �ړ���
	D3DXVECTOR3 m_rot;	// ����
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_posOld;	// �O��̈ʒu
	int m_nLife;	// ����
	TYPE m_type;	// ���
	static int m_nNumAll;	// ����
	bool m_bPierce;	// �ђʂ��邩�ǂ���
	CCollisionSphere *m_pCollisionSphere;	// ���̓����蔻��
	COrbit *m_apOrbit[NUM_ORBIT];	// �O�Ղ̃|�C���^
	D3DXCOLOR m_col;	// �F
	float m_fDamage;	// �^�_���[�W
	float m_fSize;	// �e�̃T�C�Y
};

#endif