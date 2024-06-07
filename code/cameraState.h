//*****************************************************
//
// �J�����̃X�e�C�g[cameraState.h]
// Author:���R����
//
//*****************************************************

#ifndef _CAMERASTATE_H_
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
	CCameraState();
	virtual ~CCameraState();

	virtual void Init(CCamera *pCamera) = 0;
	virtual void Update(CCamera *pCamera) = 0;

private:
};

class CCameraStateFollowPlayer : public CCameraState
{// �v���C���[�̒Ǐ]
public:
	CCameraStateFollowPlayer();
	~CCameraStateFollowPlayer();

	void Init(CCamera *pCamera) override;
	void Update(CCamera *pCamera) override;
};

class CCameraStateApperPlayer : public CCameraState
{// �v���C���[�̓o��
public:
	CCameraStateApperPlayer();
	~CCameraStateApperPlayer();

	void Init(CCamera *pCamera) override;
	void Update(CCamera *pCamera) override;
};

class CCameraStateBossBattle : public CCameraState
{// �{�X��ł̓���
public:
	CCameraStateBossBattle();
	~CCameraStateBossBattle();

	void Init(CCamera *pCamera) override;
	void Update(CCamera *pCamera) override;
};

#endif