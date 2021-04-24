#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, int screenWidth, int screenHeight, const char* windowTitle) ;

void quitSDL(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* Gameover, SDL_Surface* ScreenSurface);

void waitUntilKeyPressed();

void renderText(const string &msg, SDL_Color color, SDL_Renderer *ren, int x, int y, const char* font_file, int size);

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);

#endif // SDL_UTILS_H
