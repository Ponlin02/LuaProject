#pragma once
#include <string>
#include <vector>
#include "lua.hpp"

void SaveFileName(std::string &fileName);

void LoadMap(lua_State* L);

std::vector<std::string> GetMapFiles(const std::string& folder);