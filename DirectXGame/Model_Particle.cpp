#include "Model.h"
#include "Model_Particle.h"


void Model_Particle::Initialize(Model_Particle* model) 
{ 
	assert(model_);
	model_ = model;
	worldTransform_.Initialize();
}

void Model_Particle::Draw() 
{ 
	model_->Draw(); 
}
