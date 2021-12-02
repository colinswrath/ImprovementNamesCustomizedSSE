#include "Settings.h"
#include "TemperFactorManager.h"
#include "version.h"

#include "SKSE/API.h"

void InitLogger()
{
#ifndef NDEBUG
	auto sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
#else
	auto path = logger::log_directory();
	if (!path) {
		return;
	}

	*path /= fmt::format("{}.log"sv, Version::PROJECT);
	auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
#endif

	auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));

#ifndef NDEBUG
	log->set_level(spdlog::level::trace);
#else
	log->set_level(spdlog::level::info);
	log->flush_on(spdlog::level::info);
#endif

	spdlog::set_default_logger(std::move(log));
	spdlog::set_pattern("%s(%#): [%^%l%$] %v"s);

	logger::info(FMT_STRING("{} v{}"), Version::PROJECT, Version::NAME);
}

extern "C" DLLEXPORT constexpr auto SKSEPlugin_Version =
[]() {
	SKSE::PluginVersionData v{};
	v.PluginVersion(Version::MAJOR);
	v.PluginName(Version::PROJECT);
	v.AuthorName("fudgyduff and colinswrath"sv);
	v.UsesAddressLibrary(true);
	return v;
}();

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface * a_skse)
{
	InitLogger();
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
