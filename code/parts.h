//*****************************************************
//
// パーツの処理[parts.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _PARTS_H_	// 二重インクルード防止
#define _PARTS_H_

//*****************************************************
// インクルード
//*****************************************************s
#include "objectX.h"

//*****************************************************
// クラス定義
//*****************************************************
class CParts : public CObjectX
{
public:
	CParts();	// コンストラクタ
	~CParts();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画

	// 変数取得・設定関数
	D3DXVECTOR3 GetPosOrg(void) { return m_posOrg; }	// 初期の位置
	void SetPosOrg(D3DXVECTOR3 pos) { m_posOrg = pos; }

	// 静的メンバ関数
	static CParts *Create(void);	// 生成処理

private:
	// メンバ変数
	D3DXVECTOR3 m_posOrg;
};

#endif