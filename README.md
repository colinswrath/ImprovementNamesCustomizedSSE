# Improvement Names Customized SSE
Improvement Names Customized ported for Skyrim SE 1.6.x+ (Otherwise known as AE).
It has also been restructured to use CMake and newer CommonLib versions.
## Build Dependencies
* [Json2Settings](https://github.com/Ryan-rsm-McKenzie/Json2Settings)
## End User Dependencies
* [SKSE64](https://skse.silverlock.org/)
* [Address Library AE] (https://www.nexusmods.com/skyrimspecialedition/mods/32444)

## Settings
Setting | Description
--- | ---
`style` | The improvement string display style. Valid inputs are: `"Vanilla"`, `"VanillaPlus"`, `"PlusN"`, `"Internal"`, `"Custom"`, and `"RomanNumeral"`.
`prefix` | The improvement string prefix.
`postfix` | The improvement string postfix.
`customNames` | A set of strings to be used when `"Custom"` style is selected.
