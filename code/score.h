//*****************************************************
//
// スコアの処理[score.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _SCORE_H_	// 二重インクルード防止
#define _SCORE_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CNumber;

//*****************************************************
// クラスの定義
//*****************************************************
class CScore : public CObject
{
public:
	CScore();	// コンストラクタ
	~CScore();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void) {}	// 描画
	void SetResultScore(void);	// 最終スコアの設定

	// 変数取得・設定関数
	int AddScore(int nValue);	// スコア
	int GetScore(void) { return m_nSocreDest; }

	// 静的メンバ関数
	static CScore *Create(void);	// 生成処理
	static CScore *GetInstance(void) { return s_pScore; }	// インスタンスの取得

private:
	// メンバ変数
	CNumber *m_pObjNumber;	// スコア値のポインタ
	int m_nScore;	// スコアの値
	int m_nSocreDest;	// 目標のスコア値
	int m_nIdxTexture;	// テクスチャ番号
	
	// 静的メンバ変数
	static CScore *s_pScore;	// 自身のポインタ
};

#endif
