//*****************************************************
//
// 敵の処理[enemy.cpp]
// Author:髙山桃也
//
//*****************************************************
#ifndef _ENEMY_H_	// 二重インクルード防止
#define _ENEMY_H_

//*****************************************************
// インクルード
//*****************************************************
#include "motion.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CCollisionSphere;
class CCollisionCube;
class CShadow;

//*****************************************************
// クラスの定義
//*****************************************************
class CEnemy : public CMotion
{
public:
	// 列挙型定義
	enum E_TYPE
	{// 敵の種類
		TYPE_NONE = 0,	// 何でもない
		TYPE_SHOT,	// 撃ってくる敵
		TYPE_DRONE,	// ドローン敵
		TYPE_BOSS,	// ボス敵
		TYPE_TURRET,	// タレット
		TYPE_MAX
	};

	enum E_STATE
	{// 状態
		STATE_NONE = 0,	// 何でもない状態
		STATE_NORMAL,	// 通常状態
		STATE_DAMAGE,	// ダメージ状態
		STATE_DEATH,	// 死亡状態
		STATE_MAX
	};

	CEnemy();	// コンストラクタ
	~CEnemy();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理
	void DeleteCollision(void);	// 当たり判定の削除
	void RotDest(void);	// 目標にモデルを向ける処理
	virtual void Death(void);	// 死亡時の処理
	void Hit(float fDamage);	// ヒット処理

	// 変数取得・設定関数
	void SetLife(float fLife);	// 体力
	float GetLife(void) { return m_fLife; }
	void SetSpherePosition(D3DXVECTOR3 pos);	// 当たり判定の位置
	CCollisionSphere *GetClsnSphere(void) { return m_pCollisionSphere; }	// 当たり判定
	E_STATE GetState(void) { return m_state; }	// 状態
	void SetState(E_STATE state) { m_state = state; }
	int GetScore(void) { return m_nScore; }	// スコア
	void SetScore(int nScore) { m_nScore = nScore; }
	float GetCntState(void) { return m_fTimerState; }	// 状態カウンター
	void SetCntState(float fCnt) { m_fTimerState = fCnt; }
	CEnemy *GetNext(void) { return m_pNext; }	// リストの次のポインタ

	// 静的メンバ関数
	static CEnemy *Create(D3DXVECTOR3 pos, E_TYPE type);	// 生成処理
	static int GetNumAll(void) { return s_nNumAll; }	// 総数取得

protected:
	// メンバ関数
	CShadow *GetShadow(void) { return m_pShadow; }	// 影取得
	void ManageScore(void);	// スコア管理

private:
	// メンバ関数
	void ManageState(void);

	// メンバ変数
	float m_fLife;	// 体力
	float m_fTimerState;	// 状態遷移カウンター
	CCollisionSphere *m_pCollisionSphere;	// 球の当たり判定
	CCollisionCube *m_pCollisionCube;	// 立方体の当たり判定
	CShadow *m_pShadow;	// 影のポインタ
	E_STATE m_state;	// 状態
	int m_nScore;	// スコア値
	CEnemy *m_pPrev;	// 前のアドレス
	CEnemy *m_pNext;	// 次のアドレス

	// 静的メンバ変数
	static int s_nNumAll;	// 総数
};

#endif
