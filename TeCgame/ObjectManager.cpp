#include"ObjectManager.h"
#include "UseOperator.h"
#include"GameSystem.h"


ObjectManager::ObjectManager(String _type) :
	type(_type) {
	//���͋�
	//names.emplace_back(L"");
	//�t�@�C���ǂݍ���
	Array<FilePath> files = FileSystem::DirectoryContents(L"./Data/" + type);
	for (const auto& file : files) {
		if (file.includes(L".png") == true) {
			TextureAsset::Register(FileSystem::BaseName(file), file);
			names.emplace_back(FileSystem::BaseName(file));
		}
	}
	TextureAsset::PreloadAll();


	//csv�ǂݍ���
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
		if (1) {//�����v���C���[�Ƌ߂�������
			if (!(i->isUsing)) {
				UseOperator::get().addUsing(i);
			}
		}
	}
}