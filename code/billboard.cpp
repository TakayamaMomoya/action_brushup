//*****************************************************
//
// �r���{�[�h�̏���[billboard.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "billboard.h"
#include "renderer.h"
#include "texture.h"

//=====================================================
// �R���X�g���N�^
//=====================================================
CBillboard::CBillboard(int nPriority) : CPolygon3D(nPriority)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CBillboard::~CBillboard()
{

}

//=====================================================
// ��������
//=====================================================
CBillboard *CBillboard::Create(D3DXVECTOR3 pos, float width, float height)
{
	// �C���X�^���X����
	CBillboard *pBillboard = new CBillboard;

	if (pBillboard != nullptr)
	{
		// �T�C�Y�ݒ�
		pBillboard->SetSize(width, height);

		pBillboard->SetPosition(pos);

		// ����������
		pBillboard->Init();
	}

	return pBillboard;
}

//=====================================================
// ����������
//=====================================================
HRESULT CBillboard::Init(void)
{
	CPolygon3D::Init();

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CBillboard::Uninit(void)
{
	CPolygon3D::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CBillboard::Update(void)
{
	CPolygon3D::Update();
}

//=====================================================
// �`�揈��
//=====================================================
void CBillboard::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	D3DXMATRIX *pMtx = GetMatrix();

	//���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(pMtx);

	//�r���[�}�g���b�N�X�擾
	D3DXMATRIX mtxView;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����Ɍ�����
	D3DXMatrixInverse(pMtx, nullptr, &mtxView);
	pMtx->_41 = 0.0f;
	pMtx->_42 = 0.0f;
	pMtx->_43 = 0.0f;

	// �ʒu�𔽉f
	D3DXVECTOR3 pos = GetPosition();
	D3DXMATRIX mtxTrans;
	D3DXMatrixTranslation(&mtxTrans,
		pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(pMtx, pMtx, &mtxTrans);

	// ���[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_WORLD, pMtx);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	pDevice->SetStreamSource(0, pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���ݒ�
	int nIdx = GetIdxTexture();
	LPDIRECT3DTEXTURE9 pTexture = CTexture::GetInstance()->GetAddress(nIdx);
	pDevice->SetTexture(0, pTexture);

	// �`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}