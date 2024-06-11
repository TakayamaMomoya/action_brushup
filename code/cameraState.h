//*****************************************************
//
// �J�����̃X�e�C�g[cameraState.h]
// Author:���R����
//
//*****************************************************
#ifndef _CAMERASTATE_H_	// ��d�C���N���[�h�h�~
#define _CAMERASTATE_H_

//****************************************************
// �O���錾
//****************************************************
class CCamera;

//****************************************************
// �N���X�̒�`
//****************************************************
class CCameraState
{// ���N���X
public:
	CCameraState();	// �R���X�g���N�^
	virtual ~CCameraState();	// �f�X�g���N�^

	virtual void Init(CCamera *pCamera) = 0;	// ����������
	virtual void Update(CCamera *pCamera) = 0;	// �X�V����

private:
};

class CCameraStateTitle : public CCameraState
{// �^�C�g��
public:
	CCameraStateTitle();	// �R���X�g���N�^
	~CCameraStateTitle();	// �f�X�g���N�^

	void Init(CCamera *pCamera) override;	// ����������
	void Update(CCamera *pCamera) override;	// �X�V����
};

class CCameraStateFollowPlayer : public CCameraState
{// �v���C���[�̒Ǐ]
public:
	CCameraStateFollowPlayer();	// �R���X�g���N�^
	~CCameraStateFollowPlayer();	// �f�X�g���N�^

	void Init(CCamera *pCamera) override;	// ����������
	void Update(CCamera *pCamera) override;	// �X�V����
};

class CCameraStateApperPlayer : public CCameraState
{// �v���C���[�̓o��
public:
	CCameraStateApperPlayer();	// �R���X�g���N�^
	~CCameraStateApperPlayer();	// �f�X�g���N�^

	void Init(CCamera *pCamera) override;	// ����������
	void Update(CCamera *pCamera) override;	// �X�V����
};

class CCameraStateApperBoss : public CCameraState
{// �{�X�o��
public:
	CCameraStateApperBoss();	// �R���X�g���N�^
	~CCameraStateApperBoss();	// �f�X�g���N�^

	void Init(CCamera *pCamera) override;	// ����������
	void Update(CCamera *pCamera) override;	// �X�V����
};

class CCameraStateBossBattle : public CCameraState
{// �{�X��ł̓���
public:
	CCameraStateBossBattle();	// �R���X�g���N�^
	~CCameraStateBossBattle();	// �f�X�g���N�^

	void Init(CCamera *pCamera) override;	// ����������
	void Update(CCamera *pCamera) override;	// �X�V����
};

#endif