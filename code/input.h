//*****************************************************
//
// όΝ[input.h]
// Author:ϋόRη
//
//*****************************************************
#ifndef _INPUT_H_	// ρdCN[hh~
#define _INPUT_H_

//*****************************************************
// CN[h
//*****************************************************
#include "main.h"
#include "Xinput.h"

//*****************************************************
// Cu
//*****************************************************
#pragma comment(lib,"xinput.lib")

//*****************************************************
// NXΜθ`
//*****************************************************
class CInput
{
public:
	CInput();	// RXgN^
	virtual ~CInput();	// fXgN^

	// oΦ
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	// oΟ
	LPDIRECTINPUTDEVICE8 m_pDevice;	// efoCXΦΜ|C^

	// ΓIoΟ
	static LPDIRECTINPUT8 s_pInput;	// DirectInputIuWFNgΦΜ|C^
};

#endif