//*****************************************************
//
// �����Ă���G�̏���[enemyshot.h]
// Author:���R����
//
//*****************************************************
#ifndef _ENEMYSHOT_H_	// ��d�C���N���[�h�h�~
#define _ENEMYSHOT_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "enemyNormal.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CEnemyShot : public CEnemyNormal
{// �����Ă���G
public:
	CEnemyShot();	// �R���X�g���N�^
	~CEnemyShot();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

private:
	// �񋓌^��`
	enum MOTION
	{// ���[�V����
		MOTION_NEUTRAL = 0,	// �ҋ@���[�V����
		MOTION_SHOT,	// �ˌ����[�V����
		MOTION_MAX
	};

	// �����o�֐�
	void ManageAttack(void);	// �U���̊Ǘ�
};

#endif
