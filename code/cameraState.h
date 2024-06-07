//*****************************************************
//
// カメラのステイト[cameraState.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _CAMERASTATE_H_
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
	CCameraState();
	virtual ~CCameraState();

	virtual void Init(CCamera *pCamera) = 0;
	virtual void Update(CCamera *pCamera) = 0;

private:
};

class CCameraStateFollowPlayer : public CCameraState
{// プレイヤーの追従
public:
	CCameraStateFollowPlayer();
	~CCameraStateFollowPlayer();

	void Init(CCamera *pCamera) override;
	void Update(CCamera *pCamera) override;
};

class CCameraStateApperPlayer : public CCameraState
{// プレイヤーの登場
public:
	CCameraStateApperPlayer();
	~CCameraStateApperPlayer();

	void Init(CCamera *pCamera) override;
	void Update(CCamera *pCamera) override;
};

class CCameraStateBossBattle : public CCameraState
{// ボス戦での動き
public:
	CCameraStateBossBattle();
	~CCameraStateBossBattle();

	void Init(CCamera *pCamera) override;
	void Update(CCamera *pCamera) override;
};

#endif