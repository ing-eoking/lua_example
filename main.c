#include <stdio.h>
#include <string.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

int add(lua_State *L); int sub(lua_State *L);
int mult(lua_State *L); int div(lua_State *L); int mod(lua_State *L);

#define CALC_NUM 5

void remove_space(char *src, char *dst)
{
    while(*(src++))
        if(*(src-1) != ' ') *(dst++) = *(src-1);
    *dst = '\0';
}

void register_function(lua_State *L)
{
    int i = CALC_NUM;
    int (*calcPointer[CALC_NUM])(lua_State *L) = {add, sub, mult, div, mod};
    char *calcName[CALC_NUM] = {"add", "sub", "mult", "div", "mod"};

    lua_newtable(L);
    while(i--) {
        lua_pushstring(L, calcName[i]);
        lua_pushcfunction(L, calcPointer[i]);
        lua_settable(L, -3);
    }
    lua_setglobal(L, "calc");
}

int main(int argc, char **argv)
{
    char buf[1024], cmd[1024];
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    register_function(L);

    while(1){
        scanf("%[^\n]s", buf); getchar();
        if(!strcmp(buf, "quit")) break;
        remove_space(buf, buf);
        sprintf(cmd, "return %s", buf);
        luaL_dostring(L, cmd);
        printf("result : %.2f\n", lua_tonumber(L, -1));
    }

    lua_close(L);
    return 0;
}

int add(lua_State *L)
{
    int a = (int)lua_tointeger(L, -2);
    int b = (int)lua_tointeger(L, -1);
    lua_pushnumber(L, a + b);
    return 1;
}

int mult(lua_State *L)
{
    int a = (int)lua_tointeger(L, -2);
    int b = (int)lua_tointeger(L, -1);
    lua_pushnumber(L, a * b);
    return 1;
}

int sub(lua_State *L)
{
    int a = (int)lua_tointeger(L, -2);
    int b = (int)lua_tointeger(L, -1);
    lua_pushnumber(L, a - b);
    return 1;
}

int div(lua_State *L)
{
    float a = (float)lua_tonumber(L, -2);
    float b = (float)lua_tonumber(L, -1);
    lua_pushnumber(L, a / b);
    return 1;
}

int mod(lua_State *L)
{
    int a = (int)lua_tointeger(L, -2);
    int b = (int)lua_tointeger(L, -1);
    lua_pushnumber(L, a % b);
    return 1;
}
