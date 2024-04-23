//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : ���R����
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSound
{
public:
	typedef enum
	{
		LABEL_BGM000 = 0,				// �^�C�g��BGM
		LABEL_BGM_BATTLE,				// �퓬BGM 
		LABEL_BGM_BOSS,				// �{�XBGM 
		LABEL_SE_ATTACK,				// �ʏ�U�� 
		LABEL_SE_AIRATTACK,				// ��i�W�����v�U�� 
		LABEL_SE_LASER,				// ���[�U�[
		LABEL_SE_BULLET,				// ���e�ˌ�
		LABEL_SE_HIT_NORMAL,				// �ʏ�q�b�g
		LABEL_SE_HIT_BOSS,				// �{�X�q�b�g
		LABEL_SE_JUMP,				// �W�����v
		LABEL_SE_DASH,				// �_�b�V��
		LABEL_SE_LAND,				// ���n
		LABEL_SE_PARRY,				// �p���B
		LABEL_SE_EXPLOSION,				// ����
		LABEL_SE_MISSILE,				// �~�T�C��
		LABEL_SE_ENTER,				// �G���^�[
		LABEL_SE_DAMAGE,				// �_���[�W
		LABEL_MAX
	} LABEL;

	typedef enum
	{
		FADESTATE_NONE = 0,	//�������Ă��Ȃ����
		FADESTATE_IN,	//�t�F�[�h�C�����
		FADESTATE_OUT,	//�t�F�[�h�A�E�g���
		FADESTATE_MAX
	}FADESTATE;

	CSound();	// �R���X�g���N�^
	~CSound();	// �f�X�g���N�^

	static CSound *Create(HWND hWnd);
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	void Update(void);

	HRESULT Play(LABEL label);
	void Stop(LABEL label);
	void Stop(void);

	void SetVolume(LABEL label, float fVolume);
	void SetFade(LABEL LabelNow, LABEL LabelNext, float fSpeed);

	static CSound *GetInstance(void) { return m_pSound; }

private:
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDINFO;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[LABEL_MAX];	// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[LABEL_MAX];	// �I�[�f�B�I�f�[�^�T�C�Y
	FADESTATE m_fadeSound;	// �t�F�[�h���
	LABEL m_SoundLabelNow;	// ���݂̃T�E���h���x��
	LABEL m_SoundLabelNext;	// ���̃T�E���h���x��
	float m_fSpeedFadeSound;	// �T�E���h���t�F�[�h����X�s�[�h
	float m_fVolumeSound;	// �T�E���h�̃{�����[��

	// �T�E���h�̏��
	SOUNDINFO m_aSoundInfo[LABEL_MAX] =
	{
		{ "data/SOUND/BGM/Control_Station.wav", -1 },			// �^�C�g��	
		{ "data/SOUND/BGM/GENIX.wav", -1 },			// �퓬BGM
		{ "data/SOUND/BGM/Virus_Entry.wav", -1 },			// �{�XBGM
		{ "data/SOUND/SE/attack00.wav", 0 },		// �ʏ�U�� 
		{ "data/SOUND/SE/attack01.wav", 0 },			// ��i�W�����v�U��
		{ "data/SOUND/SE/shot00.wav", 0 },			// ���[�U�[
		{ "data/SOUND/SE/shot01.wav", 0 },			// ���e�ˌ�
		{ "data/SOUND/SE/hit00.wav", 0 },			// �ʏ�q�b�g
		{ "data/SOUND/SE/hit01.wav", 0 },			// �{�X�q�b�g
		{ "data/SOUND/SE/jump.wav", 0 },			// �W�����v
		{ "data/SOUND/SE/dash.wav", 0 },			// �_�b�V��
		{ "data/SOUND/SE/land.wav", 0 },			// ���n
		{ "data/SOUND/SE/parry.wav", 0 },			// �p���B
		{ "data/SOUND/SE/explosion.wav", 0 },			// ����
		{ "data/SOUND/SE/missile.wav", 0 },			// �~�T�C��
		{ "data/SOUND/SE/enter.wav", 0 },			// �G���^�[
		{ "data/SOUND/SE/damage.wav", 0 },			// �_���[�W
	};

	static CSound *m_pSound;	// ���g�̃|�C���^
};

#endif