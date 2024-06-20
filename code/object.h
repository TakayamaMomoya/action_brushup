//*****************************************************
//
// オブジェクトの処理[object.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _OBJECT_H_	// 二重インクルード防止
#define _OBJECT_H_

//*****************************************************
// 前方宣言
//*****************************************************
class CPlayer;
class CBlock;

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const int NUM_OBJECT = 4096;	// オブジェクトの数
const int NUM_PRIORITY = 8;	// 優先順位の数
}

//*****************************************************
// クラスの定義
//*****************************************************
class CObject
{
public:
	// 列挙型定義
	enum E_TYPE
	{
		TYPE_NONE = 0,	// 何でもない
		TYPE_PLAYER,	// プレイヤー
		TYPE_ENEMY,	// 敵
		TYPE_BLOCK,	// ブロック
		TYPE_BULLET,	// 弾
		TYPE_PARTICLE,	// パーティクル
		TYPE_MAX
	};

	CObject(int nPriority = 3);	// コンストラクタ
	virtual ~CObject();	//	デストラクタ

	// メンバ関数
	virtual HRESULT Init(void) = 0;	// 初期化処理
	virtual void Uninit(void) = 0;	// 終了処理
	virtual void Update(void) = 0;	// 更新処理
	virtual void Draw(void) {};	// 描画処理
	virtual void Hit(float fDamage){}	// ヒット処理
	
	// 変数取得・設定関数
	void SetType(E_TYPE type);	// 種類
	E_TYPE GetType(void) { return m_type; }
	virtual void SetPosition(D3DXVECTOR3 pos) {};	// 位置
	virtual D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(); }
	virtual void SetPositionOld(D3DXVECTOR3 pos) {};	// 前回の位置
	virtual D3DXVECTOR3 GetPositionOld(void) { return D3DXVECTOR3(); };
	void EnableWire(bool bWire) { m_bWire = bWire; }	// ワイヤーフレーム
	bool IsDeath(void) { return m_bDeath; }	// 死亡フラグ
	void EnableZtest(bool bZtest) { m_bZtest = bZtest; }	// Zテストフラグ
	void EnableLighting(bool bLighting) { m_bLighting = bLighting; }	// ライティングフラグ
	void EnableAdd(bool bAdd) { m_bAdd = bAdd; }	// 加算合成フラグ
	void EnableFog(bool bFog) { m_bFog = bFog; }	// フォグフラグ
	void EnableCull(bool bCull) { m_bCull = bCull; }	// カリングフラグ
	void SetAlphaTest(DWORD dValue) { m_dwAlpha = dValue; }	// アルファテストしきい値
	DWORD GetAlpha(void) { return m_dwAlpha; }

	// 静的メンバ関数
	static void ReleaseAll(void);	// 全てリリース
	static void UpdateAll(void);	// 全て更新
	static void DeleteAll(void);	// 全削除処理
	static void DrawAll(void);	// 全て描画
	static int GetNumAll(void) { return s_nNumAll; }	// 総数取得

protected:
	// メンバ関数
	void Release(void);	// 個別リリース処理

private:
	// メンバ関数
	void Delete(void);	// 個別削除処理

	// メンバ変数
	int m_nID;	// 自分のID
	E_TYPE m_type;	// 種類
	int m_nPriority;	// 描画の優先順位
	CObject *m_pPrev;	// 前のオブジェクトのアドレス
	CObject *m_pNext;	// 次のオブジェクトのアドレス
	bool m_bDeath;	// 死亡フラグ
	bool m_bWire;	// ワイヤーフレームで表示するかどうか
	bool m_bZtest;	// Zテストで前に出すかどうか
	bool m_bLighting;	// ライティングを有効化するかどうか
	bool m_bAdd;	// 加算合成するかどうか
	bool m_bFog;	// フォグをかけるかどうか
	bool m_bCull;	// カリングするかどうか
	DWORD m_dwAlpha;	// アルファテストの値

	// 静的メンバ変数
	static int s_nNumAll;	// 総数
	static CObject *s_apTop[NUM_PRIORITY];	// 先頭のオブジェクトのアドレス
	static CObject *s_apCur[NUM_PRIORITY];	// 最後尾のオブジェクトのアドレス
};

namespace Object
{
//*****************************************************
// ショートカット関数
//*****************************************************
void DeleteObject(CObject **ppObject, int nSize = 1);	// オブジェクトの破棄
}

#endif