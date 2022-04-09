#ifndef INPUT_HPP
#define INPUT_HPP

#include <SDL2/SDL.h>

class Input
{
    private:
        static Input* _input;
        const Uint8* _keyboard;
        SDL_Point _cursor;

    private:
        Input() { _keyboard = SDL_GetKeyboardState(nullptr); }

    public:
        inline static Input* Instance() { return _input = _input != nullptr ? _input : new Input(); }

    public:
        bool Listen();

    public:
        inline bool KeyPressed(SDL_Scancode key) { return _keyboard[key] == 1; }
        inline SDL_Point GetCursor() { return _cursor; }
};

#endif
