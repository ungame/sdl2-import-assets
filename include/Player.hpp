#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include "Animation.hpp"
#include "Asset.hpp"

#define PLAYER_SPEED 8.0F
#define JUMP_FORCE -16.0F
#define GRAVITY 0.8F

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
        bool _onGround;

    public:
        Player(Asset* asset, float x, float y, int scale = 1);
        ~Player();
        void Update();
        void Draw(SDL_Renderer* renderer);
        SDL_Rect GetRect();
        void HandleCollisions();
        void ApplyGravity();
};

#endif