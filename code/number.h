//*****************************************************
//
// 数字の処理[number.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _NUMBER_H_	// 二重インクルード防止
#define _NUMBER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CUI;

//*****************************************************
// マクロ定義
//*****************************************************
#define MAX_PLACE	(10)	// 最大桁数

class CNumber : public CObject
{
public:
	CNumber(int nPriority = 5);	// コンストラクタ
	~CNumber();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void) {}	// 描画
	void SetValue(int nValue, int nNumPlace);	// 表示する値の設定

	// 変数取得・設定関数
	void SetPosition(D3DXVECTOR3 pos);	// 位置
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetPositionOld(void) { return D3DXVECTOR3(); }	// 前回の位置
	void SetSizeAll(float width,float height);	// 数字のサイズ
	void SetColor(D3DXCOLOR col);	// 色設定

	// 静的メンバ関数
	static CNumber *Create(int nNumPlace, int nValue);

private:
	// メンバ変数
	CUI *m_apObject[MAX_PLACE];	// ２Ⅾオブジェクトのポインタ
	D3DXVECTOR3 m_pos;	// 位置
	int m_nNumPlace;	// 桁数
	int m_nValue;	// 値
	int m_nNumAll;	// 総数
	int m_nIdxTexture;	// テクスチャ番号
};

#endif