//*****************************************************
//
// όΝ[input.cpp]
// Author:ϋόRη
//
//*****************************************************

//*****************************************************
// CN[h
//*****************************************************
#include "input.h"

//*****************************************************
// ΓIoΟιΎ
//*****************************************************
LPDIRECTINPUT8 CInput::s_pInput = nullptr;	// DirectInputIuWFNgΦΜ|C^

//=====================================================
// RXgN^
//=====================================================
CInput::CInput() : m_pDevice(nullptr)
{

}

//=====================================================
// fXgN^
//=====================================================
CInput::~CInput()
{

}

//=====================================================
// ϊ»
//=====================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (s_pInput == nullptr)
	{
		// DirectInputIuWFNgΜΆ¬
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&s_pInput, nullptr)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//=====================================================
// IΉ
//=====================================================
void CInput::Uninit(void)
{
	if (m_pDevice != nullptr)
	{// όΝfoCXjό
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = nullptr;
	}

	if (s_pInput != nullptr)
	{// DirectInputIuWFNgΜjό
		s_pInput->Release();
		s_pInput = nullptr;
	}
}