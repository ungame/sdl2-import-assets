#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Settings.hpp"
#include "Time.hpp"
#include "Input.hpp"
#include "Asset.hpp"
#include "SpriteSheet.hpp"
#include "Animation.hpp"
#include "Player.hpp"
#include "Particle.hpp"

#define FPS 1000 / 60

const char* WINDOW_TITLE = "SDL2 IMPORT ASSETS";

void setWindowTitle(SDL_Window* window);
void safeQuit(SDL_Window* window, SDL_Renderer* renderer);

Particle* DustOnStopRun(Asset* asset);
Particle* DustOnJump(Asset* asset);
Particle* DustOnGround(Asset* asset);

int main(int argc, char* argv[])
{

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl unable to init: %s", SDL_GetError());

        return EXIT_FAILURE;
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    int imgInitted = IMG_Init(imgFlags);

    if((imgInitted&imgFlags) != imgFlags)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "img unable to init: %s", IMG_GetError());

        safeQuit(nullptr, nullptr);

        return EXIT_FAILURE;
    }

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(window == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl unable to create window: %s", SDL_GetError());

        safeQuit(nullptr, nullptr);

        return EXIT_FAILURE;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl unable to create renderer: %s", SDL_GetError());

        safeQuit(window, nullptr);

        return EXIT_FAILURE;
    }

    Asset* playerAsset = new Asset(renderer, "assets/PrototypeHero.png");

    if(playerAsset->HasError())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "player asset error: %s", playerAsset->GetError());

        delete playerAsset;

        safeQuit(window, renderer);

        return EXIT_FAILURE;
    }

    Player* player = new Player(playerAsset, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 3);

    Asset* dustAsset = new Asset(renderer, "assets/Dust.png");

    if(dustAsset->HasError())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "dust asset error: %s", dustAsset->GetError());

        delete dustAsset;

        safeQuit(window, renderer);

        return EXIT_FAILURE;
    }

    Particle* dustOnStopRun = DustOnStopRun(dustAsset);
    Particle* dustOnJump = DustOnJump(dustAsset);
    Particle* dustOnGround = DustOnGround(dustAsset);

    float lastFrame = SDL_GetTicks64();
    float frameTime = SDL_GetTicks64() - lastFrame;

    bool running = true;

    while(running)
    {
        running = Input::Instance()->Listen();

        if(running && Input::Instance()->KeyPressed(SDL_SCANCODE_ESCAPE))
            running = false;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
        SDL_RenderClear(renderer);
        
        setWindowTitle(window);

        player->Update();
        player->Draw(renderer);

        if(playerAsset->HasError())
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "error on draw player: %s", playerAsset->GetError());

            break;
        }

        dustOnStopRun->Update();
        dustOnStopRun->Draw(renderer);

        dustOnJump->Update();
        dustOnJump->Draw(renderer);

        dustOnGround->Update();
        dustOnGround->Draw(renderer);

        if(dustAsset->HasError())
        {
           SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "error on draw dust: %s", dustAsset->GetError());

            break;
        }

        if(dustOnStopRun->IsFinished())
        {
            delete dustOnStopRun;
            dustOnStopRun = DustOnStopRun(dustAsset);
        }

        if(dustOnJump->IsFinished())
        {
            delete dustOnJump;
            dustOnJump = DustOnJump(dustAsset);
        }

        if(dustOnGround->IsFinished())
        {
            delete dustOnGround;
            dustOnGround = DustOnGround(dustAsset);
        }
        
        SDL_RenderPresent(renderer);

        frameTime = SDL_GetTicks64() - lastFrame;
        lastFrame = SDL_GetTicks64();

        if(FPS > frameTime)
            SDL_Delay(FPS - frameTime);
    }

    delete dustOnStopRun;
    delete dustAsset;
    delete player;
    delete playerAsset;

    safeQuit(window, renderer);

    return EXIT_SUCCESS;
}

void setWindowTitle(SDL_Window* window)
{
    std::string title = std::string(WINDOW_TITLE);
    title += " | ";

    Time* time = new Time();
    title += std::string(time->String());
    title += " | ";
    delete time;

    SDL_Point cursor = Input::Instance()->GetCursor();
    title += "MX=" + std::to_string(cursor.x);
    title += " | ";
    title += "MY=" + std::to_string(cursor.y);

    SDL_SetWindowTitle(window, title.c_str());
}

void safeQuit(SDL_Window* window, SDL_Renderer* renderer)
{
    if(renderer != nullptr)
        SDL_DestroyRenderer(renderer);

    if(window != nullptr)
        SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
}

Particle* DustOnStopRun(Asset* asset)
{
    SpriteSheet* sprites = new SpriteSheet();
    sprites->Add(SDL_Rect{13, 24, 8, 6});
    sprites->Add(SDL_Rect{47, 23, 7, 5});
    sprites->Add(SDL_Rect{80, 23, 6, 4});
    sprites->Add(SDL_Rect{113, 23, 2, 3});

    Particle* particle = new Particle(asset, sprites, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.3, 5);
    
    return particle;
}

Particle* DustOnJump(Asset* asset)
{
    SpriteSheet* sprites = new SpriteSheet();
    sprites->Add(SDL_Rect{9, 52, 9, 10});
    sprites->Add(SDL_Rect{42, 50, 16, 9});
    sprites->Add(SDL_Rect{75, 48, 5, 9});

    Particle* particle = new Particle(asset, sprites, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, 0.3, 5);
    
    return particle;
}

Particle* DustOnGround(Asset* asset)
{
    SpriteSheet* sprites = new SpriteSheet();
    sprites->Add(SDL_Rect{4, 88, 26, 6});
    sprites->Add(SDL_Rect{32, 86, 31, 8});
    sprites->Add(SDL_Rect{64, 86, 31, 8});
    sprites->Add(SDL_Rect{96, 86, 31, 6});

    Particle* particle = new Particle(asset, sprites, SCREEN_WIDTH - (SCREEN_WIDTH / 3), SCREEN_HEIGHT / 2, 0.3, 5);
    
    return particle;
}