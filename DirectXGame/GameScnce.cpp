#include "GameScnce.h"
#include <random>

std::random_device seedGenerator;
std::mt19937 randomEngine(seedGenerator()); // メルセンヌツイスタの初期化
std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

GameScnce::~GameScnce() {
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

	// 乱数でスケールと回転
	worldTransform_.scale_ = {1.0f, randomEngine, 1.0f};
	worldTransform_.UpdateMatarix();
	worldTransform_.TransferMatrix();

	// effect にも適用
	effect_->SetWorldTransform(worldTransform_);
}


void GameScnce::Update() {
	camera_->UpdateMatrix();
	// ワールド変形は毎フレーム再設定しない（初期化時のまま）
	worldTransform_.UpdateMatarix();
	worldTransform_.TransferMatrix();

	// パーティクルの更新
	effect_->Update();
}

void GameScnce::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	Model::PreDraw(dxCommon->GetCommandList());

	effect_->Draw(camera_);

	Model::PostDraw();
}
