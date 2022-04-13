#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>
#include "Time.hpp"
#include "SpriteSheet.hpp"

class Animation
{
    private:
        std::string _name;
        SpriteSheet* _sprites;
        int _currentFrame;
        double _frameDuration;
        Time* _frameStarted;
        bool _started;
        bool _repeat;
        int _completedAnimations;

    public:
        Animation(std::string name, SpriteSheet* sprites, double frameDuration, bool repeat = true);
        ~Animation();
        void Animate();
        void Reset();

    public:
        inline std::string GetName() { return _name; }
        inline SDL_Rect GetFrame() { return _sprites->Get(_currentFrame); }
        inline int GetCompletedAnimations() { return _completedAnimations; }

    private:
        void next();
};

#endif