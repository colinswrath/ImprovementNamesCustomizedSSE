#include "Settings.h"
#include "TemperFactorManager.h"

#include "SKSE/API.h"



extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface * a_skse)
{
	logger::init();
	logger::info("ImprovementNamesCustomizedSSE loaded");

	SKSE::Init(a_skse);

	if (Settings::loadSettings()) {
		logger::info("Settings successfully loaded");
	} else {
		logger::critical("Settings failed to load!");
		return false;
	}

	SKSE::AllocTrampoline(1<<7);
	TemperFactorManager::InstallHooks();
	//auto it = TemperFactorManager::_stringCache.insert(TemperFactorManager::_formatterMap(1, true));
	//auto res = it.first != TemperFactorManager::_stringCache.end() ? it.first->c_str() : 0;

	//logger::info(std::string(res));

	return true;
};
