#include "entt.hpp"
#include "lua.hpp"
#include "graphics/rayLibTest.hpp"

#include <iostream>
#include <thread>
#include <string>
#include "Scene.hpp"
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

#include "gameloop/gameloop.hpp"

#include "graphics/rayLibTest.hpp"

void ConsoleThreadFunction(lua_State* L)
{
	std::string input;
	while (GetConsoleWindow())
	{
		std::cout << "> ";
		std::getline(std::cin, input);

		if (luaL_dostring(L, input.c_str()) != LUA_OK)
		{
			DumpError(L);
		}
	}
}



int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	//luaL_dostring(L, "print('hello from lua')");

	std::thread consoleThread(ConsoleThreadFunction, L);

	Scene scene;
	Scene::lua_openscene(L, &scene);
	
	/*scene.CreateSystem<PoisonSystem>(15);
	scene.CreateSystem<CleanupSystem>();
	scene.CreateSystem<InfoSystem>();*/
	//scene.CreateSystem<BehaviourSystem>(L);
	//luaL_dofile(L, "sceneDemo.lua");
	
	//int entity = scene.CreateEntity();
	
	for (int i = 0; i < 20; i++)
	{
		scene.UpdateSystems(1);
	}

	//rayLib raylib;
	//raylib.run();

	gameloop mazegame;
	mazegame.run(L);

	bool running = true;
	while (!running)
	{
		//Update game
		//Render game
	}

	consoleThread.detach();
	
	return 0;
}