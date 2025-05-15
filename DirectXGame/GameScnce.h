#pragma once
#include "KamataEngine.h"
#include "Model_Particle.h"

using namespace KamataEngine;

class GameScnce {
public:
	~GameScnce();

	void Initialize();
	void Update();
	void Draw();

private:

	// カメラ
	Camera* camera_ = nullptr;
	// ワールド変形
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	Model_Particle* model_particle_ = nullptr;
};
