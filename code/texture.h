//*****************************************************
//
// �e�N�X�`���̊Ǘ�[texture.h]
// Author:���R����
//
//*****************************************************

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "object.h"

namespace Texture
{
//*****************************************************
// �萔��`
//*****************************************************
const int MAX_TEX = 128;	// �e�N�X�`���̍ő吔

//*****************************************************
// �V���[�g�J�b�g�֐�
//*****************************************************
int GetIdx(const char *pFileName);	// �e�N�X�`���ԍ��̎擾
}

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CTexture
{
public:
	CTexture();	// �R���X�g���N�^
	~CTexture();	// �f�X�g���N�^
	
	// �����o�֐�
	HRESULT Load(void);
	void Unload(void);
	int Regist(const char *pFileName);
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);

	// �ÓI�����o�֐�
	static CTexture *Create(void);
	static int GetNumAll(void) { return s_nNumAll; }
	static CTexture *GetInstance(void) { return s_pTexture; }

private:
	// �����o�ϐ�
	LPDIRECT3DTEXTURE9 m_apTexture[Texture::MAX_TEX];	// �e�N�X�`���̔z��
	char *m_apFilename[Texture::MAX_TEX];	// �t�@�C�����̔z��

	// �ÓI�����o�ϐ�
	static int s_nNumAll;	// ����
	static CTexture *s_pTexture;	// ���g�̃|�C���^
};
#endif