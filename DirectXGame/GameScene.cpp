#include "GameScene.h"

GameScene::~GameScene() 
{
	delete stage_;
	delete player_;
	delete playerModel_;
	delete model_;
}

void GameScene::Initialize() {

	stage_ = new Stage();
	stage_->Initialize();

	stage_->Update();

	// カメラの初期化
	camera_.Initialize();

	worldTransform.Initialize();

	player_ = new Player();
	player_->Initialize();
	playerModel_ = Model::CreateFromOBJ("cube");
}

void GameScene::Update() 
{ 
	stage_->Update(); 

	player_->Update();
}

void GameScene::Draw() {

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Sprite::PreDraw(dxCommon->GetCommandList());

	stage_->Draw();

	player_->Draw();

	Sprite::PostDraw();
}