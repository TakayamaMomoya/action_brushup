//*****************************************************
//
// 敵マネージャー[enemyManager.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _ENEMYMANAGER_H_	// 二重インクルード防止
#define _ENEMYMANAGER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"
#include "enemy.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CEnemyManager : public CObject
{
public:
	CEnemyManager();	// コンストラクタ
	~CEnemyManager();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理
	CEnemy *CreateEnemy(D3DXVECTOR3 pos, CEnemy::TYPE type);	// 敵の生成

	// 変数取得・設定関数
	CEnemy *GetHead(void) { return m_pHead; }	// リストの先頭
	void SetHead(CEnemy *pEnemy) { m_pHead = pEnemy; }
	CEnemy *GetTail(void) { return m_pTail; }	// リストの最後尾
	void SetTail(CEnemy *pEnemy) { m_pTail = pEnemy; }

	// 静的メンバ関数
	static CEnemyManager *Create(void);	// 生成処理
	static CEnemyManager *GetInstance(void) { return s_pEnemyManager; }	// インスタンスの取得

private:
	// メンバ関数
	void Load(void);	// 配置の読込

	// メンバ変数
	CEnemy *m_pHead;	// 先頭のアドレス
	CEnemy *m_pTail;	// 最後尾のアドレス
	
	// 静的メンバ変数
	static CEnemyManager *s_pEnemyManager;	// 自身のポインタ
};

#endif
