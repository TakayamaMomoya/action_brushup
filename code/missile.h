//*****************************************************
//
// ミサイルの処理[missile.cpp]
// Author:髙山桃也
//
//*****************************************************
#ifndef _MISSILE_H_	// 二重インクルード防止
#define _MISSILE_H_

//*****************************************************
// インクルード
//*****************************************************
#include "objectX.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CCollisionSphere;
class COrbit;

//*****************************************************
// クラスの定義
//*****************************************************
class CMissile : public CObjectX
{// プレイヤーに向かう敵
public:
	CMissile();	// コンストラクタ
	~CMissile();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	void Hit(float fDamage) { Death(); }	// ヒット処理

	// 静的メンバ関数
	static CMissile *Create(D3DXVECTOR3 pos);

private:
	// メンバ関数
	void ChasePlayer(void);	// 追跡処理
	void Tilt(void);	// 傾く処理
	void Death(void);	// 死亡処理

	// メンバ変数
	float m_fDeathTimer;	// 死亡カウンター
	CCollisionSphere *m_pCollisionSphere;	// 球の当たり判定
	COrbit *m_pOrbit;	// 軌跡のポインタ
};

#endif
