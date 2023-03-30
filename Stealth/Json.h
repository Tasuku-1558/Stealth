#pragma once

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>


namespace GameData
{
	const char* filePath = "Data/Json/GameData.json";

	//json�t�@�C���̉��
	//��́E�E�E�L�[�̖��O���R���e���c�Ƃ��Ĉ�����悤�ɂ��邽�߂̍��
	std::ifstream ifs(filePath);
	rapidjson::IStreamWrapper isw(ifs);
	rapidjson::Document doc;
}