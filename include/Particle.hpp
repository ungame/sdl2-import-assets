#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SDL2/SDL.h>
#include "Asset.hpp"
#include "SpriteSheet.hpp"
#include "Animation.hpp"

class Particle
{
    private:
        Asset* _asset;
        SDL_FPoint _position;
        Animation* _animation;
        int _scale;
        SDL_RendererFlip _flip;

    public:
        Particle(Asset* asset, SpriteSheet* sprites, float x, float y, double frameDuration, int scale = 1);
        ~Particle();
        void Update(SDL_RendererFlip flip = SDL_FLIP_NONE);
        void Draw(SDL_Renderer* renderer);
        
    public:
        inline bool IsFinished() { return _animation->GetCompletedAnimations() >= 1; }

};

#endif
