#ifndef YAML_LOADER_H
#define YAML_LOADER_H

#include <vector>
#include <fstream>
#include <iostream>
#include "yaml-cpp\yaml.h"
#include "Globals.h"

class yamlLoader
{
public:
	yamlLoader() = default;

	static void loadSettings(std::string t_loadFileName, SettingsData& t_settings);
	static void WriteSettings(std::string t_loadFileName, SettingsData& t_settings);

};

#endif // !YAML_LOADER_H
