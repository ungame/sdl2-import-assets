#ifndef SPRITESHEET_HPP
#define SPRITESHEET_HPP

#include <vector>
#include <SDL2/SDL.h>

class SpriteSheet
{
    private:
        std::vector<SDL_Rect> _sprites;

    public:
        SpriteSheet() {}
        ~SpriteSheet() { _sprites.clear(); }
        inline void Add(SDL_Rect rect) { _sprites.push_back(rect); }
        inline SDL_Rect Get(int index) { return index < Len() && index >= 0 ? _sprites[index] : SDL_Rect{}; }
        inline int Len() { return _sprites.size(); }
};

#endif