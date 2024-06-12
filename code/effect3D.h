//*****************************************************
//
// 3Dエフェクト処理[effect3D.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _EFFECT3D_H_	// 二重インクルード防止
#define _EFFECT3D_H_

//*****************************************************
// インクルード
//*****************************************************
#include "billboard.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CEffect3D : public CBillboard
{
public:
	CEffect3D(int nPriority = 6);	// コンストラクタ
	~CEffect3D();	// デストラクタ

	// メンバ関数
	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);  // 描画

	// 静的メンバ関数
	// 生成処理
	static CEffect3D *Create(D3DXVECTOR3 pos, float fRadius, int nLife, D3DXCOLOR col, D3DXVECTOR3 move = { 0.0f,0.0f,0.0f },
		float fGravity = 0.0f, bool bAdd = true, float fDecrease = 0.0f, D3DXVECTOR3 *pPosOwner = nullptr, int nPriority = 6, bool bTurn = false);

private:
	// メンバ変数
	int m_nLife;	// 寿命
	float m_fDecreaseRadius;	// 半径減少量
	float m_fDecreaseAlpha;	// α値減少量
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_relPos;	// 相対位置
	D3DXVECTOR3 *m_pPosOwner;	// 持ち主のポインタ
	bool m_bAdd;	// 加算処理
	float m_fGravity;	// 重力
};

#endif