#pragma once
#include <KamataEngine.h>

using namespace KamataEngine;

class Model_Particle 
{
public:

	void Initialize(Model_Particle* model);
	
	void Draw();

private:

	WorldTransform worldTransform_;
	// カメラ
	Camera* camera_ = nullptr;
	// モデル
	Model_Particle* model_ = nullptr;

};
