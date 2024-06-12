//*****************************************************
//
// 3Dポリゴンの処理[polygon3D.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _POLYGON3D_H_	// 二重インクルード防止
#define _POLYGON3D_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CPolygon3D : public CObject
{
public:
	// 列挙型定義
	enum E_MODE
	{// 描画モード
		MODE_NORMAL = 0,	// 通常モード
		MODE_BILLBOARD,	// ビルボード
		MODE_STRETCHBILLBOARD,	// ストレッチビルボード
		MODE_MAX
	};

	CPolygon3D(int nPriority = 2);	// コンストラクタ
	~CPolygon3D();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理
	virtual void SetVtx(void);	// 頂点設定

	// 変数取得・設定関数
	float GetWidth(void) { return m_width; }	// 幅
	float GetHeight(void) { return m_heigth; }	// 幅
	void SetSize(float width, float height);	// サイズ
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	// 位置
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; }	// 前回の位置
	D3DXVECTOR3 GetRotation(void) { return m_rot; }	// 向き
	void SetRotation(D3DXVECTOR3 rot = { D3DX_PI * 0.5f,0.0f,0.0f }) { m_rot = rot; }
	void SetIdxTexture(int nIdx) { m_nIdxTexture = nIdx; }	// テクスチャ番号
	int GetIdxTexture(void) { return m_nIdxTexture; }
	D3DXCOLOR GetColor(void) { return m_col; }	// 色
	void SetColor(D3DXCOLOR col);
	void SetTex(D3DXVECTOR2 rd, D3DXVECTOR2 lu);	// テクスチャ番号
	void SetFactSB(float fFact) { m_fFactSB = fFact; }	// ストレッチビルボードの補正値
	void SetMode(E_MODE mode);	// 描画モード
	E_MODE GetMode(void) { return m_mode; }
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }	// 頂点バッファ
	D3DXMATRIX *GetMatrix(void) { return &m_mtxWorld; }	// マトリックス

	// 静的メンバ関数
	static CPolygon3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f });	// 生成処理

private:
	// メンバ関数
	void SetVtxNormal(void);	// 通常の法線設定
	void SetVtxStretchBillboard(void);	// ストレッチビルボードの頂点設定
	void SetMtx(void);	// マトリックス設定
	void SetMtxBillboard(void);	// ビルボードのマトリックス設定

	// メンバ変数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_posOld;	// 前回の位置
	D3DXVECTOR3 m_rot;	//向き
	D3DXMATRIX m_mtxWorld;	//ワールドマトリックス
	D3DXCOLOR m_col;	// 色
	float m_width;	// 幅
	float m_heigth;	// 高さ
	float m_fFactSB;	// ストレッチビルボードのときの見やすさの補正
	int m_nIdxTexture;	// テクスチャの番号
	E_MODE m_mode;	// モード
};

#endif