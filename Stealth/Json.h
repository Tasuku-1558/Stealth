#pragma once

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>

namespace GameData
{
	const char* FILE_PATH = "Data/Json/GameData.json";

	//jsonファイルの解析
	//解析・・・キーの名前をコンテンツとして扱えるようにするための作業
	std::ifstream ifs(FILE_PATH);
	rapidjson::IStreamWrapper isw(ifs);
	rapidjson::Document doc;
}