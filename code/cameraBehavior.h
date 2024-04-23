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
{
public:
	CCameraBehavior();
	virtual ~CCameraBehavior();

	virtual void Update(CCamera *pCamera) = 0;

private:
};

class CCameraBehaviorFollowPlayer : public CCameraBehavior
{
public:
	CCameraBehaviorFollowPlayer();
	~CCameraBehaviorFollowPlayer();

	void Update(CCamera *pCamera) override;
};

#endif