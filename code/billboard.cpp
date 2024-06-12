//*****************************************************
//
// ビルボードの処理[billboard.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "billboard.h"
#include "renderer.h"
#include "texture.h"

//=====================================================
// コンストラクタ
//=====================================================
CBillboard::CBillboard(int nPriority) : CPolygon3D(nPriority)
{

}

//=====================================================
// デストラクタ
//=====================================================
CBillboard::~CBillboard()
{

}

//=====================================================
// 生成処理
//=====================================================
CBillboard *CBillboard::Create(D3DXVECTOR3 pos, float width, float height)
{
	// インスタンス生成
	CBillboard *pBillboard = new CBillboard;

	if (pBillboard != nullptr)
	{
		// サイズ設定
		pBillboard->SetSize(width, height);

		pBillboard->SetPosition(pos);

		// 初期化処理
		pBillboard->Init();
	}

	return pBillboard;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CBillboard::Init(void)
{
	CPolygon3D::Init();

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CBillboard::Uninit(void)
{
	CPolygon3D::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CBillboard::Update(void)
{
	CPolygon3D::Update();
}

//=====================================================
// 描画処理
//=====================================================
void CBillboard::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	D3DXMATRIX *pMtx = GetMatrix();

	//ワールドマトリックス初期化
	D3DXMatrixIdentity(pMtx);

	//ビューマトリックス取得
	D3DXMATRIX mtxView;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに向ける
	D3DXMatrixInverse(pMtx, nullptr, &mtxView);
	pMtx->_41 = 0.0f;
	pMtx->_42 = 0.0f;
	pMtx->_43 = 0.0f;

	// 位置を反映
	D3DXVECTOR3 pos = GetPosition();
	D3DXMATRIX mtxTrans;
	D3DXMatrixTranslation(&mtxTrans,
		pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(pMtx, pMtx, &mtxTrans);

	// ワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD, pMtx);

	// 頂点バッファをデータストリームに設定
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	pDevice->SetStreamSource(0, pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャ設定
	int nIdx = GetIdxTexture();
	LPDIRECT3DTEXTURE9 pTexture = CTexture::GetInstance()->GetAddress(nIdx);
	pDevice->SetTexture(0, pTexture);

	// 描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}