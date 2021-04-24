#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "SDL_utils.h"
#include "load_Image.h"

void End_Menu(SDL_Renderer *renderer, const string & count);

void Start_Menu(SDL_Renderer *renderer, bool &play, bool &menu, bool &running, bool &in_game);

void Menu(bool &play, bool &menu, bool &running, bool &in_game);


#endif // GAME_H_INCLUDED
