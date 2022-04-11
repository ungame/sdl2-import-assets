#include "Animation.hpp"

#include <string>
#include "Time.hpp"
#include "SpriteSheet.hpp"
#include "Asset.hpp"

Animation::Animation(std::string name, SpriteSheet* sprites, double frameInterval, bool repeat)
{
    _name = name;
    _sprites = sprites;
    _frameInterval = frameInterval;
    _repeat = repeat;
    _currentFrame = 0;
    _frameStarted = nullptr;
    _started = false;
    _completedAnimations = 0;
}

void Animation::Animate()
{
    if(!_started)
    {
        _started = true;
        _frameStarted = new Time();
    }

    next();
}

void Animation::next()
{

    double elapsed = Time::Since(_frameStarted);

    // SDL_Log("Animation: Name=%s, CurrentFrame=%d, Elapsed=%lf, Repeat=%s, CompletedAnimations=%d", _name.c_str(), 
    // _currentFrame, elapsed, _repeat ? "True" : "False", _completedAnimations);

    if(elapsed < _frameInterval)
        return;

    if(_currentFrame >= _sprites->Len() - 1)
    {
        if(_repeat)
        {
            _currentFrame = 0;
            _completedAnimations++;
        }
        else if(_completedAnimations == 0)
        {
            _completedAnimations = 1;
        }
    }
    else
    {
        _currentFrame++;
    }

    _frameStarted = new Time();

    // SDL_Log("Animation: Name=%s, CurrentFrame=%d, Elapsed=%lf, Repeat=%s, CompletedAnimations=%d", _name.c_str(), 
    //     _currentFrame, elapsed, _repeat ? "True" : "False", _completedAnimations);
}

void Animation::Reset()
{
    _currentFrame = 0;
    _frameStarted = nullptr;
    _started = false; 
    _completedAnimations = 0;
    delete _frameStarted;  
}

Animation::~Animation()
{
    delete _frameStarted;
    delete _sprites;
}