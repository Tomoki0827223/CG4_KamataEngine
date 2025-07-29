#include "stage.h"


Stage::Stage() {}

Stage::~Stage() {}

void Stage::Initialize() {

	textureHandle_ = TextureManager::Load("Resources/scroll_bg.png");

	bgSprite1_.reset(Sprite::Create(textureHandle_, {0, 0}));
	bgSprite2_.reset(Sprite::Create(textureHandle_, {screenWidth_, 0}));
}

void Stage::Update() {
	scrollX_ -= scrollSpeed_;
	if (scrollX_ <= -screenWidth_) {
		scrollX_ += screenWidth_;
	}
	if (bgSprite1_)
		bgSprite1_->SetPosition({scrollX_, 0});
	if (bgSprite2_)
		bgSprite2_->SetPosition({scrollX_ + screenWidth_, 0});
}

void Stage::Draw() {
	if (bgSprite1_)
		bgSprite1_->Draw();
	if (bgSprite2_)
		bgSprite2_->Draw();
}