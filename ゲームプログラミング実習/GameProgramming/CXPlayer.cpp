#include "CXPlayer.h"

#include "CKey.h"

//コライダの初期化
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
	//合成行列の設定
	//体
	mColSphereBody.mpMatrix = &mpCombinedMatrix[8];
	//頭
	mColSphereHead.mpMatrix = &mpCombinedMatrix[11];
	//剣
	mColSphereSword.mpMatrix = &mpCombinedMatrix[21];
}

//更新処理
void CXPlayer::Update(){
	//アニメーション番号が3の時再生フレームが再生フレーム数以上になったら
	if (mAnimationIndex == 3 && mAnimationFrameSize <= mAnimationFrame){
		//攻撃1から待機までのモーション
		ChangeAnimation(4, false, 30);
	}
	//アニメーション番号が4の時再生フレームが再生フレーム数以上になったら
	else if (mAnimationIndex == 4 && mAnimationFrameSize <= mAnimationFrame){
		//待機モーション
		ChangeAnimation(0, true, 60);
		mMotion = false;
	}
	//攻撃モーション中か判定
	if (mMotion == false){
		//Aキーが押されていれば、Y軸の回転値に2加算
		if (CKey::Push('A')){
			mRotation.mY += 2;
		}
		//Dキーが押されていれば、Y軸の回転にを2減算
		if (CKey::Push('D')){
			mRotation.mY -= 2;
		}
		//Wキーが押されていれば前進
		if (CKey::Push('W')){
			ChangeAnimation(1, true, 60);
			//Z軸方向に0.1進んだ座標に移動する
			mPosition = CVector(0.0f, 0.0f, 0.1f) * mMatrix;
		}
		//Wキーが押されていなければ
		else{
			//待機モーション
			ChangeAnimation(0, true, 60);
		}
		if (CKey::Push(' ')){
			//攻撃1モーション
			ChangeAnimation(3, false, 30);
			mMotion = true;
		}
	}

	//親クラスの更新処理
	CXCharacter::Update();
}