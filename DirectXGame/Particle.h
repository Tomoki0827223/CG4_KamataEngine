#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class Particle 
{
public:

	// 初期化
	void Initialize(Model* model, Vector3 position, Vector3 velocity);
	// 更新
	void Update();
	// 描画
	void Draw(Camera* camera);

private:

	WorldTransform worldTransform_; // ワールド変形
	Model* model_ = nullptr;        // モデル

	ObjectColor objectcolor_;
	Vector4 color_;
	Vector3 velocity_; // 速度


};
