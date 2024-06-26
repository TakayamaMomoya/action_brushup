//*****************************************************
//
// 2Dポリゴンの処理[object2D.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "object2D.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//=====================================================
// 優先順位を決めるコンストラクタ
//=====================================================
CObject2D::CObject2D(int nPriority) : CObject(nPriority), m_pVtxBuff(nullptr), m_pos{}, m_fRot(0.0f), m_fHeigth(0.0f), m_fWidth(0.0f), m_col{}, m_nIdxTexture(-1)
{

}

//=====================================================
// デストラクタ
//=====================================================
CObject2D::~CObject2D()
{

}

//=====================================================
// 生成処理
//=====================================================
CObject2D *CObject2D::Create(int nPriority)
{
	CObject2D *pObject2D = nullptr;

	if (pObject2D == nullptr)
	{
		// インスタンス生成
		pObject2D = new CObject2D(nPriority);

		if (pObject2D != nullptr)
		{
			// 初期化処理
			pObject2D->Init();
		}
	}

	return pObject2D;
}

//=====================================================
// 初期化
//=====================================================
HRESULT CObject2D::Init(void)
{
	// 色の初期化
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	if (pDevice != nullptr)
	{
		if (m_pVtxBuff == nullptr)
		{
			// 頂点バッファの生成
			pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
				D3DUSAGE_WRITEONLY,
				FVF_VERTEX_2D,
				D3DPOOL_MANAGED,
				&m_pVtxBuff,
				nullptr);
		}
	}

	// 頂点情報のポインタ
	VERTEX_2D *pVtx;

	if (m_pVtxBuff != nullptr)
	{
		// 頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			pVtx[nCnt].pos = { 0.0f,0.0f,0.0f };
			pVtx[nCnt].rhw = 1.0;
			pVtx[nCnt].col = m_col;
			pVtx[nCnt].tex = D3DXVECTOR2(0.0f, 0.0f);
		}

		// 対角線の角度取得
		float fAngleUp = atan2f(m_fWidth, m_fHeigth);
		// 長さの取得
		float fLengthUp = sqrtf(m_fWidth * m_fWidth + m_fHeigth * m_fHeigth);

		// 頂点座標の設定
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

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点バッファのアンロック
		m_pVtxBuff->Unlock();
	}

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CObject2D::Uninit(void)
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// 自分自身の破棄
	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CObject2D::Update(void)
{

}

//=====================================================
// 頂点位置設定
//=====================================================
void CObject2D::SetVtx(void)
{
	// 頂点情報のポインタ
	VERTEX_2D *pVtx;

	if (m_pVtxBuff != nullptr)
	{
		// 頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 対角線の角度取得
		float fAngleUp = atan2f(m_fWidth, m_fHeigth);
		// 長さの取得
		float fLengthUp = sqrtf(m_fWidth * m_fWidth + m_fHeigth * m_fHeigth);

		// 頂点座標の設定
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

		// 頂点バッファのアンロック
		m_pVtxBuff->Unlock();
	}

}

//=====================================================
// 描画
//=====================================================
void CObject2D::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	if (pDevice != nullptr)
	{
		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		LPDIRECT3DTEXTURE9 pTexture = CTexture::GetInstance()->GetAddress(m_nIdxTexture);

		// テクスチャ設定
		pDevice->SetTexture(0, pTexture);

		// 背景の描画
 		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//=====================================================
// 設定処理
//=====================================================
void CObject2D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=====================================================
// サイズ設定処理
//=====================================================
void CObject2D::SetSize(float width, float height)
{
	m_fWidth = width;
	m_fHeigth = height;
}

//=====================================================
// テクスチャ座標設定処理
//=====================================================
void CObject2D::SetTex(D3DXVECTOR2 texLeftUp, D3DXVECTOR2 texRightDown)
{
	if (m_pVtxBuff == nullptr)
	{
		return;
	}

	// 頂点情報のポインタ
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標
	pVtx[0].tex = texLeftUp;
	pVtx[1].tex = D3DXVECTOR2(texRightDown.x, texLeftUp.y);
	pVtx[2].tex = D3DXVECTOR2(texLeftUp.x, texRightDown.y);
	pVtx[3].tex = texRightDown;

	// 頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//=====================================================
// アニメーション設定処理
//=====================================================
void CObject2D::SetAnim(int nAnim,int nNumAnim,int nNumV)
{
	// 頂点情報のポインタ
	VERTEX_2D *pVtx;

	if (m_pVtxBuff != nullptr)
	{
		// 頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// テクスチャ座標
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

		// 頂点バッファのアンロック
		m_pVtxBuff->Unlock();
	}
}

//=====================================================
// 向き設定処理
//=====================================================
void CObject2D::SetRot(float fRot)
{
	m_fRot = fRot;
}

//=====================================================
// 色設定処理
//=====================================================
void CObject2D::SetCol(D3DXCOLOR col)
{
	m_col = col;

	// 頂点情報のポインタ
	VERTEX_2D *pVtx;

	if (m_pVtxBuff != nullptr)
	{
		// 頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			pVtx[nCnt].col = m_col;
		}

		// 頂点バッファのアンロック
		m_pVtxBuff->Unlock();
	}
}