#include "load_Image.h"

void Renderer_image(SDL_Surface* ScreenSurface,SDL_Surface* Gameover,SDL_Window* window, char *file_name)
{
    ScreenSurface = SDL_GetWindowSurface(window);
    Gameover = IMG_Load(file_name);
    SDL_BlitSurface(Gameover, NULL, ScreenSurface, NULL);
    SDL_UpdateWindowSurface(window);
}


