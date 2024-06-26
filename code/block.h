//*****************************************************
//
// ブロックの処理[block.cpp]
// Author:髙山桃也
//
//*****************************************************

#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "ObjectX.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CCollisionCube;

//*****************************************************
// クラスの定義
//*****************************************************
class CBlock : public CObjectX
{
public:
	// 列挙型定義
	enum E_TYPE
	{// 種類
		TYPE_FLOOR,	// 床
		TYPE_CHAIR,	// 椅子
		TYPE_DESK,	// 机
		TYPE_DOCUMENT,	// 書類
		TYPE_FUN,	// 換気扇
		TYPE_LOCKER,	// ロッカー
		TYPE_WINDOW,	// 窓
		TYPE_FLOORBIG,	// でか床
		TYPE_WINDOWBIG,	// でか窓
		TYPE_CASE00,	// 窓ふき１
		TYPE_CASE01,	// 窓ふき柵
		TYPE_CASE02,	// 窓ふき柵
		TYPE_FLOOR4,	// 床×４
		TYPE_ROOFTOPBIG,	// 屋上床
		TYPE_ROOFTOP4,	// 屋上床×４
		TYPE_ROOFTOP1,	// 屋上床×１
		TYPE_HELIPORT,	// ヘリポート
		TYPE_FRONTWINDOW,	// 手前の窓
		TYPE_SIDEWINDOW,	// 横の窓
		TYPE_WALL,	// 壁
		TYPE_WALL2,	// 壁2
		TYPE_WALL3,	// 壁3
		TYPE_SIDEWINDOWBIG,	// でか横窓
		TYPE_FRONTWINDOW4,	// 手前窓4
		TYPE_LONGDESK,	// 長机
		TYPE_MAX
	};

	// 構造体定義
	struct MemBlock
	{// 保存するときの情報
		D3DXVECTOR3 pos;	// 位置
		D3DXVECTOR3 rot;	// 向き
		E_TYPE type;	// 種類
	};

	CBlock(int nPriority = 3);	// コンストラクタ
	~CBlock();	// デストラクタ

	// メンバ関数
	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);  // 描画

	// 静的メンバ関数
	static CBlock *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, E_TYPE type);	// 生成処理
	static HRESULT Load(char *pPath);	// 読込
	static void Save(void);	// 保存
	static void Delete(int nIdx);	// 部分削除処理
	static void DeleteAll(void);	// 全削除処理
	static int GetNumAll(void) { return s_nNumAll; }	// 総数取得
	static CBlock **GetBlock(void) { return &s_apBlock[0]; }	// ブロック取得
	static float CheckShadow(D3DXVECTOR3 pos);	// 影のチェック
	static void LoadModel(void);	// モデル読込
	static void DeleteIdx(void);	// 番号の削除
	static int *GetIndex(void) { return s_pIdxObject; }	// 番号の取得

private:
	// メンバ変数
	E_TYPE m_type;	// 種類
	CCollisionCube *m_pCollisionCube;	// 立方体の当たり判定
	int m_nLife;	// 体力

	// 静的メンバ変数
	static int *s_pIdxObject;	// モデルのタイプ番号のポインタ
	static CBlock *s_apBlock[NUM_OBJECT];	// ブロックの配列
	static int s_nNumAll;	// 総数
};

#endif
