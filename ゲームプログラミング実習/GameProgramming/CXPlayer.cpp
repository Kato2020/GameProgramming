#include "CXPlayer.h"

#include "CKey.h"

//�R���C�_�̏�����
CXPlayer::CXPlayer()
:mColSphereBody(this, nullptr, CVector(), 0.5f)
, mColSphereHead(this, nullptr, CVector(0.0f, 5.0f, -3.0f), 0.5f)
, mColSphereSword(this, nullptr, CVector(-10.0f, 10.0f, 50.0f), 0.3f)
{
	mTag = EPLAYER;
	mColSphereSword.mTag = CCollider::ESWORD;
}

void CXPlayer::Init(CModelX *model){
	CXCharacter::Init(model);
	//�����s��̐ݒ�
	//��
	mColSphereBody.mpMatrix = &mpCombinedMatrix[8];
	//��
	mColSphereHead.mpMatrix = &mpCombinedMatrix[11];
	//��
	mColSphereSword.mpMatrix = &mpCombinedMatrix[21];
}

//�X�V����
void CXPlayer::Update(){
	//�A�j���[�V�����ԍ���3�̎��Đ��t���[�����Đ��t���[�����ȏ�ɂȂ�����
	if (mAnimationIndex == 3 && mAnimationFrameSize <= mAnimationFrame){
		//�U��1����ҋ@�܂ł̃��[�V����
		ChangeAnimation(4, false, 30);
	}
	//�A�j���[�V�����ԍ���4�̎��Đ��t���[�����Đ��t���[�����ȏ�ɂȂ�����
	else if (mAnimationIndex == 4 && mAnimationFrameSize <= mAnimationFrame){
		//�ҋ@���[�V����
		ChangeAnimation(0, true, 60);
		mMotion = false;
	}
	//�U�����[�V������������
	if (mMotion == false){
		//A�L�[��������Ă���΁AY���̉�]�l��2���Z
		if (CKey::Push('A')){
			mRotation.mY += 2;
		}
		//D�L�[��������Ă���΁AY���̉�]�ɂ�2���Z
		if (CKey::Push('D')){
			mRotation.mY -= 2;
		}
		//W�L�[��������Ă���ΑO�i
		if (CKey::Push('W')){
			ChangeAnimation(1, true, 60);
			//Z��������0.1�i�񂾍��W�Ɉړ�����
			mPosition = CVector(0.0f, 0.0f, 0.1f) * mMatrix;
		}
		//W�L�[��������Ă��Ȃ����
		else{
			//�ҋ@���[�V����
			ChangeAnimation(0, true, 60);
		}
		if (CKey::Push(' ')){
			//�U��1���[�V����
			ChangeAnimation(3, false, 30);
			mMotion = true;
		}
	}

	//�e�N���X�̍X�V����
	CXCharacter::Update();
}