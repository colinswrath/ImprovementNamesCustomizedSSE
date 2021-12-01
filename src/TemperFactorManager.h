#pragma once

#include <functional>
#include <set>
#include <string>
#include <unordered_map>

#include "RE/Skyrim.h"


class TemperFactorManager
{
public:
	static std::string AsVanilla(UInt32 a_level, bool a_isWeapon);
	static std::string AsVanillaPlus(UInt32 a_level, bool a_isWeapon);
	static std::string AsPlusN(UInt32 a_level, bool a_isWeapon);
	static std::string AsInternal(UInt32 a_level, bool a_isWeapon);
	static std::string AsCustom(UInt32 a_level, bool a_isWeapon);
	static std::string AsRomanNumeral(UInt32 a_level, bool a_isWeapon);

	static const char* GetTemperFactor(float a_factor, bool a_isWeapon);
	static void VFormat(RE::BSString* a_dst, const char* a_fmt, ...);
	static void sprintf_s(char* a_buffer, std::size_t a_buffSize, const char* a_fmt, ...);

	static void InstallHooks();

private:
	class FormatterMap
	{
	public:
		FormatterMap();

		std::string operator()(UInt32 a_factor, bool a_isWeapon);

	private:
		std::unordered_map<std::string, std::function<std::string(UInt32, bool)>> _map;
	};


	class GMSTCache
	{
	public:
		GMSTCache();

		std::string operator()(std::string_view a_name);

	private:
		void Insert(std::string a_name);


		std::unordered_map<std::string_view, RE::Setting*> _map;
	};


	static std::set<std::string> _stringCache;
	static FormatterMap _formatterMap;
};
