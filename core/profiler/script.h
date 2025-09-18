#pragma once

#include <windows.h>
#include <lua.hpp>
#include <vector>
#include <string>
#include <cstdio>
#include <string>
#include <unordered_map>
#include "../window/window.h"
#include "../input/keys.h"
#include "../input/mouse.h"
#include "sound.h"

struct LuaObject {
    std::string texture;
    float pos[3];
    float scale[3];
    float rotate[3];
    float color[3];
};

int lua_print_hello(lua_State* L) {
    return 0;
}

// Функции для работы со звуком в Lua
int lua_sound_play(lua_State* L) {
    const char* soundName = luaL_checkstring(L, 1);
    // Вместо поиска по имени, просто воспроизводим звук по имени
    AudioEngine::getInstance().playSound(soundName);
    return 0;
}

int lua_sound_stop(lua_State* L) {
    const char* soundName = luaL_checkstring(L, 1);
    // Ищем источник по имени и останавливаем
    ALuint source = AudioEngine::getInstance().getSourceByName(soundName);
    if (source != 0) {
        AudioEngine::getInstance().stopSound(source);
    }
    return 0;
}

int lua_sound_set_volume(lua_State* L) {
    const char* soundName = luaL_checkstring(L, 1);
    float volume = (float)luaL_checknumber(L, 2);
    
    // Ищем источник по имени и устанавливаем громкость
    ALuint source = AudioEngine::getInstance().getSourceByName(soundName);
    if (source != 0) {
        alSourcef(source, AL_GAIN, volume);
    }
    return 0;
}

int lua_sound_load(lua_State* L) {
    const char* filename = luaL_checkstring(L, 1);
    const char* soundName = luaL_checkstring(L, 2);
    
    // Проверка существования файла
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Sound file not found: %s\n", filename);
        lua_pushboolean(L, false);
        return 1;
    }
    fclose(file);
    
    bool success = AudioEngine::getInstance().loadSound(filename, soundName);
    lua_pushboolean(L, success);
    return 1;
}

int lua_sound_create_source(lua_State* L) {
    const char* soundName = luaL_checkstring(L, 1);
    bool looping = lua_toboolean(L, 2);
    float volume = (float)luaL_optnumber(L, 3, 1.0);
    float pitch = (float)luaL_optnumber(L, 4, 1.0);
    
    ALuint source = AudioEngine::getInstance().createSource(soundName, looping, volume, pitch);
    lua_pushinteger(L, source);
    return 1;
}

int lua_sound_is_playing(lua_State* L) {
    const char* soundName = luaL_checkstring(L, 1);
    
    // Ищем источник по имени и проверяем состояние
    ALuint source = AudioEngine::getInstance().getSourceByName(soundName);
    if (source != 0) {
        ALint state;
        alGetSourcei(source, AL_SOURCE_STATE, &state);
        lua_pushboolean(L, state == AL_PLAYING);
    } else {
        lua_pushboolean(L, false);
    }
    return 1;
}

class LuaEngine {
private:
    lua_State* file;

public:
    LuaEngine() {
        file = luaL_newstate();

        if (!file) {
            printf("Error: Cannot create Lua state\n");
            exit(-1);
        }

        luaL_openlibs(file);
        registerSoundFunctions();
        registerUtilsModule();
        
        // Добавьте пути поиска для Lua модулей
        const char* package_path = "package.path = package.path .. ';./lua/?.lua;./?.lua;./BBE/?.lua'";
        if (luaL_dostring(file, package_path) != LUA_OK) {
            printf("Failed to set package path: %s\n", lua_tostring(file, -1));
            lua_pop(file, 1);
        }
    }

    void registerSoundFunctions() {
        lua_register(file, "sound_play", lua_sound_play);
        lua_register(file, "sound_stop", lua_sound_stop);
        lua_register(file, "sound_set_volume", lua_sound_set_volume);
        lua_register(file, "sound_load", lua_sound_load);
        lua_register(file, "sound_create_source", lua_sound_create_source);
        lua_register(file, "sound_is_playing", lua_sound_is_playing);
    }

