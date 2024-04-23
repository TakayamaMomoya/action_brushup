//*****************************************************
//
// �J�����̃r�w�C�r�A[cameraBehavior.h]
// Author:���R����
//
//*****************************************************

#ifndef _CAMERABEHAVIOR_H_
#define _CAMERABEHAVIOR_H_

//****************************************************
// �O���錾
//****************************************************
class CCamera;

//****************************************************
// �N���X�̒�`
//****************************************************
class CCameraBehavior
{// ���N���X
public:
	CCameraBehavior();
	virtual ~CCameraBehavior();

	virtual void Update(CCamera *pCamera) = 0;

private:
};

class CCameraBehaviorFollowPlayer : public CCameraBehavior
{// �v���C���[�̒Ǐ]
public:
	CCameraBehaviorFollowPlayer();
	~CCameraBehaviorFollowPlayer();

	void Update(CCamera *pCamera) override;
};

class CCameraBehaviorApperPlayer : public CCameraBehavior
{// �v���C���[�̓o��
public:
	CCameraBehaviorApperPlayer();
	~CCameraBehaviorApperPlayer();

	void Update(CCamera *pCamera) override;
};

#endif