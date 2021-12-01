#include "TemperFactorManager.h"

#include <cmath>
#include <cstdio>
#include <set>
#include <string>
#include <string_view>
#include <typeinfo>

#include "Settings.h"

#include "RE/Skyrim.h"
#include "REL/Relocation.h"
#include "SKSE/API.h"
#include "SKSE/Trampoline.h"


std::string TemperFactorManager::AsVanilla(std::uint32_t a_level, bool a_isWeapon)
{
	static GMSTCache cache;
	switch (a_level) {
	case 1:
		return a_isWeapon ? cache("sHealthDataPrefixWeap1") : cache("sHealthDataPrefixArmo1");
	case 2:
		return a_isWeapon ? cache("sHealthDataPrefixWeap2") : cache("sHealthDataPrefixArmo2");
	case 3:
		return a_isWeapon ? cache("sHealthDataPrefixWeap3") : cache("sHealthDataPrefixArmo3");
	case 4:
		return a_isWeapon ? cache("sHealthDataPrefixWeap4") : cache("sHealthDataPrefixArmo4");
	case 5:
		return a_isWeapon ? cache("sHealthDataPrefixWeap5") : cache("sHealthDataPrefixArmo5");
	default:
		return a_isWeapon ? cache("sHealthDataPrefixWeap6") : cache("sHealthDataPrefixArmo6");
	}
}


std::string TemperFactorManager::AsVanillaPlus(std::uint32_t a_level, bool a_isWeapon)
{
	auto result = AsVanilla(a_level, a_isWeapon);
	if (a_level > 5) {
		result += " ";
		result += std::to_string(a_level - 5);
	}
	return result;
}


std::string TemperFactorManager::AsPlusN(std::uint32_t a_level, [[maybe_unused]] bool a_isWeapon)
{
	return std::string("+") + std::to_string(a_level);
}


std::string TemperFactorManager::AsInternal(std::uint32_t a_level, [[maybe_unused]] bool a_isWeapon)
{
	std::string result = std::to_string((a_level / 10) + 1);
	result += ".";
	result += std::to_string(a_level % 10);
	return result;
}


std::string TemperFactorManager::AsCustom(std::uint32_t a_level, [[maybe_unused]] bool a_isWeapon)
{
	std::size_t idx = a_level - 1;
	if (idx < Settings::customNames->size()) {
		return (*Settings::customNames)[idx];
	} else {
		return Settings::customNames->empty() ? "" : Settings::customNames->back();
	}
}


std::string TemperFactorManager::AsRomanNumeral(std::uint32_t a_level, [[maybe_unused]] bool a_isWeapon)
{
	constexpr std::pair<std::uint32_t, std::string_view> MILESTONES[] = {
		{ 1, "I" },
		{ 4, "IV" },
		{ 5, "V" },
		{ 9, "IX" },
		{ 10, "X" },
		{ 40, "XL" },
		{ 50, "L" },
		{ 100, "C" },
		{ 400, "CD" },
		{ 500, "D" },
		{ 900, "CM" },
		{ 1000, "M" }
	};

	constexpr std::size_t SIZE = std::extent<decltype(MILESTONES)>::value;

	std::string result;
	for (auto i = SIZE; a_level; --i) {
		auto div = a_level / MILESTONES[i].first;
		a_level = a_level % MILESTONES[i].first;
		while (div--) {
			result += MILESTONES[i].second;
		}
	}

	return result;
}


const char* TemperFactorManager::GetTemperFactor(float a_factor, bool a_isWeapon)
{
	auto fLevel = std::roundf((a_factor - 1.0) * 10.0);
	if (fLevel < 1.0) {
		return 0;
	}

	auto level = static_cast<std::uint32_t>(fLevel);
	auto it = _stringCache.insert(_formatterMap(level, a_isWeapon));
	return it.first != _stringCache.end() ? it.first->c_str() : 0;
}


