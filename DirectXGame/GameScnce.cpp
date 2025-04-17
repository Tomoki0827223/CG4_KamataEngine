#include "GameScnce.h"

GameScnce::~GameScnce() 
{ 
	delete modelParticle_;
	delete camera_;
	delete particle_;
}

void GameScnce::Initialize() {

	modelParticle_ = Model::CreateSphere(4, 4);
	camera_ = new Camera();
	camera_->Initialize();

	Vector3 position = {0.0f, 0.0f, 0.0f};
	particle_ = new Particle();
	particle_->Initialize(modelParticle_, position);

	// ワールド変形の初期化
	worldTransform_.Initialize();

	for (int i = 0; i < 150; i++) {
	}
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
