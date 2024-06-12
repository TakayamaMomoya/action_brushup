//*****************************************************
//
// 2D�|���S���̏���[object2D.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object2D.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//=====================================================
// �D�揇�ʂ����߂�R���X�g���N�^
//=====================================================
CObject2D::CObject2D(int nPriority) : CObject(nPriority), m_pVtxBuff(nullptr), m_pos{}, m_fRot(0.0f), m_fHeigth(0.0f), m_fWidth(0.0f), m_col{}, m_nIdxTexture(-1)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CObject2D::~CObject2D()
{

}

//=====================================================
// ��������
//=====================================================
CObject2D *CObject2D::Create(int nPriority)
{
	CObject2D *pObject2D = nullptr;

	if (pObject2D == nullptr)
	{
		// �C���X�^���X����
		pObject2D = new CObject2D(nPriority);

		if (pObject2D != nullptr)
		{
			// ����������
			pObject2D->Init();
		}
	}

	return pObject2D;
}

//=====================================================
// ������
//=====================================================
HRESULT CObject2D::Init(void)
{
	// �F�̏�����
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	if (pDevice != nullptr)
	{
		if (m_pVtxBuff == nullptr)
		{
			// ���_�o�b�t�@�̐���
			pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
				D3DUSAGE_WRITEONLY,
				FVF_VERTEX_2D,
				D3DPOOL_MANAGED,
				&m_pVtxBuff,
				nullptr);
		}
	}

	// ���_���̃|�C���^
	VERTEX_2D *pVtx;

	if (m_pVtxBuff != nullptr)
	{
		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			pVtx[nCnt].pos = { 0.0f,0.0f,0.0f };
			pVtx[nCnt].rhw = 1.0;
			pVtx[nCnt].col = m_col;
			pVtx[nCnt].tex = D3DXVECTOR2(0.0f, 0.0f);
		}

		// �Ίp���̊p�x�擾
		float fAngleUp = atan2f(m_fWidth, m_fHeigth);
		// �����̎擾
		float fLengthUp = sqrtf(m_fWidth * m_fWidth + m_fHeigth * m_fHeigth);

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3
		(
			m_pos.x + sinf(m_fRot - D3DX_PI + fAngleUp) * fLengthUp,
			m_pos.y + cosf(m_fRot - D3DX_PI + fAngleUp) * fLengthUp,
			0.0f
		);
		pVtx[1].pos = D3DXVECTOR3
		(
			m_pos.x + sinf(m_fRot + D3DX_PI - fAngleUp) * fLengthUp,
			m_pos.y + cosf(m_fRot + D3DX_PI - fAngleUp) * fLengthUp,
			0.0f
		);
		pVtx[2].pos = D3DXVECTOR3
		(
			m_pos.x + sinf(m_fRot - fAngleUp) * fLengthUp,
			m_pos.y + cosf(m_fRot - fAngleUp) * fLengthUp,
			0.0f
		);
		pVtx[3].pos = D3DXVECTOR3
		(
			m_pos.x + sinf(m_fRot + fAngleUp) * fLengthUp,
			m_pos.y + cosf(m_fRot + fAngleUp) * fLengthUp,
			0.0f
		);

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�o�b�t�@�̃A�����b�N
		m_pVtxBuff->Unlock();
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CObject2D::Uninit(void)
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// �������g�̔j��
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CObject2D::Update(void)
{

}