void TemperFactorManager::VFormat(RE::BSString* a_dst, const char* a_fmt, ...)
{
	std::string fmt = "%s";
	fmt += *Settings::prefix;
	fmt += "%s";
	fmt += *Settings::postfix;

	std::va_list args1;
	va_start(args1, a_fmt);
	std::va_list args2;
	va_copy(args2, args1);
	std::vector<char> buf(std::vsnprintf(0, 0, fmt.c_str(), args1) + 1);
	va_end(args1);
	std::vsnprintf(buf.data(), buf.size(), fmt.c_str(), args2);
	va_end(args2);

	std::string_view view(buf.data(), buf.size());
	*a_dst = view;
}


void TemperFactorManager::sprintf_s(char* a_buffer, std::size_t a_buffSize, const char* a_fmt, ...)
{
	std::string fmt = *Settings::prefix;
	fmt += "%s";
	fmt += *Settings::postfix;

	std::va_list args;
	va_start(args, a_fmt);
	std::vsnprintf(a_buffer, a_buffSize, fmt.c_str(), args);
	va_end(args);
}


void TemperFactorManager::InstallHooks()
{
	REL::Offset<std::uintptr_t> funcBase(REL::ID(12633));

	auto trampoline = SKSE::GetTrampoline();
	trampoline->Write5Call(funcBase.GetAddress() + 0x59, &TemperFactorManager::GetTemperFactor);
	trampoline->Write5Call(funcBase.GetAddress() + 0x1A6, &TemperFactorManager::VFormat);
	trampoline->Write5Call(funcBase.GetAddress() + 0x177, &TemperFactorManager::VFormat);
	trampoline->Write5Call(funcBase.GetAddress() + 0x13D, &TemperFactorManager::sprintf_s);

	_MESSAGE("Installed hooks for %s", typeid(TemperFactorManager).name());
}


TemperFactorManager::FormatterMap::FormatterMap() :
	_map()
{
	_map.insert({ "Vanilla", TemperFactorManager::AsVanilla });
	_map.insert({ "VanillaPlus", TemperFactorManager::AsVanillaPlus });
	_map.insert({ "PlusN", TemperFactorManager::AsPlusN });
	_map.insert({ "Internal", TemperFactorManager::AsInternal });
	_map.insert({ "Custom", TemperFactorManager::AsCustom });
	_map.insert({ "RomanNumeral", TemperFactorManager::AsRomanNumeral });
}


std::string TemperFactorManager::FormatterMap::operator()(std::uint32_t a_factor, bool a_isWeapon)
{
	auto it = _map.find(*Settings::style);
	if (it != _map.end()) {
		return it->second(a_factor, a_isWeapon);
	} else {
		return TemperFactorManager::AsVanilla(a_factor, a_isWeapon);
	}
}


TemperFactorManager::GMSTCache::GMSTCache() :
	_map()
{
	constexpr std::string_view NAMES[] = {
		"sHealthDataPrefixWeap1",
		"sHealthDataPrefixArmo1",
		"sHealthDataPrefixWeap2",
		"sHealthDataPrefixArmo2",
		"sHealthDataPrefixWeap3",
		"sHealthDataPrefixArmo3",
		"sHealthDataPrefixWeap4",
		"sHealthDataPrefixArmo4",
		"sHealthDataPrefixWeap5",
		"sHealthDataPrefixArmo5",
		"sHealthDataPrefixWeap6",
		"sHealthDataPrefixArmo6"
	};

	constexpr std::size_t SIZE = std::extent<decltype(NAMES)>::value;

	for (std::size_t i = 0; i < SIZE; ++i) {
		Insert(std::string(NAMES[i]));
	}
}


std::string TemperFactorManager::GMSTCache::operator()(std::string_view a_name)
{
	auto it = _map.find(a_name);
	return it != _map.end() ? it->second->GetString() : "";
}


void TemperFactorManager::GMSTCache::Insert(std::string a_name)
{
	auto gmst = RE::GameSettingCollection::GetSingleton();
	auto setting = gmst->GetSetting(a_name.c_str());
	if (setting) {
		auto it = _map.insert(std::make_pair(std::move(a_name), setting));
		assert(it.second);
	} else {
		assert(false);
	}
}


decltype(TemperFactorManager::_stringCache) TemperFactorManager::_stringCache;
decltype(TemperFactorManager::_formatterMap) TemperFactorManager::_formatterMap;
