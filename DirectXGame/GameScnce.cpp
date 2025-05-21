#include "GameScnce.h"
#include <random>

// 乱数生成用（グローバル）
std::random_device seedGen;
std::mt19937 engine(seedGen());
std::uniform_real_distribution<float> scaleDist(-1.0f, 1.0f);             // Yスケール範囲
std::uniform_real_distribution<float> rotDist(0.0f, 1.0f); // Z回転範囲（0～2π）

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
	worldTransform_.scale_ = {1.0f, scaleDist(engine), 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, rotDist(engine)};
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