//=====================================================
// ���_�ʒu�ݒ�
//=====================================================
void CObject2D::SetVtx(void)
{
	// ���_���̃|�C���^
	VERTEX_2D *pVtx;

	if (m_pVtxBuff != nullptr)
	{
		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// �Ίp���̊p�x�擾
		float fAngleUp = atan2f(m_fWidth, m_fHeigth);
		// �����̎擾
		float fLengthUp = sqrtf(m_fWidth * m_fWidth + m_fHeigth * m_fHeigth);

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3
		(
			m_pos.x + sinf(m_fRot - D3DX_PI + fAngleUp) * fLengthUp,
			m_pos.y + cosf(m_fRot - D3DX_PI + fAngleUp) * fLengthUp,
			0.0f
		);
		pVtx[1].pos = D3DXVECTOR3
		(
			m_pos.x + sinf(m_fRot + D3DX_PI - fAngleUp) * fLengthUp,
			m_pos.y + cosf(m_fRot + D3DX_PI - fAngleUp) * fLengthUp,
			0.0f
		);
		pVtx[2].pos = D3DXVECTOR3
		(
			m_pos.x + sinf(m_fRot - fAngleUp) * fLengthUp,
			m_pos.y + cosf(m_fRot - fAngleUp) * fLengthUp,
			0.0f
		);
		pVtx[3].pos = D3DXVECTOR3
		(
			m_pos.x + sinf(m_fRot + fAngleUp) * fLengthUp,
			m_pos.y + cosf(m_fRot + fAngleUp) * fLengthUp,
			0.0f
		);

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			pVtx[nCnt].col = m_col;
		}

		// ���_�o�b�t�@�̃A�����b�N
		m_pVtxBuff->Unlock();
	}

}

//=====================================================
// �`��
//=====================================================
void CObject2D::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	if (pDevice != nullptr)
	{
		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		LPDIRECT3DTEXTURE9 pTexture = CTexture::GetInstance()->GetAddress(m_nIdxTexture);

		// �e�N�X�`���ݒ�
		pDevice->SetTexture(0, pTexture);

		// �w�i�̕`��
 		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//=====================================================
// �ݒ菈��
//=====================================================
void CObject2D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=====================================================
// �T�C�Y�ݒ菈��
//=====================================================
void CObject2D::SetSize(float width, float height)
{
	m_fWidth = width;
	m_fHeigth = height;
}

//=====================================================
// �e�N�X�`�����W�ݒ菈��
//=====================================================
void CObject2D::SetTex(D3DXVECTOR2 texLeftUp, D3DXVECTOR2 texRightDown)
{
	if (m_pVtxBuff == nullptr)
	{
		return;
	}

	// ���_���̃|�C���^
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W
	pVtx[0].tex = texLeftUp;
	pVtx[1].tex = D3DXVECTOR2(texRightDown.x, texLeftUp.y);
	pVtx[2].tex = D3DXVECTOR2(texLeftUp.x, texRightDown.y);
	pVtx[3].tex = texRightDown;

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//=====================================================
// �A�j���[�V�����ݒ菈��
//=====================================================
void CObject2D::SetAnim(int nAnim,int nNumAnim,int nNumV)
{
	// ���_���̃|�C���^
	VERTEX_2D *pVtx;

	if (m_pVtxBuff != nullptr)
	{
		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2
		(
			(1.0f / nNumAnim) * nAnim,
			0.0f
		);
		pVtx[1].tex = D3DXVECTOR2
		(
			1.0f / nNumAnim + 1.0f / nNumAnim * nAnim,
			0.0f
		);
		pVtx[2].tex = D3DXVECTOR2
		(
			1.0f / nNumAnim * nAnim,
			1.0f
		);
		pVtx[3].tex = D3DXVECTOR2
		(
			1.0f / nNumAnim + 1.0f / nNumAnim * nAnim,
			1.0f
		);

		// ���_�o�b�t�@�̃A�����b�N
		m_pVtxBuff->Unlock();
	}
}

//=====================================================
// �����ݒ菈��
//=====================================================
void CObject2D::SetRot(float fRot)
{
	m_fRot = fRot;
}

//=====================================================
// �F�ݒ菈��
//=====================================================
void CObject2D::SetCol(D3DXCOLOR col)
{
	m_col = col;

	// ���_���̃|�C���^
	VERTEX_2D *pVtx;

	if (m_pVtxBuff != nullptr)
	{
		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			pVtx[nCnt].col = m_col;
		}

		// ���_�o�b�t�@�̃A�����b�N
		m_pVtxBuff->Unlock();
	}
}