//*****************************************************
//
// 入力処理[input.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _INPUT_H_	// 二重インクルード防止
#define _INPUT_H_

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "Xinput.h"

//*****************************************************
// ライブラリ
//*****************************************************
#pragma comment(lib,"xinput.lib")

//*****************************************************
// クラスの定義
//*****************************************************
class CInput
{
public:
	CInput();	// コンストラクタ
	virtual ~CInput();	// デストラクタ

	// メンバ関数
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	// メンバ変数
	LPDIRECTINPUTDEVICE8 m_pDevice;	// 各デバイスへのポインタ

	// 静的メンバ変数
	static LPDIRECTINPUT8 s_pInput;	// DirectInputオブジェクトへのポインタ
};

#endif