//*****************************************************
//
// �I�u�W�F�N�g�̏���[object.h]
// Author:���R����
//
//*****************************************************
#ifndef _OBJECT_H_	// ��d�C���N���[�h�h�~
#define _OBJECT_H_

//*****************************************************
// �O���錾
//*****************************************************
class CPlayer;
class CBlock;

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const int NUM_OBJECT = 4096;	// �I�u�W�F�N�g�̐�
const int NUM_PRIORITY = 8;	// �D�揇�ʂ̐�
}

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CObject
{
public:
	// �񋓌^��`
	enum E_TYPE
	{
		TYPE_NONE = 0,	// ���ł��Ȃ�
		TYPE_PLAYER,	// �v���C���[
		TYPE_ENEMY,	// �G
		TYPE_BLOCK,	// �u���b�N
		TYPE_BULLET,	// �e
		TYPE_PARTICLE,	// �p�[�e�B�N��
		TYPE_MAX
	};

	CObject(int nPriority = 3);	// �R���X�g���N�^
	virtual ~CObject();	//	�f�X�g���N�^

	// �����o�֐�
	virtual HRESULT Init(void) = 0;	// ����������
	virtual void Uninit(void) = 0;	// �I������
	virtual void Update(void) = 0;	// �X�V����
	virtual void Draw(void) {};	// �`�揈��
	virtual void Hit(float fDamage){}	// �q�b�g����
	
	// �ϐ��擾�E�ݒ�֐�
	void SetType(E_TYPE type);	// ���
	E_TYPE GetType(void) { return m_type; }
	virtual void SetPosition(D3DXVECTOR3 pos) {};	// �ʒu
	virtual D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(); }
	virtual void SetPositionOld(D3DXVECTOR3 pos) {};	// �O��̈ʒu
	virtual D3DXVECTOR3 GetPositionOld(void) { return D3DXVECTOR3(); };
	void EnableWire(bool bWire) { m_bWire = bWire; }	// ���C���[�t���[��
	bool IsDeath(void) { return m_bDeath; }	// ���S�t���O
	void EnableZtest(bool bZtest) { m_bZtest = bZtest; }	// Z�e�X�g�t���O
	void EnableLighting(bool bLighting) { m_bLighting = bLighting; }	// ���C�e�B���O�t���O
	void EnableAdd(bool bAdd) { m_bAdd = bAdd; }	// ���Z�����t���O
	void EnableFog(bool bFog) { m_bFog = bFog; }	// �t�H�O�t���O
	void EnableCull(bool bCull) { m_bCull = bCull; }	// �J�����O�t���O
	void SetAlphaTest(DWORD dValue) { m_dwAlpha = dValue; }	// �A���t�@�e�X�g�������l
	DWORD GetAlpha(void) { return m_dwAlpha; }

	// �ÓI�����o�֐�
	static void ReleaseAll(void);	// �S�ă����[�X
	static void UpdateAll(void);	// �S�čX�V
	static void DeleteAll(void);	// �S�폜����
	static void DrawAll(void);	// �S�ĕ`��
	static int GetNumAll(void) { return s_nNumAll; }	// �����擾

protected:
	// �����o�֐�
	void Release(void);	// �ʃ����[�X����

private:
	// �����o�֐�
	void Delete(void);	// �ʍ폜����

	// �����o�ϐ�
	int m_nID;	// ������ID
	E_TYPE m_type;	// ���
	int m_nPriority;	// �`��̗D�揇��
	CObject *m_pPrev;	// �O�̃I�u�W�F�N�g�̃A�h���X
	CObject *m_pNext;	// ���̃I�u�W�F�N�g�̃A�h���X
	bool m_bDeath;	// ���S�t���O
	bool m_bWire;	// ���C���[�t���[���ŕ\�����邩�ǂ���
	bool m_bZtest;	// Z�e�X�g�őO�ɏo�����ǂ���
	bool m_bLighting;	// ���C�e�B���O��L�������邩�ǂ���
	bool m_bAdd;	// ���Z�������邩�ǂ���
	bool m_bFog;	// �t�H�O�������邩�ǂ���
	bool m_bCull;	// �J�����O���邩�ǂ���
	DWORD m_dwAlpha;	// �A���t�@�e�X�g�̒l

	// �ÓI�����o�ϐ�
	static int s_nNumAll;	// ����
	static CObject *s_apTop[NUM_PRIORITY];	// �擪�̃I�u�W�F�N�g�̃A�h���X
	static CObject *s_apCur[NUM_PRIORITY];	// �Ō���̃I�u�W�F�N�g�̃A�h���X
};

namespace Object
{
//*****************************************************
// �V���[�g�J�b�g�֐�
//*****************************************************
void DeleteObject(CObject **ppObject, int nSize = 1);	// �I�u�W�F�N�g�̔j��
}

#endif