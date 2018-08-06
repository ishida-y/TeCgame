#include "EnemyManager.h"
#include"UseOperator.h"

EnemyManager::EnemyManager(String _type) :
	type(_type) {
	//ファイル読み込み
	Array<FilePath> files = FileSystem::DirectoryContents(L"./Data/" + type);
	for (const auto& file : files) {
		if (file.includes(L".png") == true) {
			TextureAsset::Register(FileSystem::BaseName(file), file);
			names.emplace_back(FileSystem::BaseName(file));
		}
	}
	TextureAsset::PreloadAll();

	//csv読み込み
	const CSVReader csv(L"sample.csv");
	if (!csv) {
		return;
	}
	for (int i = 0; i < csv.rows; i++) {
		if (csv.get<String>(i, 0) == type) {
			for (int j = 0; j < names.size(); j++) {
				if (csv.get<String>(i, 1) == names[j]) {
					enemies.emplace_back(std::make_shared<SampleEnemy>(csv.get<String>(i, 1), csv.get<Vec2>(i, 2), csv.get<double>(i, 3), csv.get<Vec2>(i, 4), csv.get<int>(i, 5)));
					break;
				}
			}
		}
	}
}

void EnemyManager::useUpdate(PhysicsWorld& world) {
	for (auto i : enemies) {
		if (1) {//もしプレイヤーと近すぎず遠すぎなかったら
			if (!(i->obj.isUsing && !(i->isDead))) {
				UseOperator::get().addUsingEnemy(i, world);
			}
		}
	}
}
