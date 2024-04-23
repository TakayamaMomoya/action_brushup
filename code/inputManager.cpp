//*****************************************************
//
// ���̓}�l�[�W���[[inputManager.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "inputManager.h"
#include "manager.h"
#include "inputjoypad.h"
#include "inputkeyboard.h"
#include "inputmouse.h"

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CInputManager *CInputManager::m_pInputManager = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CInputManager::CInputManager()
{
	ZeroMemory(&m_info, sizeof(SInfo));
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CInputManager::~CInputManager()
{

}

//=====================================================
// ��������
//=====================================================
CInputManager *CInputManager::Create(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInputManager == nullptr)
	{// �C���X�^���X����
		m_pInputManager = new CInputManager;

		// ����������
		m_pInputManager->Init(hInstance, hWnd);
	}

	return m_pInputManager;
}

//=====================================================
// ����������
//=====================================================
HRESULT CInputManager::Init(HINSTANCE hInstance, HWND hWnd)
{
	// �W���C�p�b�h����
	CInputJoypad::Create();

	// �L�[�{�[�h����
	CInputKeyboard::Create(hInstance, hWnd);

	// �}�E�X����
	CInputMouse::Create(hInstance, hWnd);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CInputManager::Uninit(void)
{
	CInputJoypad *pJoypad = CInputJoypad::GetInstance();
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse *pMouse = CInputMouse::GetInstance();

	if (pJoypad != nullptr)
	{
		pJoypad->Uninit();
	}

	if (pKeyboard != nullptr)
	{
		pKeyboard->Uninit();
	}

	if (pMouse != nullptr)
	{
		pMouse->Uninit();
	}

	// ���g�̃|�C���^�j��
	m_pInputManager = nullptr;
	delete this;
}

//=====================================================
// �X�V����
//=====================================================
void CInputManager::Update(void)
{
	// �e���̓f�o�C�X�̍X�V
	CInputJoypad *pJoypad = CInputJoypad::GetInstance();
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse *pMouse = CInputMouse::GetInstance();

	if (pJoypad != nullptr)
	{
		pJoypad->Update();
	}

	if (pKeyboard != nullptr)
	{
		pKeyboard->Update();
	}

	if (pMouse != nullptr)
	{
		pMouse->Update();
	}

	// �G���^�[
	m_info.abTrigger[BUTTON_ENTER] =
	(
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_A, 0) ||
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_START, 0) ||
		pMouse->GetTrigger(CInputMouse::BUTTON_LMB) ||
		pKeyboard->GetTrigger(DIK_RETURN)
	);

	// �߂�{�^��
	m_info.abTrigger[BUTTON_BACK] =
	(
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_B, 0) ||
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_BACK, 0) ||
		pMouse->GetTrigger(CInputMouse::BUTTON_RMB)
	);

	// �W�����v
	m_info.abTrigger[BUTTON_JUMP] =
	(
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_A, 0) ||
		pKeyboard->GetTrigger(DIK_SPACE)
	);

	// �E�ړ�
	m_info.abPress[BUTTON_MOVE_RIGHT] = pKeyboard->GetPress(DIK_D) || pJoypad->GetJoyStickLX(0) > 0;

	// ���ړ�
	m_info.abPress[BUTTON_MOVE_LEFT] = pKeyboard->GetPress(DIK_A) || pJoypad->GetJoyStickLX(0) < 0;

	// �U��
	m_info.abTrigger[BUTTON_ATTACK] = 
	(
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_RB, 0) ||
		pMouse->GetTrigger(CInputMouse::BUTTON_LMB) ||
		pKeyboard->GetTrigger(DIK_RETURN)
	);

	// �p���B
	m_info.abTrigger[BUTTON_PARRY] = 
	(
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_LB, 0) ||
		pMouse->GetTrigger(CInputMouse::BUTTON_RMB) ||
		pKeyboard->GetTrigger(DIK_BACKSPACE)
	);

	// �_�b�V��
	m_info.abTrigger[BUTTON_DASH] =
	(
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_B, 0) ||
		pKeyboard->GetTrigger(DIK_LSHIFT)
	);

	// �|�[�Y
	m_info.abTrigger[BUTTON_PAUSE] =
	(
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_START, 0) ||
		pKeyboard->GetTrigger(DIK_P)
	);

	// ������L�[
	m_info.abTrigger[BUTTON_AXIS_UP] =
	(
		pJoypad->GetLStickTrigger(CInputJoypad::DIRECTION_UP,0) || 
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_UP,0) ||
		pKeyboard->GetTrigger(DIK_W)
	);

	// �������L�[
	m_info.abTrigger[BUTTON_AXIS_DOWN] =
	(
		pJoypad->GetLStickTrigger(CInputJoypad::DIRECTION_DOWN, 0) ||
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_DOWN, 0) ||
		pKeyboard->GetTrigger(DIK_S)
	);
}