#pragma once

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>


namespace GameData
{
	const char* filePath = "Data/Json/GameData.json";

	//jsonファイルの解析
	//解析・・・キーの名前をコンテンツとして扱えるようにするための作業
	std::ifstream ifs(filePath);
	rapidjson::IStreamWrapper isw(ifs);
	rapidjson::Document doc;
}