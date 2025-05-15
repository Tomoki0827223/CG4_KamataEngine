#include "GameScnce.h"
#include <random>

// グローバルまたはクラス内で乱数エンジンを用意
std::random_device seedGen;
std::mt19937 engine(seedGen());
std::uniform_real_distribution<float> scaleDist(0.5f, 2.0f);             // Yスケール範囲
std::uniform_real_distribution<float> rotDist(0.0f, 3.14159265f * 2.0f); // Z回転範囲（0～2π）

GameScnce::~GameScnce() 
{ 
	delete modelParticle_;
	delete camera_;
	delete effect_;
}

void GameScnce::Initialize() {

	modelParticle_ = Model::CreateFromOBJ("ddd", true);
	camera_ = new Camera();
	camera_->Initialize();

	effect_ = new Effect();
	effect_->Initialize(modelParticle_);

	// ワールド変形の初期化
	worldTransform_.Initialize();
}


void GameScnce::Update() {
	// カメラの更新
	camera_->UpdateMatrix();
	// ワールド変形の更新
	worldTransform_.UpdateMatarix();
	// パーティクルの更新
	effect_->Update(); // ここでワールド変形を更新する


	worldTransform_.rotation_.x = 0.0f;
	// Yスケールを乱数で設定
	worldTransform_.scale_ = {1.0f, scaleDist(engine), 1.0f};
	// Z回転を乱数で設定
	worldTransform_.rotation_.z = rotDist(engine);
	worldTransform_.UpdateMatarix();
	worldTransform_.TransferMatrix();
}

void GameScnce::Draw() 
{
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	Model::PreDraw(dxCommon->GetCommandList());

	// パーティクルの描画
	effect_->Draw(camera_);

	Model::PostDraw();

}
