#include "Asset.hpp"

#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Error.hpp"

Asset::Asset(SDL_Renderer* renderer, const char* filePath)
{
    _texture = nullptr;
    _error = nullptr;

    _surface = IMG_Load(filePath);

    if(_surface == nullptr)
    {
        _error = new Error(IMG_GetError());
        return;
    }

    _texture = SDL_CreateTextureFromSurface(renderer, _surface);

    if(_texture == nullptr)
        _error = new Error(SDL_GetError());
}

void Asset::Draw(SDL_Renderer* renderer, SDL_Rect* frame, int x, int y, int scale, SDL_RendererFlip flip)
{
    SDL_Rect destination = { x, y, frame->w * scale, frame->h * scale };

    double angle = 0;
    SDL_Point* center = nullptr;

    if(SDL_RenderCopyEx(renderer, _texture, frame, &destination, angle, center, flip) != 0)
        _error = new Error(SDL_GetError());
}

Asset::~Asset()
{
    if(_surface != nullptr)
    {
        SDL_FreeSurface(_surface);
        SDL_Log("Surface destroyed.");
    }

    if(_texture != nullptr)
    {
        SDL_DestroyTexture(_texture);
        SDL_Log("Texture destroyed.");
    }

    if(_error != nullptr)
    {
        delete _error;
        SDL_Log("Error deleted.");
    }

}
