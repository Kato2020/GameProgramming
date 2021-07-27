#include "CXEnemy.h"
#include "CCollider.h"

//�R���C�_�̏�����
CXEnemy::CXEnemy()
:mColSphereBody(this, nullptr, CVector(), 0.5f)
, mColSphereHead(this, nullptr, CVector(0.0f, 5.0f, -3.0f), 0.5f)
, mColSphereSword(this, nullptr, CVector(-10.0f, 10.0f, 50.0f), 0.3f)
{}

void CXEnemy::Init(CModelX *model){
	CXCharacter::Init(model);
	//�����s��̐ݒ�
	//��
	mColSphereBody.mpMatrix = &mpCombinedMatrix[8];
	//��
	mColSphereHead.mpMatrix = &mpCombinedMatrix[11];
	//��
	mColSphereSword.mpMatrix = &mpCombinedMatrix[21];
}
//�ۑ�26
//�Փˏ���
void CXEnemy::Collision(CCollider *m, CCollider *o){
	//���g�̃R���C�_�^�C�v�̔���
	switch (m->mType){
		//���R���C�_�̎�
	case CCollider::ESPHERE:
		//����̃R���C�_�����R���C�_�̎�
		if (o->mType == CCollider::ESPHERE){
			//����̃R���C�_�̐e���v���C���[�̎�
			if (o->mpParent->mTag == EPLAYER){
				//����̃R���C�_������ł����
				if (o->mTag == CCollider::ESWORD){
					//�Փ˂��Ă��邩����
					if (CCollider::Collision(m, o)){
						//�|���A�j���[�V�����ɕύX
						ChangeAnimation(11, false, 30);
					}
				}
			}
		}
		break;
	}
}