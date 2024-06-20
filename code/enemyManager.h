//*****************************************************
//
// �G�}�l�[�W���[[enemyManager.h]
// Author:���R����
//
//*****************************************************
#ifndef _ENEMYMANAGER_H_	// ��d�C���N���[�h�h�~
#define _ENEMYMANAGER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"
#include "enemy.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CEnemyManager : public CObject
{
public:
	CEnemyManager();	// �R���X�g���N�^
	~CEnemyManager();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��
	CEnemy *CreateEnemy(D3DXVECTOR3 pos, CEnemy::TYPE type);	// �G�̐���

	// �ϐ��擾�E�ݒ�֐�
	CEnemy *GetHead(void) { return m_pHead; }	// ���X�g�̐擪
	void SetHead(CEnemy *pEnemy) { m_pHead = pEnemy; }
	CEnemy *GetTail(void) { return m_pTail; }	// ���X�g�̍Ō��
	void SetTail(CEnemy *pEnemy) { m_pTail = pEnemy; }

	// �ÓI�����o�֐�
	static CEnemyManager *Create(void);	// ��������
	static CEnemyManager *GetInstance(void) { return s_pEnemyManager; }	// �C���X�^���X�̎擾

private:
	// �����o�֐�
	void Load(void);	// �z�u�̓Ǎ�

	// �����o�ϐ�
	CEnemy *m_pHead;	// �擪�̃A�h���X
	CEnemy *m_pTail;	// �Ō���̃A�h���X
	
	// �ÓI�����o�ϐ�
	static CEnemyManager *s_pEnemyManager;	// ���g�̃|�C���^
};

#endif
