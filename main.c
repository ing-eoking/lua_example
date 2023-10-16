#include <stdio.h>
#include <stdlib.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

int main(int argc, char **argv){
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dofile(L, "Hello.lua");
    return 0;
}
