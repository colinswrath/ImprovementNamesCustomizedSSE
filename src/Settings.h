#pragma once

#include "Json2Settings.h"

namespace J2S = Json2Settings;


class Settings
{
public:
	Settings() = delete;
	static bool loadSettings(bool a_dumpParse = false);


	static J2S::sSetting style;
	static J2S::sSetting prefix;
	static J2S::sSetting postfix;
	static J2S::aSetting<std::string> customNames;

private:
	static inline constexpr char FILE_NAME[] = "Data\\SKSE\\Plugins\\ImprovementNamesCustomizedSSE.json";
};
