#include <string>
#include <memory>
#include <fstream>
#include <sstream>

#include <lualib.h>
#include <luacode.h>

int unsafe_loadbytecode(lua_State* L) 
{
	size_t len;
	const char* data = luaL_checklstring(L, 1, &len);
	const char* chunkName = luaL_optstring(L, 2, "");

	luau_load(L, chunkName, data, len, 0);
	return 1;
}

static const luaL_Reg unsafelib[] = 
{
	{"loadbytecode", unsafe_loadbytecode},
	{NULL, NULL},
};

std::string runsource(lua_State* L, std::string source) {
	size_t bytecodeSize = 0;
	char* bytecode = luau_compile(source.data(), source.size(), NULL, &bytecodeSize);
	int result = luau_load(L, "LuauCTF", bytecode, bytecodeSize, 0);
	free(bytecode);

	if (result != 0) {
		size_t len;
		const char* msg = lua_tolstring(L, -1, &len);

		std::string error(msg, len);
		lua_pop(L, 1);
		return error;
	}

	result = lua_resume(L, nullptr, 0);

	if (result == 0) {
		return "script exited successfully";
	}
	else {
		std::string error;

		if (result == LUA_YIELD) {
			error = "script thread yielded unexpectedly";
		}
		else if (const char* str = lua_tostring(L, -1)) {
			error = str;
		}

		error += "\nstacktrace:\n";
		error += lua_debugtrace(L);
		return error;
	}

	return "unexpected fallthrough";
}

int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("usage: %s <filename>\n", argv[0]);
		return 1;
	}

	std::ifstream fileStream(argv[1]);
	if (!fileStream) {
		printf("error opening file: %s", argv[1]);
		return 1;
	}

	std::ostringstream stream;
	stream << fileStream.rdbuf();
	std::string scriptSource = stream.str();

	std::unique_ptr<lua_State, void(*)(lua_State*)> state{ luaL_newstate(), lua_close };
	lua_State* L = state.get();

	luaL_openlibs(L);
	luaL_register(L, "unsafe", unsafelib);
	luaL_sandbox(L);
	luaL_sandboxthread(L);

	puts("running file");
	puts("-------------------------------");
	std::string result_message = runsource(L, scriptSource);
	puts("-------------------------------");
	puts(result_message.c_str());

    return 0;
}
