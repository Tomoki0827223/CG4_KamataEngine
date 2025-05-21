#include "Effect.h"
#include <random>

void Effect::Initialize(Model* model) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();

	// ランダム値をここで一度だけ生成
	std::random_device seedGen;
	std::mt19937 engine(seedGen());
	std::uniform_real_distribution<float> scaleDist(0.5f, 2.0f);
	std::uniform_real_distribution<float> rotDist(0.0f, 3.14159265f * 2.0f);

	randomScaleY_ = scaleDist(engine);
	randomRotZ_ = rotDist(engine);
}

void Effect::Update() {
	worldTransform_.scale_ = {1.0f, randomScaleY_, 1.0f};
	worldTransform_.rotation_.z = randomRotZ_;
	worldTransform_.UpdateMatarix();
	worldTransform_.TransferMatrix();
}


void Effect::Draw(Camera* camera) {

	model_->Draw(worldTransform_, *camera); // 必要な引数を渡す
}

void Effect::SetWorldTransform(const WorldTransform& wt) {
	worldTransform_.scale_ = wt.scale_;
	worldTransform_.rotation_ = wt.rotation_;
	worldTransform_.translation_ = wt.translation_;
	worldTransform_.UpdateMatarix();
	worldTransform_.TransferMatrix();
}
