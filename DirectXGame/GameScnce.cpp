#include "GameScnce.h"
#include <random>

using namespace MathUtility;

std::random_device seedGenerator;
std::mt19937 randomEngine(seedGenerator()); // メルセンヌツイスタの初期化
std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

GameScnce::~GameScnce() {
	
	
	delete camera_;
	delete model_;
	delete model_particle_;
}


void GameScnce::Initialize() {

	camera_ = new Camera();
	camera_->Initialize();

	model_ = new Model();
	model_ = Model::CreateFromOBJ("ddd", true);

	srand((unsigned)time(NULL));

	// ワールド変形の初期化
	worldTransform_.Initialize();

}

void GameScnce::Update() {
	// カメラの更新
	camera_->UpdateMatrix();
	// ワールド変形の更新
	worldTransform_.UpdateMatarix();
	// パーティクルの更新

	worldTransform_.TransferMatrix();
}

void GameScnce::Draw() 
{
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	Model::PreDraw(dxCommon->GetCommandList());

	model_->Draw(worldTransform_, camera_);

	Model::PostDraw();

}