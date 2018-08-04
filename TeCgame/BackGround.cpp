#include "BackGround.h"

BackGround::BackGround(String _type, Vec2 _moveRate) :
	moveRate(_moveRate) {

	//ファイル読み込み
	Array<FilePath> files = FileSystem::DirectoryContents(L"./Data/" + _type);
	for (const auto& file : files) {
		if (file.includes(L".png") == true) {
			TextureAsset::Register(FileSystem::BaseName(file), file);
		}
	}

	//csv読み込み
	const CSVReader csv(L"sample.csv");
	if (!csv)
	{
		return;
	}
	for (int i = 0; i < csv.rows; i++) {
		if (csv.get<String>(i, 0) == _type) {
			name = csv.get<String>(i, 1);
			pos = csv.get<Vec2>(i, 2);
			rot = csv.get<double>(i, 3);
			scale = csv.get<Vec2>(i, 4);
			alpha = csv.get<int>(i, 5);
			break;
			/*
			for (int j = 0; j < names.size(); j++) {
				if (csv.get<String>(i, 1) == names[j]) {
					use += j;
					obj.reset();
					obj = std::make_shared<BackGround>(*use, moveRate, csv.get<Vec2>(i, 2), csv.get<double>(i, 3), csv.get<Vec2>(i, 4), csv.get<int>(i, 5));
					break;
				}
			}
			break;
			*/
		}
	}
}


void BackGround::draw(Vec2 camera) const {
	//ループ描画処理
	Vec2 cam = camera * 100;
	Vec2 tmp = Vec2(cam.x * (1 - moveRate.x), cam.y *(1 - moveRate.y));//動きの差
	double x = pos.x + tmp.x;//一番左のx位置
	const static int loop = 4;//枚数
	while (cam.x - x > TextureAsset(name).width * loop / 2.0) {
		x += TextureAsset(name).width;
	}
	for (int i = 0; i < loop; i++) {
		TextureAsset(name).scale(1.0/100.0).draw(Vec2(x, tmp.y + pos.y) / 100.0, Color(255, 255, 255, alpha));
		x += TextureAsset(name).width;
	}
}
