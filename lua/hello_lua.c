/*
    Lua and C integration example for my Computer Science Classes.
    References:
        https://medium.com/@imwithye/interfacing-lua-with-c-92a1067435ab
        https://www.lua.org/ftp/
*/

#include <lua/lauxlib.h>
#include <lua/lualib.h>
#include <lua/lua.h>
#include <string.h>

#include <stdio.h>


static int talk(lua_State *L) {
    const char *fromLua = luaL_checkstring(L, 1);

    if (strcmp(fromLua, "msg_hello_from_lua") == 0) {
        const char *response = "msg_response_from_c";
        printf("C: Hello Lua! I'm fine, thanks!");
        printf("\nC: And you?");
        lua_pushstring(L, response);
        return 1;
    }
    else if (strcmp(fromLua, "msg_bye_from_lua") == 0) {
        const char *response = "msg_bye_from_c";
        printf("C: Sure. Bye!");
        lua_pushstring(L, response);
        return 1;        
    }

    return 0;
}


static const luaL_Reg t[] = {
    {"talk", talk},
    {NULL, NULL}
};


LUAMOD_API int luaopen_hello_lua(lua_State *L) {
    luaL_newlib(L, t);
    return 1;
}