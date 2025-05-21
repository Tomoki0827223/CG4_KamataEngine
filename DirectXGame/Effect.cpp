#include "Effect.h"
#include <random>

void Effect::Initialize(Model* model) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();

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
