//*****************************************************
//
// 2Dエフェクト処理[effect2D.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _EFFECT2D_H_	// 二重インクルード防止
#define _EFFECT2D_H_

//*****************************************************
// インクルード
//*****************************************************
#include "Object2D.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CEffect2D : public CObject2D
{
public:
	CEffect2D(int nPriority = 5);	// コンストラクタ
	~CEffect2D();	// デストラクタ

	// メンバ関数
	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);  // 描画

	// 変数取得・設定関数
	D3DXVECTOR3 GetMove(void) { return m_move; }	// 移動量
	void SetMove(D3DXVECTOR3 move) { m_move = move; }

	// 静的メンバ関数
	static CEffect2D *Create(D3DXVECTOR3 pos, float fRadius, int nLife, D3DXCOLOR col, D3DXVECTOR3 move = { 0.0f,0.0f,0.0f });

private:
	// メンバ変数
	int m_nLife;	// 寿命
	float m_fDecrease;	// 減少量
	D3DXVECTOR3 m_move;	// 移動量
};

#endif