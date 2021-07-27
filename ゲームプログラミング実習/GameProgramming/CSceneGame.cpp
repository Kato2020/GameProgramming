#include "CSceneGame.h"
//
#include "CCamera.h"
//
#include "CUtil.h"
//
#include "CRes.h"
//
#include "CKey.h"
//
#include "CModelX.h"
//
#include "CMaterial.h"
//
#include "CXCharacter.h"
//
#include "CXPlayer.h"
//
#include "CXEnemy.h"
//
#include "CCollisionManager.h"

CMatrix Matrix;

//キャラクタクラスのインスタンス
CXPlayer mPlayer;
//敵のインスタンス
CXEnemy mEnemy;

CSceneGame::~CSceneGame() {

}

void CSceneGame::Init() {
	//3Dモデルファイルノの読み込み
	CRes::sModelX.Load(MODEL_FILE);
	//キャラクターにモデルを設定
	mPlayer.Init(&CRes::sModelX);
	//テキストフォントの読み込みと設定
	mFont.LoadTexture("FontG.tga", 1, 4096 / 64);
	//敵の初期設定
	mEnemy.Init(&CRes::sModelX);
	//敵の配置
	mEnemy.mPosition = CVector(7.0f, 0.0f, 0.0f);
}

void CSceneGame::Update() {
	//衝突処理
	CCollisionManager::Get()->Collision();
	//歩くアニメーションに切り替える
	//mPlayer.ChangeAnimation(1, true, 60);
	//敵の更新
	mEnemy.Update();
	//キャラクタークラスの更新
	mPlayer.Update();

	
	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向
	//視点を求める
	e = CVector(1.0f, 2.0f, 10.0f);
	//注視点を求める
	c = CVector();
	//上方向を求める
	u = CVector(0.0f, 1.0f, 0.0f);

	//カメラクラスの設定
	Camera.Set(e, c, u);
	Camera.Render();

	//X軸+回転
	if (CKey::Push('K')){
		Matrix = Matrix*CMatrix().RotateX(1);
	}
	if (CKey::Push('I')){
		Matrix = Matrix*CMatrix().RotateX(-1);
	}
	if (CKey::Push('L')){
		Matrix = Matrix*CMatrix().RotateY(1);
	}
	if (CKey::Push('J')){
		Matrix = Matrix*CMatrix().RotateY(-1);
	}
	//行列設定
	glMultMatrixf(Matrix.mF);
	//モデルの描画
	//CRes::sModelX.Render();
	mPlayer.Render();
	//コライダの描画
	CCollisionManager::Get()->Render();
	//敵描画
	mEnemy.Render();

	//2D描画開始
	CUtil::Start2D(0, 800, 0, 600);

	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2Dの描画終了
	CUtil::End2D();

	return;
}

