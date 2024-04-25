//*****************************************************
//
// カメラのビヘイビア[cameraBehavior.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _CAMERABEHAVIOR_H_
#define _CAMERABEHAVIOR_H_

//****************************************************
// 前方宣言
//****************************************************
class CCamera;

//****************************************************
// クラスの定義
//****************************************************
class CCameraBehavior
{// 基底クラス
public:
	CCameraBehavior();
	virtual ~CCameraBehavior();

	virtual void Init(CCamera *pCamera) = 0;
	virtual void Update(CCamera *pCamera) = 0;

private:
};

class CCameraBehaviorFollowPlayer : public CCameraBehavior
{// プレイヤーの追従
public:
	CCameraBehaviorFollowPlayer();
	~CCameraBehaviorFollowPlayer();

	void Init(CCamera *pCamera) override;
	void Update(CCamera *pCamera) override;
};

class CCameraBehaviorApperPlayer : public CCameraBehavior
{// プレイヤーの登場
public:
	CCameraBehaviorApperPlayer();
	~CCameraBehaviorApperPlayer();

	void Init(CCamera *pCamera) override;
	void Update(CCamera *pCamera) override;
};

class CCameraBehaviorBossBattle : public CCameraBehavior
{// ボス戦での動き
public:
	CCameraBehaviorBossBattle();
	~CCameraBehaviorBossBattle();

	void Init(CCamera *pCamera) override;
	void Update(CCamera *pCamera) override;
};

#endif