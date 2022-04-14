#include "Particle.hpp"

#include <SDL2/SDL.h>
#include "Asset.hpp"
#include "SpriteSheet.hpp"
#include "Animation.hpp"

Particle::Particle(Asset* asset, SpriteSheet* sprites, float x, float y, double frameDuration, int scale)
{
    _asset = asset;
    _position = { x, y };
    _animation = new Animation("particle", sprites, frameDuration, false);
    _scale = scale;
    _flip = SDL_FLIP_NONE;
}

void Particle::Update(SDL_RendererFlip flip)
{
    _flip = flip;
    _animation->Animate();
}

void Particle::Draw(SDL_Renderer* renderer)
{
    SDL_Rect frame = _animation->GetFrame();
    _asset->Draw(renderer, &frame, _position.x, _position.y, _scale, _flip);
}

Particle::~Particle()
{
    delete _animation;
    SDL_Log("Particle destroyed.");
}