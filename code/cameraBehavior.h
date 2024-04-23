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
{
public:
	CCameraBehavior();
	virtual ~CCameraBehavior();

	virtual void Update(CCamera *pCamera) = 0;

private:
};

class CCameraBehaviorFollowPlayer : public CCameraBehavior
{
public:
	CCameraBehaviorFollowPlayer();
	~CCameraBehaviorFollowPlayer();

	void Update(CCamera *pCamera) override;
};

#endif