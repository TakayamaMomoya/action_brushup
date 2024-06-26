//*****************************************************
//
// Xファイルの処理[objectX.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _OBJECTX_H_	// 二重インクルード防止
#define _OBJECTX_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"
#include "model.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define NUM_TEX	(5)	// テクスチャの数

//*****************************************************
// クラス定義
//*****************************************************
class CObjectX : public CObject
{
public:
	CObjectX(int nPriority = 3);	// コンストラクタ
	~CObjectX();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	void JustDraw(void);	// 描画のみを行う
	void CalcMatrix(void);	// マトリックス計算
	void DrawShadow(void);	// 影の描画

	// 変数取得・設定関数
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	// 位置
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	// 取得処理
	void SetPositionOld(D3DXVECTOR3 pos) { m_posOld = pos; }	// 前回の位置
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }	// 移動量
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }	// 向き
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	void BindModel(int nIdx);	// モデルの割り当て
	int GetIdxModel(void) { return m_nIdxModel; }	// モデル番号
	void SetRadius(void);	// 半径
	float GetRadius(void) { return m_fRadius; }
	D3DXMATRIX *GetMatrix(void) { return &m_mtxWorld; }	// マトリックス
	void SetMatrix(D3DXMATRIX mtx) { m_mtxWorld = mtx; }
	D3DXVECTOR3 GetVtxMax(void) { return m_vtxMax; }	// 最大頂点
	D3DXVECTOR3 GetVtxMin(void) { return m_vtxMin; }	// 最小頂点
	void SetEmissiveCol(D3DXCOLOR col) { m_col = col; m_bChangeCol = true; }	// 色
	D3DXCOLOR GetEmissiveCol(void);
	void ResetColor(void) { m_bChangeCol = false; }
	float GetScale(void) { return m_fScale; }	// スケール
	void SetScale(float fScale) { m_fScale = fScale; }
	CModel::Model *GetModel(void) { return m_pModel; }	// モデル情報
	void SetModel(CModel::Model *pModel) { m_pModel = pModel; }

	// 静的メンバ関数
	static CObjectX *Create(D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f }, D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f });	// 生成処理

private:
	// メンバ変数	
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_posOld;	// 前回の位置
	D3DXVECTOR3 m_move;	// 移動量
	D3DXVECTOR3 m_rot;	//向き
	D3DXMATRIX m_mtxWorld;	//ワールドマトリックス
	D3DXMATRIX m_mtxRot;	// 回転マトリックス保存用
	D3DXVECTOR3 m_vecAxis;	// 回転軸
	D3DXCOLOR m_col;	// 色
	CModel::Model *m_pModel;	// モデル情報
	int m_nIdxModel;	// モデルの番号
	float m_fRadius;	// モデルの半径
	float m_fScale;	// スケール
	D3DXVECTOR3 m_vtxMax;	// 最大頂点
	D3DXVECTOR3 m_vtxMin;	// 最小頂点
	bool m_bChangeCol;	// 色変更フラグ
};

#endif