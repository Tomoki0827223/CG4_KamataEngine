#include "Effect.h"
#include <random>

void Effect::Initialize(Model* model) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
}

void Effect::Update() 
{ 
}

void Effect::Draw(Camera* camera) {

	model_->Draw(worldTransform_, *camera); // 必要な引数を渡す
}
