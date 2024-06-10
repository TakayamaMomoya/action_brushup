//*****************************************************
//
// ボスのステイトの処理[enemybossState.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _ENEMYBOSSSTATE_H_
#define _ENEMYBOSSSTATE_H_

//*****************************************************
// 前方宣言
//*****************************************************
class CEnemyBoss;

//*****************************************************
// クラスの定義
//*****************************************************
class CEnemyBossState
{
public:
	CEnemyBossState() {}	// コンストラクタ
	~CEnemyBossState() {}	// デストラクタ

	// メンバ関数
	virtual void Init(CEnemyBoss *pBoss) = 0;	// 初期化処理
	virtual void Update(CEnemyBoss *pBoss) = 0;	// 更新処理

private:
};

class CEnemyBossStateApper : public CEnemyBossState
{// 出現状態
public:
	CEnemyBossStateApper();	// コンストラクタ
	~CEnemyBossStateApper();	// デストラクタ

	// メンバ関数
	void Init(CEnemyBoss *pBoss) override;	// 初期化処理
	void Update(CEnemyBoss *pBoss) override;	// 更新処理

private:
};

class CEnemyBossStateMissile : public CEnemyBossState
{// ミサイル攻撃
public:
	CEnemyBossStateMissile();	// コンストラクタ
	~CEnemyBossStateMissile();	// デストラクタ

	// メンバ関数
	void Init(CEnemyBoss *pBoss) override;	// 初期化処理
	void Update(CEnemyBoss *pBoss) override;	// 更新処理

private:
	// メンバ変数
	float m_fTimerAttack;	// 攻撃タイマー
	int m_nCntAttack;	// 攻撃カウンター
};

class CEnemyBossStateDash : public CEnemyBossState
{// 突進攻撃
public:
	CEnemyBossStateDash();	// コンストラクタ
	~CEnemyBossStateDash();	// デストラクタ

	// メンバ関数
	void Init(CEnemyBoss *pBoss) override;	// 初期化処理
	void Update(CEnemyBoss *pBoss) override;	// 更新処理

private:
};

class CEnemyBossStateShot : public CEnemyBossState
{// 射撃攻撃
public:
	CEnemyBossStateShot();	// コンストラクタ
	~CEnemyBossStateShot();	// デストラクタ

	// メンバ関数
	void Init(CEnemyBoss *pBoss) override;	// 初期化処理
	void Update(CEnemyBoss *pBoss) override;	// 更新処理

private:
	// メンバ変数
	float m_fTimerAttack;	// 攻撃タイマー
};

#endif
