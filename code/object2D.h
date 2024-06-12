//*****************************************************
//
// 2Dポリゴンの処理[object2D.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _OBJECT2D_H_	// 二重インクルード防止
#define _OBJECT2D_H_

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "object.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CObject2D	: public CObject
{
public:
	CObject2D(int nPriority = 3);	// コンストラクタ
	~CObject2D();	//	デストラクタ

	// メンバ変数
	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理
	void SetVtx(void);	// 頂点設定

	// 変数取得・設定関数
	D3DXVECTOR2 GetSize(void) { return D3DXVECTOR2(m_fWidth, m_fHeigth); }	// サイズ
	void SetSize(float width, float height);
	float GetWidth(void) { return m_fWidth; }	// 幅
	float GetHeight(void) { return m_fHeigth; }	// 高さ
	void SetAnim(int nAnim, int nNumAnim, int nNumV);	// アニメーション
	void SetTex(D3DXVECTOR2 texLeftUp, D3DXVECTOR2 texRightDown);	// テクスチャ座標
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	// 位置
	void SetPosition(D3DXVECTOR3 pos);
	void SetRot(float fRot);// 向き設定処理
	float GetRot(void) { return m_fRot; }	// 向き取得処理
	D3DXCOLOR GetCol(void) { return m_col; }	// 色
	void SetCol(D3DXCOLOR col);
	void SetIdxTexture(int nIdx) { m_nIdxTexture = nIdx; }	// テクスチャ番号
	int GetIdxTexture(void) { return m_nIdxTexture; }

	// 静的メンバ関数
	static CObject2D *Create(int nPriority = 3);	// 生成処理

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファ
	D3DXVECTOR3 m_pos;	// 位置
	D3DXCOLOR m_col;	// 色
	float m_fRot;	// 向き
	float m_fWidth;	// 幅
	float m_fHeigth;	// 高さ
	int m_nIdxTexture;	// テクスチャの番号
};

#endif