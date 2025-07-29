#pragma once
#include <KamataEngine.h>
#include <memory>

using namespace KamataEngine;

class Stage {
public:
	Stage();
	~Stage();

	void Initialize();
	void Update();
	void Draw();

private:
	float scrollX_ = 0.0f;
	const float scrollSpeed_ = 2.0f;
	const float screenWidth_ = 1280.0f;

	std::unique_ptr<Sprite> bgSprite1_;
	std::unique_ptr<Sprite> bgSprite2_;

	uint32_t textureHandle_ = 0; // テクスチャハンドル

public:
	
	// ...既存...
	Sprite* GetBgSprite1() { return bgSprite1_.get(); }
	Sprite* GetBgSprite2() { return bgSprite2_.get(); }
};