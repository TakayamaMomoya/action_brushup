//*****************************************************
//
// Xファイルモデルの処理[model.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _MODEL_H_	// 二重インクルード防止
#define _MODEL_H_

//*****************************************************
// マクロ定義
//*****************************************************
#define NUM_MODEL	(256)	// モデルの数

//*****************************************************
// クラスの定義
//*****************************************************
class CModel
{
public:
	typedef struct
	{// モデルの構造体
		int *pIdxTexture;	// テクスチャ番号へのポインタ
		LPD3DXMESH pMesh;		//メッシュへのポインタ
		LPD3DXBUFFER pBuffMat;	//マテリアルへのバッファ
		DWORD dwNumMat;	//マテリアルの数
	}Model;

	CModel();	// コンストラクタ
	~CModel();	// デストラクタ
	
	// 静的メンバ関数
	static int Load(char *pPath);	// 読込
	static void Unload(void);	// 破棄
	static void Init(int nIdx);	// 初期化
	static Model *GetModel(int nIdx) { return m_apModel[nIdx]; }	// モデルの取得	
	static int GetNumAll(void) { return m_nNumAll; }// 総数取得

private:
	// 静的メンバ変数
	static Model *m_apModel[NUM_MODEL];	// モデルへのポインタ
	static char m_aPath[NUM_MODEL][256];	// モデルのファイル名
	static int m_nNumAll;	// 総数
};

#endif