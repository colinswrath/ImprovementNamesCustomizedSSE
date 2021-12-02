#include "Settings.h"


bool Settings::loadSettings(bool a_dumpParse)
{
	auto [log, success] = Json2Settings::load_settings(FILE_NAME, a_dumpParse);
	if (!log.empty()) {
		logger::error("%s", log.c_str());
	}
	return success;
}


decltype(Settings::style) Settings::style("style", "PlusN");
decltype(Settings::prefix) Settings::prefix("prefix", " [");
decltype(Settings::postfix) Settings::postfix("postfix", "]");
decltype(Settings::customNames) Settings::customNames("customNames");
