#include "SDL_utils.h"

void logSDLError(std::ostream& os, const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, int screenWidth, int screenHeight, const char* windowTitle)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);

    TTF_Init();
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* Gameover, SDL_Surface* ScreenSurface)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_FreeSurface(Gameover);
	SDL_FreeSurface(ScreenSurface);
    TTF_Quit();
	SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

void renderText(const string &msg, SDL_Color color, SDL_Renderer *ren, int x, int y, const char * font_file, int size)
{
    TTF_Font *font = TTF_OpenFont(font_file, size);
    SDL_Surface *suf= TTF_RenderText_Solid(font, msg.c_str(), color);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, suf);
    TTF_CloseFont(font);
    SDL_Rect rect;
    rect.h = suf->h;
    rect.w = suf->w;
    rect.x = x;
    rect.y = y;
    SDL_FreeSurface(suf);
    SDL_RenderCopy(ren, tex, NULL, &rect);
}

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren)
{

	SDL_Texture *texture = nullptr;

	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());

	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);

		if (texture == nullptr){
			logSDLError(std::cout, "CreateTextureFromSurface");
		}
	}
	else {
		logSDLError(std::cout, "LoadBMP");
	}
	return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{

	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
    dst.w = w;
    dst.h = h;

	SDL_RenderCopy(ren, tex, NULL, &dst);
}

