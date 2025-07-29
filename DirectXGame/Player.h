#pragma once
#include "KamataEngine.h"
#include "3d/WorldTransform.h"

using namespace KamataEngine;

class Player {
public:
	~Player();

	void Initialize();

	void Update();

	void Draw();

	//void ParticleBorn(Vector3 position);

private:
	// パーティクル3Dモデルデータ
	Model* modelPlayer_ = nullptr;

	Input* input_ = nullptr;

	Camera camera_;

	WorldTransform worldTransform;
};