    void registerUtilsModule() {
        const char* utils_code = R"(
            local utils = {sound = {}}
            
            function utils.quit()
                os.exit()
            end
            
            function utils.sound_load(filename, name)
                return sound_load(filename, name)
            end
            
            function utils.sound_play(name)
                sound_play(name)
            end
            
            function utils.sound_stop(name)
                sound_stop(name)
            end
            
            function utils.sound_set_volume(name, volume)
                sound_set_volume(name, volume)
            end
            
            function utils.sound_create_source(name, looping, volume, pitch)
                looping = looping or false
                volume = volume or 1.0
                pitch = pitch or 1.0
                return sound_create_source(name, looping, volume, pitch)
            end
            
            function utils.sound_is_playing(name)
                return sound_is_playing(name)
            end
            
            -- Дополнительные утилиты
            function utils.print_table(t, indent)
                indent = indent or 0
                for k, v in pairs(t) do
                    local formatting = string.rep("  ", indent) .. k .. ": "
                    if type(v) == "table" then
                        print(formatting)
                        utils.print_table(v, indent + 1)
                    else
                        print(formatting .. tostring(v))
                    end
                end
            end
            
            function utils.vector3(x, y, z)
                return {x or 0, y or 0, z or 0}
            end

            function utils.distance(vec1, vec2)
                local dx = vec2[1] - vec1[1]
                local dy = vec2[2] - vec1[2]
                local dz = vec2[3] - vec1[3]
                return math.sqrt(dx * dx + dy * dy + dz * dz)
            end
            
            function utils.lerp(a, b, t)
                return a + (b - a) * math.max(0, math.min(1, t))
            end
            
            function utils.clamp(value, min, max)
                return math.max(min, math.min(max, value))
            end
            
            -- Функции для работы со временем
            utils.time = {
                delta_time = 0,
                total_time = 0,
                frame_count = 0
            }
            
            function utils.time.update(dt)
                utils.time.delta_time = dt
                utils.time.total_time = utils.time.total_time + dt
                utils.time.frame_count = utils.time.frame_count + 1
            end
            
            function utils.time.get_delta_time()
                return utils.time.delta_time
            end
            
            function utils.time.get_total_time()
                return utils.time.total_time
            end
            
            function utils.time.get_frame_count()
                return utils.time.frame_count
            end
            
            -- Функции для работы с файлами
            function utils.file_exists(filename)
                local file = io.open(filename, "r")
                if file then
                    file:close()
                    return true
                end
                return false
            end
            
            function utils.read_file(filename)
                local file = io.open(filename, "r")
                if file then
                    local content = file:read("*a")
                    file:close()
                    return content
                end
                return nil
            end
            
            function utils.write_file(filename, content)
                local file = io.open(filename, "w")
                if file then
                    file:write(content)
                    file:close()
                    return true
                end
                return false
            end
            
            package.loaded["BBE.utils"] = utils
            return utils
        )";
        
