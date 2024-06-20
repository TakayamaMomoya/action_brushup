//*****************************************************
//
// �e�N�X�`���̊Ǘ�[texture.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "texture.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************
// �萔��`
//*****************************************************
#define MAX_STRING (256)	// �ő�̕�����

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
int CTexture::s_nNumAll = 0;	// ����
CTexture *CTexture::s_pTexture = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CTexture::CTexture()
{
	s_pTexture = this;

	ZeroMemory(&m_apFilename[0], sizeof(m_apFilename));
	ZeroMemory(&m_apTexture[0], sizeof(m_apTexture));
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CTexture::~CTexture()
{
	s_pTexture = nullptr;
}

//=====================================================
// ��������
//=====================================================
CTexture *CTexture::Create(void)
{
	if (s_pTexture == nullptr)
	{
		s_pTexture = new CTexture;

		if (s_pTexture != nullptr)
		{
			s_pTexture->Load();
		}
	}

	return s_pTexture;
}

//=====================================================
// �Ǎ�����
//=====================================================
HRESULT CTexture::Load(void)
{
	// �t�@�C�����̐ݒ�
	char *apFileName[] = 
	{
		"data\\TEXTURE\\EFFECT\\muzzleFlush.png",
		"data\\TEXTURE\\EFFECT\\beam.png",
		"data\\TEXTURE\\EFFECT\\hit00.png",
		"data\\TEXTURE\\UI\\pause_quit.png",
		"data\\TEXTURE\\UI\\pause_restart.png",
		"data\\TEXTURE\\UI\\pause_resume.png",
		"data\\TEXTURE\\EFFECT\\energy00.png",
		"data\\TEXTURE\\EFFECT\\blade.png",
		"data\\TEXTURE\\EFFECT\\explosion.png",
		"data\\TEXTURE\\UI\\menu_resume.png",
		"data\\TEXTURE\\UI\\menu_retry.png",
		"data\\TEXTURE\\UI\\menu_quit.png",
	};

	for ( int nCntTex = 0;nCntTex < sizeof(apFileName) / sizeof(char*);nCntTex++)
	{
		if (apFileName[nCntTex] != nullptr)
		{// �t�@�C��������������e�N�X�`���̓Ǎ�
			// �f�o�C�X�̎擾
			LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

			// �e�N�X�`���̓Ǎ�
			D3DXCreateTextureFromFile
			(pDevice, apFileName[nCntTex],&m_apTexture[nCntTex]);

			// �t�@�C�����ۑ�
			m_apFilename[nCntTex] = apFileName[nCntTex];

			// �����J�E���g�A�b�v
			s_nNumAll++;
		}
	}

	return S_OK;
}

//=====================================================
// �S�j������
//=====================================================
void CTexture::Unload(void)
{
	for (int nCntTex = 0; nCntTex < Texture::MAX_TEX; nCntTex++)
	{
		if (m_apTexture[nCntTex] != nullptr)
		{
			if (m_apTexture[nCntTex] != nullptr)
			{
				m_apTexture[nCntTex]->Release();
				m_apTexture[nCntTex] = nullptr;
				s_nNumAll--;
			}
		}
	}
}

//=====================================================
// �ʓǍ�
//=====================================================
int CTexture::Regist(const char *pFileName)
{
	if (pFileName == nullptr)
	{
		return -1;
	}

	for (int nCntTex = 0; nCntTex < Texture::MAX_TEX; nCntTex++)
	{
		if (m_apFilename[nCntTex] != nullptr)
		{
			if (strcmp(&m_apFilename[nCntTex][0], &pFileName[0]) == 0)
			{// �t�@�C�����������ꍇ�A���݂̔ԍ���Ԃ�
 				return nCntTex;
			}
		}
	}

	// �V�����e�N�X�`����ǂݍ��ޏꍇ��

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	// �e�N�X�`���̓Ǎ�
	D3DXCreateTextureFromFile
	(pDevice, pFileName, &m_apTexture[s_nNumAll]);

	m_apFilename[s_nNumAll] = new char[MAX_STRING];

	// �t�@�C�����̕ۑ�
	strcpy(m_apFilename[s_nNumAll], pFileName);

	// ���݂̔ԍ���ۑ�
	int nIdx = s_nNumAll;

	// �����J�E���g�A�b�v
	s_nNumAll++;

	return nIdx;
}

//=====================================================
// �A�h���X�擾����
//=====================================================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	if (nIdx == -1)
	{
		return nullptr;
	}
	else
	{
		return m_apTexture[nIdx];
	}
}

namespace Texture
{
//=====================================================
// �e�N�X�`���ԍ��̎擾�i�V���[�g�J�b�g�֐��j
//=====================================================
int GetIdx(const char *pFileName)
{
	CTexture *pTexture = CTexture::GetInstance();

	if (pTexture == nullptr)
		return -1;

	int nIdx = pTexture->Regist(pFileName);

	return nIdx;
}
}