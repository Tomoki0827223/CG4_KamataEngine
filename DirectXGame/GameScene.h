#pragma once
#include "KamataEngine.h"
#include "Stage.h"

using namespace KamataEngine;

class GameScene {
public:
	~GameScene();

	void Initialize();

	void Update();

	void Draw();

private:
	uint32_t textureHandle_ = 0;

	KamataEngine::Sprite* sprite_ = nullptr;

	// 3Dモデルデータ
	Model* model_ = nullptr;

	Camera camera_;

	WorldTransform worldTransform;

	Stage* stage_ = nullptr;
};