#include "Particle.h"

void Particle::Initialize(Model* model) 
{ 
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
}

void Particle::Update() 
{ 
	worldTransform_.rotation_.x = 0.0f;
	worldTransform_.UpdateMatarix();
}

void Particle::Draw(Camera* camera) {

	model_->Draw(worldTransform_, *camera); // 必要な引数を渡す
}
