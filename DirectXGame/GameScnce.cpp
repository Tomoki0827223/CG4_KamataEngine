#include "GameScnce.h"
#include <random>

using namespace MathUtility;

std::random_device seedGenerator;
std::mt19937 randomEngine(seedGenerator()); // メルセンヌツイスタの初期化
std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

GameScnce::~GameScnce() 
{ 
	delete modelParticle_;
	delete camera_;
	delete particle_;

	for (Particle* particle : particles_) {
		delete particle;
	}
	particles_.clear();
}

void GameScnce::Initialize() {

	modelParticle_ = Model::CreateSphere(4, 4);
	camera_ = new Camera();
	camera_->Initialize();

	for (int i = 0; i < 150; i++) {
		Particle* particle = new Particle();
		Vector3 position = {0.0f, 0.0f, 0.0f};
		Vector3 velocity = {distribution(randomEngine), distribution(randomEngine), 0}; // ランダムな速度を生成
		Normalize(velocity);
		velocity *= distribution(randomEngine); // ランダムな速度を生成
		velocity *= 0.1f;                       // スピードを調整
		particle->Initialize(modelParticle_, position, velocity);
		particles_.push_back(particle);
	}
	
	// ワールド変形の初期化
	worldTransform_.Initialize();
}


void GameScnce::Update() {
	// カメラの更新
	camera_->UpdateMatrix();
	// ワールド変形の更新
	worldTransform_.UpdateMatarix();
	// パーティクルの更新
	for (Particle * particle : particles_) {
		particle->Update();
	}

	// 終了フラグの立ったパーティクルを削除
	for (auto it = particles_.begin(); it != particles_.end();) {
		if ((*it)->IsFinished()) {
			delete *it;
			it = particles_.erase(it);
		} else {
			++it;
		}
	}

	worldTransform_.TransferMatrix();
}

void GameScnce::Draw() 
{
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	Model::PreDraw(dxCommon->GetCommandList());

	// パーティクルの描画
	for (Particle* particle : particles_) {
		particle->Draw(camera_);
	}

	Model::PostDraw();

}
