//*****************************************************
//
// キーボード入力処理[inputkeyboard.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "inputkeyboard.h"
#include "debugproc.h"
#include "manager.h"

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CInputKeyboard *CInputKeyboard::s_pKeyboard = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CInputKeyboard::CInputKeyboard() : m_aKeyState{}, m_aKeyStateTrigger{}, m_aKeyStateRelease{}, m_aKeyStateRepeat{}, m_aCntRepeat{}
{

}

//=====================================================
// デストラクタ
//=====================================================
CInputKeyboard::~CInputKeyboard()
{

}

//=====================================================
// 生成処理
//=====================================================
CInputKeyboard *CInputKeyboard::Create(HINSTANCE hInstance, HWND hWnd)
{
	if (s_pKeyboard == nullptr)
	{
		s_pKeyboard = new CInputKeyboard;

		if (s_pKeyboard != nullptr)
		{
			s_pKeyboard->Init(hInstance, hWnd);
		}
	}

	return s_pKeyboard;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//入力デバイスの生成
	if (FAILED(s_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, nullptr)))
	{
		return E_FAIL;
	}

	//データフォーマットの生成
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードのアクセス権獲得
	m_pDevice->Acquire();

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CInputKeyboard::Uninit(void)
{
	s_pKeyboard = nullptr;

	// 基本クラスの終了処理
	CInput::Uninit();
}

//=====================================================
//キーボード更新処理
//=====================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			if (m_aKeyStateRepeat[nCntKey] & 0x80)
			{// リピートのカウンター
				m_aCntRepeat[nCntKey]++;
			}
			else if (m_aKeyState[nCntKey] == 0 && aKeyState[nCntKey] == 0)
			{
				m_aCntRepeat[nCntKey] = 0;
			}

			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & m_aKeyState[nCntKey];
			m_aKeyStateRepeat[nCntKey] = (m_aKeyState[nCntKey] & aKeyState[nCntKey]);
			m_aKeyState[nCntKey] = aKeyState[nCntKey];			//キーのプレス情報を保存
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//=====================================================
//プレス情報取得
//=====================================================
bool CInputKeyboard::GetPress(int nKey)
{
	//三項演算子
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}

//=====================================================
//トリガー情報取得
//=====================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=====================================================
//リリース情報取得
//=====================================================
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//=====================================================
//リピート情報取得
//=====================================================
int CInputKeyboard::GetRepeat(int nKey)
{
	return m_aCntRepeat[nKey];
}