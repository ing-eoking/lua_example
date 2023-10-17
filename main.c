#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

int main(int argc, char **argv){
    lua_State* L = luaL_newstate();
    char buf[1024];
    char cmd[1024];
    luaL_openlibs(L);
    while(1){
        scanf("%s", buf);
        if(!strcmp(buf, "quit")) return 0;
        sprintf(cmd, "return %s", buf);
        luaL_dostring(L, cmd);
        printf("result : %d\n", lua_tointeger(L, -1));
    }
    lua_close(L);
    return 0;
}
