//*****************************************************
//
// �u���b�N�̏���[block.cpp]
// Author:���R����
//
//*****************************************************

#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "ObjectX.h"

//*****************************************************
// �O���錾
//*****************************************************
class CCollisionCube;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CBlock : public CObjectX
{
public:
	// �񋓌^��`
	enum E_TYPE
	{// ���
		TYPE_FLOOR,	// ��
		TYPE_CHAIR,	// �֎q
		TYPE_DESK,	// ��
		TYPE_DOCUMENT,	// ����
		TYPE_FUN,	// ���C��
		TYPE_LOCKER,	// ���b�J�[
		TYPE_WINDOW,	// ��
		TYPE_FLOORBIG,	// �ł���
		TYPE_WINDOWBIG,	// �ł���
		TYPE_CASE00,	// ���ӂ��P
		TYPE_CASE01,	// ���ӂ���
		TYPE_CASE02,	// ���ӂ���
		TYPE_FLOOR4,	// ���~�S
		TYPE_ROOFTOPBIG,	// ���㏰
		TYPE_ROOFTOP4,	// ���㏰�~�S
		TYPE_ROOFTOP1,	// ���㏰�~�P
		TYPE_HELIPORT,	// �w���|�[�g
		TYPE_FRONTWINDOW,	// ��O�̑�
		TYPE_SIDEWINDOW,	// ���̑�
		TYPE_WALL,	// ��
		TYPE_WALL2,	// ��2
		TYPE_WALL3,	// ��3
		TYPE_SIDEWINDOWBIG,	// �ł�����
		TYPE_FRONTWINDOW4,	// ��O��4
		TYPE_LONGDESK,	// ����
		TYPE_MAX
	};

	// �\���̒�`
	struct MemBlock
	{// �ۑ�����Ƃ��̏��
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 rot;	// ����
		E_TYPE type;	// ���
	};

	CBlock(int nPriority = 3);	// �R���X�g���N�^
	~CBlock();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V
	void Draw(void);  // �`��

	// �ÓI�����o�֐�
	static CBlock *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, E_TYPE type);	// ��������
	static HRESULT Load(char *pPath);	// �Ǎ�
	static void Save(void);	// �ۑ�
	static void Delete(int nIdx);	// �����폜����
	static void DeleteAll(void);	// �S�폜����
	static int GetNumAll(void) { return s_nNumAll; }	// �����擾
	static CBlock **GetBlock(void) { return &s_apBlock[0]; }	// �u���b�N�擾
	static float CheckShadow(D3DXVECTOR3 pos);	// �e�̃`�F�b�N
	static void LoadModel(void);	// ���f���Ǎ�
	static void DeleteIdx(void);	// �ԍ��̍폜
	static int *GetIndex(void) { return s_pIdxObject; }	// �ԍ��̎擾

private:
	// �����o�ϐ�
	E_TYPE m_type;	// ���
	CCollisionCube *m_pCollisionCube;	// �����̂̓����蔻��
	int m_nLife;	// �̗�

	// �ÓI�����o�ϐ�
	static int *s_pIdxObject;	// ���f���̃^�C�v�ԍ��̃|�C���^
	static CBlock *s_apBlock[NUM_OBJECT];	// �u���b�N�̔z��
	static int s_nNumAll;	// ����
};

#endif
