//*****************************************************
//
// �e�̏���[shadow.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "shadow.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "game.h"
#include "block.h"
#include "debugproc.h"

//=====================================================
// �R���X�g���N�^
//=====================================================
CShadow::CShadow(int nPriority) : CPolygon3D(nPriority)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CShadow::~CShadow()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CShadow::Init(void)
{
	CPolygon3D::Init();

	SetMode(E_MODE::MODE_NORMAL);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CShadow::Uninit(void)
{
	// �p���N���X�̏I��
	CPolygon3D::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CShadow::Update(void)
{
	// �p���N���X�̍X�V
	CPolygon3D::Update();

	// �ϐ��錾
	float fHeight = 0.0f;

	// �u���b�N�̍������擾
	fHeight = CBlock::CheckShadow(GetPosition());

	// �e�̈ʒu�ݒ�
	SetPosition(D3DXVECTOR3(GetPosition().x, fHeight + 0.1f, GetPosition().z));
}

//=====================================================
// �`�揈��
//=====================================================
void CShadow::Draw(void)
{
	// �p���N���X�̕`��
	CPolygon3D::Draw();

	CDebugProc::GetInstance()->Print("\n�e�̈ʒu�F[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
}

//=====================================================
// ��������
//=====================================================
CShadow *CShadow::Create(D3DXVECTOR3 pos, float width, float height)
{
	CShadow *pShadow = nullptr;

	if (pShadow == nullptr)
	{
		pShadow = new CShadow;

		if (pShadow != nullptr)
		{
			// ������
			pShadow->Init();

			pShadow->SetPosition(pos);
			pShadow->SetSize(width, height);
			pShadow->SetVtx();

			// �e�N�X�`���̓Ǎ�
			int nIdx = CTexture::GetInstance()->Regist("data\\TEXTURE\\EFFECT\\effect000.png");
			pShadow->SetIdxTexture(nIdx);

			pShadow->SetColor(D3DXCOLOR(0.0f,0.0f,0.0f,1.0f));
		}
	}

	return pShadow;
}