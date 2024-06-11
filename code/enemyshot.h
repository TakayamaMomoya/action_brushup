//*****************************************************
//
// 撃ってくる敵の処理[enemyshot.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _ENEMYSHOT_H_	// 二重インクルード防止
#define _ENEMYSHOT_H_

//*****************************************************
// インクルード
//*****************************************************
#include "enemyNormal.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CEnemyShot : public CEnemyNormal
{// 撃ってくる敵
public:
	CEnemyShot();	// コンストラクタ
	~CEnemyShot();	// デストラクタ

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
