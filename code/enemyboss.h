//*****************************************************
//
// ボス敵の処理[enemyboss.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _ENEMYBOSS_H_	// 二重インクルード防止
#define _ENEMYBOSS_H_

//*****************************************************
// インクルード
//*****************************************************
#include "enemy.h"
#include "enemybossState.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CEnemyBoss : public CEnemy
{
public:
	// 列挙型定義
	enum IDXPARTS
	{// パーツの番号
		IDX_WAIST = 0,	// 腰
		IDX_BODY,	// 胴
		IDX_HEAD,	// 頭
		IDX_SHOULDER_L,	// 左肩
		IDX_ARM_L,	// 左腕
		IDX_HAND_L,	// 左手
		IDX_SHOULDER_R,	// 右肩
		IDX_ARM_R,	// 右手
		IDX_HAND_R,	// 右手
		IDX_LEG_L,	// 左腿
		IDX_FOOT_L,	// 左脛
		IDX_TOE_L,	// 左足先
		IDX_LEG_R,	// 右腿
		IDX_FOOT_R,	// 右脛
		IDX_TOE_R,	// 右足先
		IDX_WEAPON,	// 武器
		IDX_MAX
	};
	enum MOTION
	{// モーション
		MOTION_APPER = 0,	// 出現モーション
		MOTION_MISSILE,	// ミサイルモーション
		MOTION_DASH,	// 突進モーション
		MOTION_SHOT_UNDER,	// 射撃モーション
		MOTION_SHOT_UPPER,	// 反転射撃モーション
		MOTION_DEATH,	// 死亡モーション
		MOTION_MAX
	};

	CEnemyBoss();	// コンストラクタ
	~CEnemyBoss();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理
	void Hit(float fDamage);	// ヒット処理
	bool FollowDest(void);	// 目標に向かう処理
	void SwitchState(void);	// 状態の変更
	void FollowCollision(void);	// 当たり判定の追従
	void Death(void) override;	// 死亡時の処理

	// 変数取得・設定関数
	void SetPosDest(D3DXVECTOR3 posDest) { m_info.posDest = posDest; }	// 目標位置
	D3DXVECTOR3 GetPosDest(void) { return m_info.posDest; }

	// 静的メンバ関数
	static CEnemyBoss *Create(void);	// 生成処理
	static CEnemyBoss *GetInstance(void) { return s_pEnemyBoss; }	// インスタンスの取得

private:
	// 列挙型定義
	enum STATE
	{// 状態
		STATE_NONE = 0,	// 何もしていない状態
		STATE_APPER,	// 出現状態
		STATE_BATTLE,	// 戦闘状態
		STATE_MAX
	};
	enum ATTACKSTATE
	{// 攻撃状態
		ATTACK_MISSILE = 0,	// ミサイル攻撃
		ATTACK_DASH,	// 突進攻撃
		ATTACK_SHOT,	// 射撃攻撃
		ATTACK_MAX
	};

	// 構造体定義
	struct S_Info
	{// 自身の情報
		STATE state;	// 状態
		ATTACKSTATE attackState;	// 攻撃状態
		D3DXVECTOR3 posDest;	// 目標位置
		float fTimerState;	// 状態遷移タイマー
		// コンストラクタ
		S_Info() : state(CEnemyBoss::STATE::STATE_NONE), attackState(ATTACKSTATE::ATTACK_MISSILE),
			posDest{}, fTimerState(0.0f) {}
	};
	
	// メンバ関数
	void ManageState(void);	// 状態の管理
	void ManageCollision(void);	// 当たり判定管理
	void ChangeState(CEnemyBossState *pState);	// ステイトの切り替え

	// メンバ変数
	S_Info m_info;	// 自身の情報
	CEnemyBossState *m_pState;	// ステイトのポインタ

	// 静的メンバ変数
	static CEnemyBoss *s_pEnemyBoss;	// 自身のポインタ
};

#endif
