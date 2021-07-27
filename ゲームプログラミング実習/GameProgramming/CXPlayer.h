#ifndef CXPLAYER_H
#define CXPLAYER_H

#include "CXCharacter.h"
#include "CCollider.h"

class CXPlayer:public CXCharacter{
public:
	//�R���C�_�̐錾
	CCollider mColSphereBody;  //��
	CCollider mColSphereHead;  //��
	CCollider mColSphereSword; //��
	//���[�V������������
	bool mMotion;
	//�f�t�H���g�R���X�g���N�^
	CXPlayer();
	//��x�������s
	void Init(CModelX *model);
	//�X�V����
	void Update();
};

#endif