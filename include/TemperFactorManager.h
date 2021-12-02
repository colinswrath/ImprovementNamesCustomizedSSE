#pragma once

#include <functional>
#include <set>
#include <string>
#include <unordered_map>

#include "RE/Skyrim.h"


class TemperFactorManager
{
public:
	static std::string AsVanilla(std::uint32_t a_level, bool a_isWeapon);
	static std::string AsVanillaPlus(std::uint32_t a_level, bool a_isWeapon);
	static std::string AsPlusN(std::uint32_t a_level, bool a_isWeapon);
	static std::string AsInternal(std::uint32_t a_level, bool a_isWeapon);
	static std::string AsCustom(std::uint32_t a_level, bool a_isWeapon);
	static std::string AsRomanNumeral(std::uint32_t a_level, bool a_isWeapon);

	static const char* GetTemperFactor(float a_factor, bool a_isWeapon);
	static void VFormat(RE::BSString* a_dst, const char* a_fmt, ...);
	static void sprintf_s(char* a_buffer, std::size_t a_buffSize, const char* a_fmt, ...);

	static void InstallHooks();

private:
	class FormatterMap
	{
	public:
		FormatterMap();

		std::string operator()(std::uint32_t a_factor, bool a_isWeapon);

	private:
		std::unordered_map<std::string, std::function<std::string(std::uint32_t, bool)>> _map;
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
