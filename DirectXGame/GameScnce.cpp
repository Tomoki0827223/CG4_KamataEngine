#include "GameScnce.h"
#include <random>

using namespace MathUtility;

std::random_device seedGenerator;
std::mt19937 randomEngine(seedGenerator()); // メルセンヌツイスタの初期化
std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

GameScnce::~GameScnce() {
	delete modelParticle_;
	delete camera_;

	for (Particle* particle : particles_) {
		delete particle;
	}
	particles_.clear();
}


void GameScnce::Initialize() {

	modelParticle_ = new Model();
	modelParticle_ = Model::CreateFromOBJ("ddd", true); // モデルの生成
	camera_ = new Camera();
	camera_->Initialize();

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
	
	if (rand() % 20 == 0) {

		//発生位置は乱数とパーティクル生成
		Vector3 position = {distribution(randomEngine) * 30.0f, distribution(randomEngine) * 20.0f, 0};
		ParticleBorn(position); // 後で呼び出す
	}

	for (Particle* particle : particles_) {
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

void GameScnce::ParticleBorn(Vector3 position) {
	const int modelCount = 10;

	for (int i = 0; i < modelCount; ++i) {

		Vector3 pos = position; // すべて同じ位置に重ねる

		// ランダムなスケール（Y軸のみ正の値）
		float scaleY = std::abs(distribution(randomEngine)) + 4.0f; // 最低0.5以上

		// ランダムなZ軸回転（ラジアン）
		float rotZ = std::uniform_real_distribution<float>(0.0f, MathUtility::PI * 2.0f)(randomEngine);

		// パーティクル生成
		Particle* particle = new Particle();
		Vector3 velocity = {0, 0, 0};

		particle->Initialize(modelParticle_, pos, velocity);

		// スケールと回転を反映
		particle->worldTransform_.scale_.y = scaleY;
		particle->worldTransform_.rotation_.z = rotZ;

		particles_.push_back(particle);
	}
}
