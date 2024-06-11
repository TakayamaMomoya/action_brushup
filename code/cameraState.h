//*****************************************************
//
// カメラのステイト[cameraState.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _CAMERASTATE_H_	// 二重インクルード防止
#define _CAMERASTATE_H_

//****************************************************
// 前方宣言
//****************************************************
class CCamera;

//****************************************************
// クラスの定義
//****************************************************
class CCameraState
{// 基底クラス
public:
	CCameraState();	// コンストラクタ
	virtual ~CCameraState();	// デストラクタ

	virtual void Init(CCamera *pCamera) = 0;	// 初期化処理
	virtual void Update(CCamera *pCamera) = 0;	// 更新処理

private:
};

class CCameraStateTitle : public CCameraState
{// タイトル
public:
	CCameraStateTitle();	// コンストラクタ
	~CCameraStateTitle();	// デストラクタ

	void Init(CCamera *pCamera) override;	// 初期化処理
	void Update(CCamera *pCamera) override;	// 更新処理
};

class CCameraStateFollowPlayer : public CCameraState
{// プレイヤーの追従
public:
	CCameraStateFollowPlayer();	// コンストラクタ
	~CCameraStateFollowPlayer();	// デストラクタ

	void Init(CCamera *pCamera) override;	// 初期化処理
	void Update(CCamera *pCamera) override;	// 更新処理
};

class CCameraStateApperPlayer : public CCameraState
{// プレイヤーの登場
public:
	CCameraStateApperPlayer();	// コンストラクタ
	~CCameraStateApperPlayer();	// デストラクタ

	void Init(CCamera *pCamera) override;	// 初期化処理
	void Update(CCamera *pCamera) override;	// 更新処理
};

class CCameraStateApperBoss : public CCameraState
{// ボス出現
public:
	CCameraStateApperBoss();	// コンストラクタ
	~CCameraStateApperBoss();	// デストラクタ

	void Init(CCamera *pCamera) override;	// 初期化処理
	void Update(CCamera *pCamera) override;	// 更新処理
};

class CCameraStateBossBattle : public CCameraState
{// ボス戦での動き
public:
	CCameraStateBossBattle();	// コンストラクタ
	~CCameraStateBossBattle();	// デストラクタ

	void Init(CCamera *pCamera) override;	// 初期化処理
	void Update(CCamera *pCamera) override;	// 更新処理
};

#endif