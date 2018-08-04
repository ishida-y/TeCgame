#include"ObjectManager.h"
#include "UseOperator.h"
#include"GameSystem.h"


ObjectManager::ObjectManager(String _type) :
	type(_type) {
	//頭は空
	//names.emplace_back(L"");
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
	if (!csv)
	{
		return;
	}
	for (int i = 0; i < csv.rows; i++) {
		if (csv.get<String>(i, 0) == type) {
			for (int j = 0; j < names.size(); j++) {
				if (csv.get<String>(i, 1) == names[j]) {
					objs.emplace_back(std::make_shared<Object>(csv.get<String>(i, 1), csv.get<Vec2>(i, 2), csv.get<double>(i, 3), csv.get<Vec2>(i, 4), csv.get<int>(i, 5)));
					break;
				}
			}
		}
	}
}

void ObjectManager::useUpdate() {
	if (GameSystem::get().debug) {
		Print(L"Objs:");
		Println(objs.size());
	}
	for (auto i : objs) {
		if (1) {//もしプレイヤーと近かったら
			if (!(i->isUsing)) {
				UseOperator::get().addUsing(i);
			}
		}
	}
}