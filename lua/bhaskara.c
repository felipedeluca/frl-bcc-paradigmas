/*
    Lua and C integration example for my Computer Science Classes.
    References:
        https://nachtimwald.com/2014/07/26/calling-lua-from-c/
        https://www.cs.usfca.edu/~galles/cs420/lecture/LuaLectures/LuaAndC.html
        https://www.lua.org/ftp/
*/

#include <stdio.h>
#include <lua/lua.h>
#include <lua/lauxlib.h>
#include <lua/lualib.h>

int main(int argc, char **argv) {
    lua_State *L;

    // Define the coeficients of our equation.
    int a = 1;
    int b = -1;
    int c = -6;

    printf("\n-----------------------------");
    printf("\nC -> Lua integration example");
    printf("\n-----------------------------");

    printf("\n-> Finding the roots for a = %d, b = %d, c = %d", a, b, c);

    L = luaL_newstate();
    luaL_openlibs(L);
    if (luaL_dofile(L, "mlib.lua")) {
        printf("Could not load file: %sn", lua_tostring(L, -1));
        lua_close(L);
        return 0;
    }

    // Retrieve the function
    lua_getglobal(L, "bhaskara");

    // Set function arguments
    lua_pushnumber(L, a);
    lua_pushnumber(L, b);
    lua_pushnumber(L, c);

    // Execute function
    lua_call(L, 3, 2);

    // Retireve results
    float x1 = (float)lua_tonumber(L, -1);
    float x2 = (float)lua_tonumber(L, -2);

    // Print the two roots found using Bhaskara 
    printf("X1 = %0.f\n", x1);
    printf("X2 = %0.f\n", x2);
    printf("\n");

    lua_close(L);
    return 0;
}