        if (luaL_dostring(file, utils_code) != LUA_OK) {
            printf("Failed to load utils module: %s\n", lua_tostring(file, -1));
            lua_pop(file, 1);
        }
    }

    void LoadFunc(const char* func) {
        lua_register(file, func, lua_print_hello);
    }

    void StartLine(const char* LuaCode) {
        if (luaL_dostring(file, LuaCode) != LUA_OK) {
            printf("Lua error: %s\n", lua_tostring(file, -1));
            lua_pop(file, 1);
        }
    }

    void LoadFile(const char* LuaFile) {
        if (luaL_dofile(file, LuaFile) != LUA_OK) {
            printf("Lua file error: %s\n", lua_tostring(file, -1));
            lua_pop(file, 1);
        }
    }

    void StartFunc(const char* func) {
        lua_getglobal(file, func);
        if (lua_isfunction(file, -1)) {
            if (lua_pcall(file, 0, 0, 0) != LUA_OK) {
                printf("Lua function error: %s\n", lua_tostring(file, -1));
                lua_pop(file, 1);
            }
        } else {
            lua_pop(file, 1);
        }
    }

    std::vector<LuaObject> getLuaObjects() {
        std::vector<LuaObject> result;
        
        lua_getglobal(file, "engine");
        if (lua_isnil(file, -1)) {
            lua_pop(file, 1);
            
            lua_getglobal(file, "package");
            lua_getfield(file, -1, "loaded");
            lua_getfield(file, -1, "BBE.engine");
            
            if (lua_isnil(file, -1)) {
                lua_pop(file, 3);
                printf("Warning: Cannot find engine table\n");
                return result;
            }
        }
        
        lua_getfield(file, -1, "objects");
        
        if (lua_istable(file, -1)) {
            lua_len(file, -1);
            int length = lua_tointeger(file, -1);
            lua_pop(file, 1);
            
            for (int i = 1; i <= length; i++) {
                lua_rawgeti(file, -1, i);
                
                if (lua_istable(file, -1)) {
                    LuaObject obj;
                    
                    lua_rawgeti(file, -1, 1);
                    if (!lua_isnil(file, -1)) {
                        obj.texture = lua_tostring(file, -1);
                    }
                    lua_pop(file, 1);
                    
                    lua_rawgeti(file, -1, 2);
                    if (lua_istable(file, -1)) {
                        for (int j = 1; j <= 3; j++) {
                            lua_rawgeti(file, -1, j);
                            obj.pos[j-1] = (float)lua_tonumber(file, -1);
                            lua_pop(file, 1);
                        }
                    }
                    lua_pop(file, 1);
                    
                    lua_rawgeti(file, -1, 3);
                    if (lua_istable(file, -1)) {
                        for (int j = 1; j <= 3; j++) {
                            lua_rawgeti(file, -1, j);
                            obj.scale[j-1] = (float)lua_tonumber(file, -1);
                            lua_pop(file, 1);
                        }
                    }
                    lua_pop(file, 1);
                    
                    lua_rawgeti(file, -1, 4);
                    if (lua_istable(file, -1)) {
                        for (int j = 1; j <= 3; j++) {
                            lua_rawgeti(file, -1, j);
                            obj.rotate[j-1] = (float)lua_tonumber(file, -1);
                            lua_pop(file, 1);
                        }
                    }
                    lua_pop(file, 1);
                    
                    lua_rawgeti(file, -1, 5);
                    if (lua_istable(file, -1)) {
                        for (int j = 1; j <= 3; j++) {
                            lua_rawgeti(file, -1, j);
                            obj.color[j-1] = (float)lua_tonumber(file, -1);
                            lua_pop(file, 1);
                        }
                    }
                    lua_pop(file, 1);
                    
                    result.push_back(obj);
                }
                lua_pop(file, 1);
            }
        }
        lua_pop(file, 1);
        
        if (lua_gettop(file) >= 2) {
            lua_pop(file, 2);
        }
        
        return result;
    }

    void input(UlightWindow window) {
        lua_getglobal(file, "package");
        lua_getfield(file, -1, "loaded");
        lua_getfield(file, -1, "BBE.input");

        if (lua_isnil(file, -1)) {
            lua_pop(file, 3);
            printf("Warning: BBE.input module not found\n");
            return;
        }

        lua_getfield(file, -1, "keys");
        if (lua_isnil(file, -1)) {
            lua_pop(file, 1);
            lua_newtable(file);
            lua_setfield(file, -2, "keys");
            lua_getfield(file, -1, "keys");
        }

        const std::vector<std::pair<int, const char*>> keyList = {
            {keys::Q, "Q"}, {keys::W, "W"}, {keys::E, "E"}, {keys::R, "R"},
            {keys::T, "T"}, {keys::Y, "Y"}, {keys::U, "U"}, {keys::I, "I"},
            {keys::O, "O"}, {keys::P, "P"}, {keys::A, "A"}, {keys::S, "S"},
            {keys::D, "D"}, {keys::F, "F"}, {keys::G, "G"}, {keys::H, "H"},
            {keys::J, "J"}, {keys::K, "K"}, {keys::L, "L"}, {keys::Z, "Z"},
            {keys::X, "X"}, {keys::C, "C"}, {keys::V, "V"}, {keys::B, "B"},
            {keys::N, "N"}, {keys::M, "M"}, {keys::F1, "F1"}, {keys::F2, "F2"},
            {keys::F3, "F3"}, {keys::F4, "F4"}, {keys::F5, "F5"}, {keys::F6, "F6"},
            {keys::F7, "F7"}, {keys::F8, "F8"}, {keys::F9, "F9"}, {keys::F10, "F10"},
            {keys::F11, "F11"}, {keys::F12, "F12"}, {keys::LCTRL, "LCTRL"},
            {keys::RCTRL, "RCTRL"}, {keys::LSHIFT, "LSHIFT"}, {keys::RSHIFT, "RSHIFT"},
            {keys::LALT, "LALT"}, {keys::RALT, "RALT"}, {keys::TAB, "TAB"},
            {keys::SPACE, "SPACE"}, {keys::ENTER, "ENTER"}, {keys::ESC, "ESC"}
        };

        for (const auto& key : keyList) {
            int state = glfwGetKey(window, key.first);
            bool isPressed = (state == GLFW_PRESS);

            lua_pushboolean(file, isPressed);
            lua_setfield(file, -2, key.second);
        }

        lua_pop(file, 3);
    }

    std::array<float, 3> GetBackgroundColor() {
        std::array<float, 3> rgb = {0, 0, 0};

        lua_getglobal(file, "package");
        lua_getfield(file, -1, "loaded");
        lua_getfield(file, -1, "BBE.config");

        if (lua_istable(file, -1)) {
            lua_getfield(file, -1, "background");

            if (lua_istable(file, -1) && lua_rawlen(file, -1) >= 3) {
                for (int i = 0; i < 3; i++) {
                    lua_rawgeti(file, -1, i+1);
                    if (lua_isnumber(file, -1)) {
                        rgb[i] = (int)lua_tonumber(file, -1) / 255.0f;
                    }
                    lua_pop(file, 1);
                }
            }
            lua_pop(file, 1);
        }

        return rgb;
    }

    void close() {
        if (file) {
            lua_close(file);
            file = nullptr;
        }
    }
};
