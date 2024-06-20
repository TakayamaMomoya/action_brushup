//*****************************************************
//
// 通常敵の処理[enemyNormal.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _ENEMYNORMAL_H_	// 二重インクルード防止
#define _ENEMYNORMAL_H_

//*****************************************************
// インクルード
//*****************************************************
#include "enemy.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CEnemyNormal : public CEnemy
{
public:
	CEnemyNormal();	// コンストラクタ
	~CEnemyNormal();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理
	void Death(void);	// 死亡処理

	// 変数取得・設定関数
	float GetLife(void) { return m_fLife; }	// 体力
	void SetLife(float fLife) { m_fLife = fLife; }
	int GetScore(void) { return m_nScore; }	// 倒したときに得られるスコア
	void SetScore(int nScore) { m_nScore = nScore; }
	float GetAttackCounter(void) { return m_fCntAttack; }	// 攻撃カウンター
	void SetAttackCounter(float fCounter) { m_fCntAttack = fCounter; }
	void SetSpherePosition(D3DXVECTOR3 pos);	// 球判定の位置
	CCollisionSphere *GetClsnSphere(void) { return m_pCollisionSphere; }	// 球判定の取得
	CEnemyNormal *GetNext(void) { return m_pNext; }	// リストの次のポインタ

	// 静的メンバ関数
	static int GetNumAll(void) { return s_nNumAll; }	// 総数取得

private:
	// メンバ関数
	void ManageState(void);	// 状態の管理
	void ManageCollision(void);	// 当たり判定の管理

	// メンバ変数
	float m_fLife;	// 体力
	int m_nTimerState;	// 状態遷移カウンター
	CCollisionSphere *m_pCollisionSphere;	// 球の当たり判定
	CCollisionCube *m_pCollisionCube;	// 立方体の当たり判定
	int m_nScore;	// スコア値
	float m_fCntAttack;	// 攻撃カウンタ
	CEnemyNormal *m_pPrev;	// 前のアドレス
	CEnemyNormal *m_pNext;	// 次のアドレス

	// 静的メンバ変数
	static int s_nNumAll;	// 総数
};

#endif
