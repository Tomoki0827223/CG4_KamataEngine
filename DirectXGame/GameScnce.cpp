#include "GameScnce.h"

GameScnce::~GameScnce() 
{ 
	delete modelParticle_;
	delete camera_;
	delete particle_;
}

void GameScnce::Initialize() {

	modelParticle_ = Model::CreateFromOBJ("ddd", true);
	camera_ = new Camera();
	camera_->Initialize();

	particle_ = new Particle();
	particle_->Initialize(modelParticle_);

	// ワールド変形の初期化
	worldTransform_.Initialize();
}


void GameScnce::Update() {
	// カメラの更新
	camera_->UpdateMatrix();
	// ワールド変形の更新
	worldTransform_.UpdateMatarix();
	// パーティクルの更新
	particle_->Update(); // ここでワールド変形を更新する
	
	worldTransform_.TransferMatrix();
}

void GameScnce::Draw() 
{
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	Model::PreDraw(dxCommon->GetCommandList());

	// パーティクルの描画
	particle_->Draw(camera_);

	Model::PostDraw();

}
