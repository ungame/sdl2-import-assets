#ifndef ASSET_HPP
#define ASSET_HPP

#include <SDL2/SDL.h>
#include "Error.hpp"

class Asset
{
    private:
        SDL_Surface* _surface;
        SDL_Texture* _texture;
        Error* _error;

    public:
        Asset(SDL_Renderer* renderer, const char* filePath);
        ~Asset();
        void Draw(SDL_Renderer* renderer, SDL_Rect* frame, int x, int y, int scale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);

    public:
        inline SDL_Surface* GetSurface() { return _surface; }
        inline SDL_Texture* GetTexture() { return _texture; }
        
        inline int GetWidth() { return _surface != nullptr ? _surface->w : 0; }
        inline int GetHeight() { return _surface != nullptr ? _surface->h : 0; }

        inline bool HasError() { return _error != nullptr ? _error->HasError() : false; }
        inline const char* GetError() { return _error != nullptr ? _error->String() : ""; }
};

#endif