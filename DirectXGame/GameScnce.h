#pragma once
#include "KamataEngine.h"
#include "Effect.h"

using namespace KamataEngine;

class GameScnce 
{
public:
	
	~GameScnce();
	
	void Initialize();
	void Update();
	void Draw();

private:

	// 3Dモデルの生成
	Model* modelParticle_ = nullptr;
	//カメラ
	Camera* camera_ = nullptr;
	//パーティクル
	Effect* effect_ = nullptr;
	// ワールド変形
	WorldTransform worldTransform_;
};
