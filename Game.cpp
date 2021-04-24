#include "Game.h"

void End_Menu(SDL_Renderer * renderer, const string & count)
{
    SDL_Color color = {200, 0 ,0};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    renderText("SCORE:",color, renderer, 300, 150, "Score.ttf",80);
    renderText("Game Over",color, renderer, 270, 250, "Score.ttf",80);
    renderText(count,color, renderer, 570, 150,"Score.ttf",80);
    SDL_RenderPresent(renderer);
}

void Start_Menu(SDL_Renderer *renderer, bool &play, bool &menu ,bool &running, bool &in_game)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0,255);
    SDL_RenderClear(renderer);
    SDL_Color color_Score = {255, 0, 0};
    SDL_Color color = {0, 0, 0};
    renderText("SNAKE GAME",color, renderer, 160, 100,"snake.ttf",100);
    renderText("PLAY GAME = 1",color_Score, renderer, 210, 250, "Score.ttf",70);
    renderText("QUIT GAME = 2",color_Score, renderer, 210, 350, "Score.ttf",70);
    SDL_RenderPresent(renderer);
    Menu(play, menu , running , in_game);
}

void Menu(bool &play, bool &menu, bool &running, bool &in_game)
{
    SDL_Event e;
    while (true) {
        SDL_Delay(10);
        if ( SDL_WaitEvent(&e) == 0) continue;

        if (e.type == SDL_QUIT) break;

        if (e.type == SDL_KEYDOWN) {

            if (e.key.keysym.sym == SDLK_ESCAPE) break;

            if (e.key.keysym.sym == SDLK_1)
            {
                play = true;
                running = true;
                in_game = true;
                menu = false;
                return;
            }
            if (e.key.keysym.sym == SDLK_2)
            {
                play = false;
                running = false;
                in_game = false;
                menu = false;
                return;
            }
        }
        if (e.type = SDL_MOUSEBUTTONDOWN)
        {

        }
    }
}


