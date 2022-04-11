#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include "Animation.hpp"
#include "Asset.hpp"

#define PLAYER_SPEED 8.0F

class Player
{
    private:
        Asset* _asset;
        SDL_FPoint _position;
        SDL_FPoint _direction;
        int _scale;
        SDL_RendererFlip _flip;
        std::map<std::string, Animation*> _animations;
        std::string _currentAnimation;

    public:
        Player(Asset* asset, float x, float y, int scale = 1);
        ~Player();
        void Update();
        void Draw(SDL_Renderer* renderer);
        SDL_Rect GetRect();
        void HandleCollisions();
};

#endif