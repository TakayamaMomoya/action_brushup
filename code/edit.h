//*****************************************************
//
// エディターの処理[edit.h]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "block.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CObjectX;

//*****************************************************
// クラスの定義
//*****************************************************
class CEdit : public CObject
{
public:
	CEdit();	// コンストラクタ
	~CEdit();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	// 静的メンバ関数
	static CEdit *Create(void);
	static CEdit *GetInstatnce(void) { return s_pEdit; }

private:
	// メンバ変数
	CObjectX *m_pObjectCursor;	// カーソルのオブジェクトXへのポインタ
	int m_nIdxObject;
	CBlock::TYPE m_type;

	// 静的メンバ変数
	static CEdit *s_pEdit;	// 自身のポインタ
};