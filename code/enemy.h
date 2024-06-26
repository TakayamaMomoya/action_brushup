//*****************************************************
//
// 敵の処理[enemy.cpp]
// Author:髙山桃也
//
//*****************************************************

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "motion.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CCollisionSphere;
class CCollisionCube;
class CShadow;

//*****************************************************
// マクロ定義
//*****************************************************
#define LOCKON_RANGE	(4000.0f)	// ロックオン距離
#define AIM_LOCKON_RANGE	(LOCKON_RANGE * 2.0f)	// エイム時のロックオン距離

//*****************************************************
// クラスの定義
//*****************************************************
class CEnemy : public CMotion
{
public:
	// 列挙型定義
	typedef enum
	{// 敵の種類
		TYPE_NONE = 0,	// 何でもない
		TYPE_SHOT,	// 撃ってくる敵
		TYPE_DRONE,	// ドローン敵
		TYPE_BOSS,	// ボス敵
		TYPE_TURRET,	// タレット
		TYPE_MAX
	}TYPE;

	typedef enum
	{// 状態
		STATE_NONE = 0,	// 何でもない状態
		STATE_NORMAL,	// 通常状態
		STATE_DAMAGE,	// ダメージ状態
		STATE_DEATH,	// 死亡状態
		STATE_MAX
	}STATE;

	CEnemy();	// コンストラクタ
	~CEnemy();	// デストラクタ

	static CEnemy *Create(D3DXVECTOR3 pos,TYPE type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static int GetNumAll(void) { return s_nNumAll; }
	void SetLife(float fLife);
	float GetLife(void) { return m_fLife; }
	void Hit(float fDamage);
	virtual void Death(void);
	void SetSpherePosition(D3DXVECTOR3 pos);
	STATE GetState(void) { return m_state; }
	void SetState(STATE state) { m_state = state; }
	CCollisionSphere *GetClsnSphere(void) { return m_pCollisionSphere; }
	CEnemy *GetNext(void) { return m_pNext; }
	int GetScore(void) { return m_nScore; }
	void SetScore(int nScore) { m_nScore = nScore; }
	float GetCntState(void) { return m_fTimerState; }
	void SetCntState(float fCnt) { m_fTimerState = fCnt; }
	void DeleteCollision(void);
	void RotDest(void);

protected:
	CShadow *GetShadow(void) { return m_pShadow; }
	void ManageScore(void);

private:
	void ManageState(void);

	// メンバ変数
	float m_fLife;	// 体力
	float m_fTimerState;	// 状態遷移カウンター
	CCollisionSphere *m_pCollisionSphere;	// 球の当たり判定
	CCollisionCube *m_pCollisionCube;	// 立方体の当たり判定
	CShadow *m_pShadow;	// 影のポインタ
	STATE m_state;	// 状態
	int m_nScore;	// スコア値
	CEnemy *m_pPrev;	// 前のアドレス
	CEnemy *m_pNext;	// 次のアドレス

	// 静的メンバ変数
	static int s_nNumAll;	// 総数
};

#endif
