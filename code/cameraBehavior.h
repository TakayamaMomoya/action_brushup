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

	virtual void Update(CCamera *pCamera) = 0;

private:
};

class CCameraBehaviorFollowPlayer : public CCameraBehavior
{// プレイヤーの追従
public:
	CCameraBehaviorFollowPlayer();
	~CCameraBehaviorFollowPlayer();

	void Update(CCamera *pCamera) override;
};

class CCameraBehaviorApperPlayer : public CCameraBehavior
{// プレイヤーの登場
public:
	CCameraBehaviorApperPlayer();
	~CCameraBehaviorApperPlayer();

	void Update(CCamera *pCamera) override;
};

#endif