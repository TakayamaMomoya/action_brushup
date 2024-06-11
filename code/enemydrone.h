//*****************************************************
//
// ドローン敵の処理[enemydrone.cpp]
// Author:髙山桃也
//
//*****************************************************

#ifndef _ENEMYDRONE_H_
#define _ENEMYDRONE_H_

#include "enemyNormal.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CEnemyDrone : public CEnemyNormal
{
public:
	CEnemyDrone();	// コンストラクタ
	~CEnemyDrone();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理

private:
	// 列挙型定義
	enum MOTION
	{// モーション
		MOTION_NEUTRAL = 0,	// 待機モーション
		MOTION_SHOT,	// 射撃モーション
		MOTION_MAX
	};

	// メンバ関数
	void ManageAttack(void);	// 攻撃の管理
};

#endif
