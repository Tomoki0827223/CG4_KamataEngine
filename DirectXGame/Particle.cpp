#include "Particle.h"
#include "math/MathUtility.h"
#include <random>

using namespace MathUtility;

void Particle::Initialize(Model* model, Vector3 position, Vector3 velocity) {

	assert(model);
	model_ = model;
	velocity_ = velocity;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.scale_ = {0.2f, 0.2f, 0.2f};

	objectcolor_.Initialize();


	// ランダムな色を生成
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<float> dist(0.0f, 1.0f);

	color_ = {dist(gen), dist(gen), dist(gen), 1.0f}; // RGBをランダム、Aは1.0
}


void Particle::Update() 
{
	//フェード処理
	color_.w = std::clamp(1.0f - counter_ / kDuration, 0.0f, 1.0f); // アルファ値を更新

	if (isFinished_) {
		return;
	}

	counter_ += 1.0f / 60.0f; // カウンターを更新

	if (counter_ >= kDuration) {

		counter_ = kDuration; // カウンターを最大値にする

		isFinished_ = true; // 寿命を超えたら終了
	}


	worldTransform_.translation_ += velocity_; // ワールド変形の位置を初期化
	worldTransform_.TransferMatrix();                   // ワールド変形の転送
	worldTransform_.UpdateMatarix(); // ワールド変形の更新

	objectcolor_.SetColor(color_); // 色を設定
}

void Particle::Draw(Camera* camera) {

	model_->Draw(worldTransform_, *camera, &objectcolor_); // 必要な引数を渡す
}
