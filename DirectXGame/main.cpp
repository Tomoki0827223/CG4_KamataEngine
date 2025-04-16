#include "KamataEngine.h"
#include <Windows.h>
#include "GameScnce.h"

using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// 初期化処理
	//  // エンジンの初期化

	KamataEngine::Initialize(L"LE3C_26_ムラタ_トモキ");

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	GameScnce* gameScnce = new GameScnce();
	gameScnce->Initialize();

	// メインループ
	while (true) {
		if (KamataEngine::Update()) {
			break;
		}

		// ゲームシーンの更新
		gameScnce->Update();

		// 描画処理
		dxCommon->PreDraw();

		// ゲームシーンの描画
		gameScnce->Draw();

		// 描画処理
		dxCommon->PostDraw();
	}

	delete gameScnce;
	gameScnce = nullptr;

	// 終了処理
	KamataEngine::Finalize();
	return 0;
}
