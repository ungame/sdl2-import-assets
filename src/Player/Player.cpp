#include "Player.hpp"

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include "Animation.hpp"
#include "Asset.hpp"
#include "Input.hpp"

Player::Player(Asset* asset, float x, float y, int scale)
{
    _asset = asset;
    _position = { x, y };
    _direction = { 0, 0 };
    _scale = scale;
    _flip = SDL_FLIP_NONE;

    SpriteSheet* idleSprites = new SpriteSheet();
    idleSprites->Add(SDL_Rect{39, 32, 20, 46});
    idleSprites->Add(SDL_Rect{139, 33, 20, 45});
    idleSprites->Add(SDL_Rect{239, 33, 20, 45});
    idleSprites->Add(SDL_Rect{339, 33, 20, 45});
    idleSprites->Add(SDL_Rect{439, 32, 20, 46});
    idleSprites->Add(SDL_Rect{539, 32, 20, 46});

    Animation* idle = new Animation("idle", idleSprites, 0.1, false);
    _animations[idle->GetName()] = idle;
    _currentAnimation = idle->GetName();
}

void Player::Update()
{
    _direction.x = 0;

    if(Input::Instance()->KeyPressed(SDL_SCANCODE_RIGHT))
        _direction.x = 1;

    if(Input::Instance()->KeyPressed(SDL_SCANCODE_LEFT))
        _direction.x = -1;

    _position.x += _direction.x * PLAYER_SPEED;

    if(_animations[_currentAnimation]->GetCompletedAnimations() == 1)
        _animations[_currentAnimation]->Reset();

    _animations[_currentAnimation]->Animate();
}

void Player::Draw(SDL_Renderer* renderer)
{
    SDL_Rect frame = _animations[_currentAnimation]->GetFrame();

    int w = (frame.w * _scale);
    int h = (frame.h * _scale);
    int x = _position.x - w;
    int y = _position.y - h;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_TRANSPARENT);
    SDL_Rect border = { x, y, w, h };
    SDL_RenderDrawRect(renderer, &border);

    _asset->Draw(renderer, &frame, x, y, _scale, _flip);
}

Player::~Player()
{
    std::map<std::string, Animation*>::iterator it = _animations.begin();

    while(it != _animations.end())
    {
        delete it->second;
        it++;
    }
    _animations.clear();
}