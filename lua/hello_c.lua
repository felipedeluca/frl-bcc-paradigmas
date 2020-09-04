local hello_lua = require "hello_lua"
print("\nATENTION!! We caught a silly conversation between Lua and C. Just watch!!\n");
print("\nLua: Hello C! How are you doing?");
local conversation = hello_lua.talk("msg_hello_from_lua");

if (not(conversation == null))
then
    if (conversation == "msg_response_from_c")
    then
        print("\nLua: I'm fine. Thanks for asking!");
        print("\nLua: Well, gotta go now! Bye!");
        local bye = hello_lua.talk("msg_bye_from_lua");
        if (bye == "msg_bye_from_c")
        then
            print("\nLua: See ya!\n");
        end
    end
end
