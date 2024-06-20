//*****************************************************
//
// テクスチャの管理[texture.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "object.h"

namespace Texture
{
//*****************************************************
// 定数定義
//*****************************************************
const int MAX_TEX = 128;	// テクスチャの最大数

//*****************************************************
// ショートカット関数
//*****************************************************
int GetIdx(const char *pFileName);	// テクスチャ番号の取得
}

//*****************************************************
// クラスの定義
//*****************************************************
class CTexture
{
public:
	CTexture();	// コンストラクタ
	~CTexture();	// デストラクタ
	
	// メンバ関数
	HRESULT Load(void);
	void Unload(void);
	int Regist(const char *pFileName);
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);

	// 静的メンバ関数
	static CTexture *Create(void);
	static int GetNumAll(void) { return s_nNumAll; }
	static CTexture *GetInstance(void) { return s_pTexture; }

private:
	// メンバ変数
	LPDIRECT3DTEXTURE9 m_apTexture[Texture::MAX_TEX];	// テクスチャの配列
	char *m_apFilename[Texture::MAX_TEX];	// ファイル名の配列

	// 静的メンバ変数
	static int s_nNumAll;	// 総数
	static CTexture *s_pTexture;	// 自身のポインタ
};
#endif