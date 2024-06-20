//*****************************************************
//
// �p�[�e�B�N������[particle.h]
// Author:���R����
//
//*****************************************************
#ifndef _PARTICLE_H_	// ��d�C���N���[�h�h�~
#define _PARTICLE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �N���X��`
//*****************************************************
class CParticle : public CObject
{
public:
	// �񋓌^��`
	enum E_TYPE
	{// �p�[�e�B�N���̎��
		TYPE_NONE = 0,	// ���ł��Ȃ�
		TYPE_EXPLOSION,	// ����
		TYPE_FLASH,	// �Ή�
		TYPE_FIRE,	// ��
		TYPE_MAX
	};

	CParticle(int nPriority = 3);	// �R���X�g���N�^
	~CParticle();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V
	void Draw(void) {};  // �`��

	// �ÓI�����o�֐�
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	// �ʒu
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPositionOld(void) { return D3DXVECTOR3(); }	// �O��̈ʒu
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };	// ����
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	float GetWidth(void) { return 0.0f; }	// ��
	float GetHeight(void) { return 0.0f; }	// ����

	// �ÓI�����o�֐�
	static CParticle *Create(D3DXVECTOR3 pos, E_TYPE type, D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f }, D3DXVECTOR3 *pPosOwner = nullptr, int nPriorityEffect = 5);	// ��������
	static void Load(void);	// �Ǎ�����
	static void Unload(void);	// �j������

private:
	// �\���̒�`
	struct S_PARTICLE_INFO
	{// �p�[�e�B�N�����
		int nLife;	// ����
		int nLifeEffect;	// �G�t�F�N�g�̎���
		float fRadiusEffect;	// �G�t�F�N�g�̔��a
		int nNumEffect;	// �G�t�F�N�g�̐�
		float fSpeed;	// �G�t�F�N�g�̊�X�s�[�h
		D3DXCOLOR col;	// �F
		int nAdd;	// ���Z���������邩�ǂ���
		float fGravity;	// �d��
		float fDecrease;	// ���a������
		float fRangeRot;	// �����̃����_���͈�
		int nRot;	// �����𔽉f���邩�ǂ���
		bool bTurn;	// ���]���邩�ǂ���
		// �R���X�g���N�^
		S_PARTICLE_INFO() : nLife(0), nLifeEffect(0) {}
	};

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 *m_pPosOwner;	// ������̈ʒu
	D3DXVECTOR3 m_rot;	// ����
	int m_nLife;	// ����
	E_TYPE m_type; // ���
	int m_nPriorityEffect;	// �`��v���C�I���e�B
	
	// �ÓI�����o�ϐ�
	static S_PARTICLE_INFO *s_apParticleInfo[TYPE_MAX + 1];	// �p�[�e�B�N���̏��
};

#endif