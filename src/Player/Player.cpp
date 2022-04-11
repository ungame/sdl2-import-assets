#include "Player.hpp"

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include "Animation.hpp"
#include "Asset.hpp"
#include "Input.hpp"
#include "Settings.hpp"

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

    Animation* idle = new Animation("idle", idleSprites, 0.1, true);
    _animations[idle->GetName()] = idle;
    _currentAnimation = idle->GetName();

    SpriteSheet* startRunSprites = new SpriteSheet();
    startRunSprites->Add(SDL_Rect{640, 32, 19, 46});
    startRunSprites->Add(SDL_Rect{741, 31, 22, 47});

    Animation* startRun = new Animation("start_run", startRunSprites, 0.1, false);
    _animations[startRun->GetName()] = startRun;

    SpriteSheet* runSprites = new SpriteSheet();
    runSprites->Add(SDL_Rect{33, 111, 38, 47});
    runSprites->Add(SDL_Rect{132, 111, 40, 46});
    runSprites->Add(SDL_Rect{234, 111, 38, 45});
    runSprites->Add(SDL_Rect{338, 114, 28, 44});
    runSprites->Add(SDL_Rect{432, 114, 38, 44});
    runSprites->Add(SDL_Rect{530, 114, 39, 43});
    runSprites->Add(SDL_Rect{634, 113, 32, 45});
    runSprites->Add(SDL_Rect{739, 113, 31, 45});

    Animation* run = new Animation("run", runSprites, 0.1, true);
    _animations[run->GetName()] = run;

    SpriteSheet* stopRunSprites = new SpriteSheet();
    stopRunSprites->Add(SDL_Rect{40, 194, 19, 44});
    stopRunSprites->Add(SDL_Rect{137, 193, 23, 45});

    Animation* stopRun = new Animation("stop_run", stopRunSprites, 0.1, false);
    _animations[stopRun->GetName()] = stopRun;
}

void Player::Update()
{
    _direction.x = 0;

    if(Input::Instance()->KeyPressed(SDL_SCANCODE_RIGHT))
    {
        _direction.x = 1;
        _flip = SDL_FLIP_NONE;
    }

    if(Input::Instance()->KeyPressed(SDL_SCANCODE_LEFT))
    {
        _direction.x = -1;
        _flip = SDL_FLIP_HORIZONTAL;
    }

    if(Input::Instance()->KeyPressed(SDL_SCANCODE_1))
    {
        _animations[_currentAnimation]->Reset();
        _currentAnimation = "idle";
    }

    if(Input::Instance()->KeyPressed(SDL_SCANCODE_2))
    {
        _animations[_currentAnimation]->Reset();
        _currentAnimation = "start_run";
    }

    if(Input::Instance()->KeyPressed(SDL_SCANCODE_3))
    {
        _animations[_currentAnimation]->Reset();
        _currentAnimation = "run";
    }

    if(Input::Instance()->KeyPressed(SDL_SCANCODE_4))
    {
        _animations[_currentAnimation]->Reset();
        _currentAnimation = "stop_run";
    }

    _position.x += _direction.x * PLAYER_SPEED;

    HandleCollisions();

    _animations[_currentAnimation]->Animate();
}

void Player::Draw(SDL_Renderer* renderer)
{
    SDL_Rect frame = _animations[_currentAnimation]->GetFrame();
    SDL_Rect rect = GetRect();

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_TRANSPARENT);
    SDL_RenderDrawRect(renderer, &rect);

    _asset->Draw(renderer, &frame, rect.x, rect.y, _scale, _flip);
}

SDL_Rect Player::GetRect()
{
    SDL_Rect frame = _animations[_currentAnimation]->GetFrame();

    int w = (frame.w * _scale);
    int h = (frame.h * _scale);
    int x = _position.x - w;
    int y = _position.y - h;

    return SDL_Rect{ x, y, w, h };
}

void Player::HandleCollisions()
{
    SDL_Rect rect = GetRect();

    if(rect.x < 0)
        _position.x = rect.w;

    if(rect.x + rect.w > SCREEN_WIDTH)
        _position.x = SCREEN_WIDTH;

    if(rect.y > SCREEN_HEIGHT)
        _position.y = SCREEN_HEIGHT;
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