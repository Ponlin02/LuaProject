//scene.SetComponent<BehaviourComponent>(entity, BehaviourComponent( script, entity));


	//	for (auto entity : curedView) {
	//		float tickDamage = static_cast<float>(rand() % 10 + 1);
	//		registry.emplace<Poison>(entity, tickDamage);

	//		std::cout << "Enitty inflicted" << std::endl;
	//	}

	//entt::registry registry;
	// Create all entites and their tickdamage!

	//entt::registry registry;
	//srand(time(NULL));
	//for (int i = 0; i < 100; i++) {

	//	auto entity = registry.create();
	//	
	//	//std::cout << "Entity ID: " << (int)entity << "\n";

	//	registry.emplace<Health>(entity, 100);

	//	float tickDamage = static_cast<float>(rand() % 10 + 1); 
	//	registry.emplace<Poison>(entity, tickDamage);

	//}

	//int iterations = 0;
	//while (!registry.view<Health>().empty() && iterations < 10000)
	//{
	//	{
	//		auto view = registry.view<Health, Poison>();

	//		view.each([](Health& health, const Poison& poison) {
	//			health.Value -= poison.TickDamage;
	//			}); 
	//	}

	//	{

	//	auto view = registry.view<Health>();

	//	view.each([&](entt::entity entity, const Health& health) {
	//		if (health.Value <= 0.f)
	//		{
	//			registry.destroy(entity);
	//		}
	//		});
	//	}

	//	{
	//		float saveChance = rand() % 20;
	//		if (saveChance == 0)
	//		{
	//			registry.clear<Poison>();

	//			std::cout << "Entity Saved!" << std::endl;
	//		}

	//	}



	//	iterations++;
	//	std::cout << "Iteration " << iterations
	//		<< ", entities alive: " << registry.view<Health>().size()
	//		<< std::endl;
	//}
	//




//Vector3 vector = { 1,1,1 };

	//lua_pushvector(L, vector);

	/*lua_pushstring(L, "x");
	lua_pushnumber(L, 1);
	lua_settable(L, -3);

	lua_pushstring(L, "y");
	lua_pushnumber(L, 2);
	lua_settable(L, -3);
	DumpStack(L);

	lua_pushstring(L, "z");
	lua_pushnumber(L, 3);
	lua_settable(L, -3);
	*/
	//DumpStack(L);

	//PrintVector(L);

	/*lua_pushcfunction(L, PrintVector);
	lua_setglobal(L, "PrintVector");
	luaL_dofile(L, "vector-demo.lua");*/





	//void DumpError(lua_State* L)
	//{
	//	if (lua_gettop(L) && lua_isstring(L, -1))
	//	{
	//		std::cout << "Lua error: " << lua_tostring(L, -1) << std::endl;
	//		lua_pop(L, 1);
	//	}
	//}
	//
	//std::string GetValueString(lua_State* L, int i)
	//{
	//	switch (lua_type(L, i))
	//	{
	//	case LUA_TNIL: return "nil";
	//	case LUA_TBOOLEAN: return lua_toboolean(L, i) ? "true" : "false";
	//	case LUA_TNUMBER: return std::to_string(lua_tonumber(L, i));
	//	case LUA_TSTRING: return lua_tostring(L, i);
	//	default: return "";
	//	}
	//}
	//
	//void DumpStack(lua_State* L)
	//{
	//	int size = lua_gettop(L);
	//
	//	std::cout << "--- STACK BEGIN ---" << std::endl;
	//	for (int i = size; i > 0; i--)
	//	{
	//		std::cout << i
	//			<< "\t"
	//			<< lua_typename(L, lua_type(L, i))
	//			<< "\t\t" << GetValueString(L, i)
	//			<< std::endl;
	//	}
	//	std::cout << "--- STACK END ---" << std::endl;
	//}


	// Denna �r den enda funktionen som beh�ver windows.h
	// som inte g�r att inkludera f�r d� tjatar den

	//void ConsoleThreadFunction(lua_State* L)
	//{
	//	std::string input;
	//	while (GetConsoleWindow())
	//	{
	//		std::cout << "> ";
	//		std::getline(std::cin, input);
	//
	//		if (luaL_dostring(L, input.c_str()) != LUA_OK)
	//		{
	//			DumpError(L);
	//		}
	//	}
	//}

	//struct Vector3
	//{
	//	float X, Y, Z;
	//	Vector3(float x = 0.f, float y = 0.f, float z = 0.f) :
	//		X(x), Y(y), Z(z) { }
	//};
	//
	//struct Transform
	//{
	//	Vector3 Position;
	//	Vector3 Rotation;
	//	Vector3 Scale;
	//	Transform(Vector3 position = Vector3(), Vector3 rotation = Vector3(), Vector3 scale = Vector3()) :
	//		Position(position), Rotation(rotation), Scale(scale) {}
	//};

	//Vector3 lua_tovector(lua_State* L, int index)
	//{
	//	Vector3 vector;
	//	lua_getfield(L, index, "x");
	//	vector.X = lua_tonumber(L, -1);
	//	lua_pop(L, 1);
	//	
	//	lua_getfield(L, index, "y");
	//	vector.Y = lua_tonumber(L, -1);
	//	lua_pop(L, 1);
	//	lua_getfield(L, index, "z");
	//	vector.Z = lua_tonumber(L, -1);
	//	lua_pop(L, 1);
	//	
	//	return vector;
	//}
	//
	//static int PrintVector(lua_State* L)
	//{
	//	Vector3 hej = lua_tovector(L, -1);
	//
	//	std::cout << "[c++] Vector("
	//		<< hej.X << ", "
	//		<< hej.Y << ", "
	//		<< hej.Z << ")"
	//		<< std::endl;
	//
	//	return 0;
	//}
	//
	//static int lua_pushvector(lua_State* L, const Vector3& vector)
	//{
	//	lua_newtable(L);
	//
	//
	//	//lua_pushstring(L, "x");
	//	lua_pushnumber(L, vector.X);
	//	lua_setfield(L, -2, "x");
	//
	//	//lua_pushstring(L, "y");
	//	lua_pushnumber(L, vector.Y);
	//	lua_setfield(L, -2, "y");
	//	//DumpStack(L);
	//
	//	//lua_pushstring(L, "z");
	//	lua_pushnumber(L, vector.Z);
	//	lua_setfield(L, -2, "z");
	//
	//	return 0;
	//}
	//
	//static int lua_totransform(lua_State* L, int index) 
	//{
	//	Transform transform;
	//	lua_getfield(L, index, "position");
	//	transform.Position = lua_tovector(L, -1);
	//
	//	lua_getfield(L, index, "rotation");
	//	transform.Rotation = lua_tovector(L, -1);
	//
	//	lua_getfield(L, index, "scale");
	//	transform.Scale = lua_tovector(L, -1);
	//}
	//
	//static int lua_pushtransform(lua_State* L, Transform& transform)
	//{
	//	lua_newtable(L);
	//
	//	lua_pushvector(L, transform.Position);
	//	lua_setfield(L, -2, "position");	
	//	lua_pushvector(L, transform.Rotation);
	//	lua_setfield(L, -2, "rotation");	
	//	lua_pushvector(L, transform.Scale);
	//	lua_setfield(L, -2, "scale");
	//
	//}
