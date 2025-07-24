#pragma once
#include <KamataEngine.h>
#include "json.hpp"
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <map>
#include "imgui.h"

using namespace KamataEngine;

class GameScnce {

	// オブジェクト1個分のデータ
	struct ObjectData {
		std::string type;
		std::string name;

		struct Transform {
			Vector3 translation;
			Vector3 rotation;
			Vector3 scaling;
		};

		Transform transform;

		std::string file_name;
	};

	// レベルデータ
	struct LevelData {
		std::string name;
		std::vector<ObjectData> objects;
	};

public:

	void Initialize();
	void Update();
	void Draw();

private:


	std::map<std::string, Model*> models;

	std::vector<WorldTransform*> objects;

	// LevelData構造体へ格納
	LevelData* levelData = nullptr;

	Camera* camera = nullptr;
};
