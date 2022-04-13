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

#define FPS 1000 / 60

const char* WINDOW_TITLE = "SDL2 IMPORT ASSETS";

void setWindowTitle(SDL_Window* window);
void safeQuit(SDL_Window* window, SDL_Renderer* renderer);

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

    Asset* asset = new Asset(renderer, "assets/PrototypeHero.png");

    if(asset->HasError())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "asset error: %s", asset->GetError());

        delete asset;

        safeQuit(window, renderer);

        return EXIT_FAILURE;
    }

    Player* player = new Player(asset, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 3);


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

        if(asset->HasError())
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "error on draw: %s", asset->GetError());

            break;
        }
        
        SDL_RenderPresent(renderer);

        frameTime = SDL_GetTicks64() - lastFrame;
        lastFrame = SDL_GetTicks64();

        if(FPS > frameTime)
            SDL_Delay(FPS - frameTime);
    }

    delete player;
    delete asset;

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