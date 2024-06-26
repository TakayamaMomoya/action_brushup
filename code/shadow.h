//*****************************************************
//
// 影の処理[shadow.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _SHADOW_H_	// 二重インクルード防止
#define _SHADOW_H_

//*****************************************************
// インクルード
//*****************************************************
#include "polygon3D.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CShadow : public CPolygon3D
{
public:
	CShadow(int nPriority = 6);	// コンストラクタ
	~CShadow();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画

	// 静的メンバ関数
	static CShadow *Create(D3DXVECTOR3 pos,float width,float height);	// 生成処理

private:
};

#endif
