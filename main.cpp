#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_utils.h"
#include "load_Image.h"
#include "Game.h"
using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface* Gameover = NULL;
SDL_Surface* ScreenSurface = NULL;

int SCREEN_WIDTH = 950;
int SCREEN_HEIGHT = 650;
int side_of_aUnit=25;

int Column_Board=SCREEN_WIDTH/side_of_aUnit, // 38 cot
    Row_Board=SCREEN_HEIGHT/side_of_aUnit;   // 26 hang

struct Point{
    int x, y;
};

enum object
{
    Snake,
    SnakeHEAD,
    Wall,
    Fruit,
    Blank
};

enum Direction
{
    Freeze,
    Up,
    Down,
    Left,
    Right
} ;

Direction old_DIRECTION=Freeze;

class snake {
public:
    Point HEAD;
    vector <Point> body;
    void event_handle(SDL_Event &event, bool &in_game, bool &running);
    void Move(Direction &old_DIRECTION, int column, int row);
    bool eatFruit(Point fruit);
    void getLonger();
    bool CRASH();
    Direction DIRECTION = Freeze;
private:
    Point old_Point;
    int body_CELL=1;
};

struct Map {
    int row, column;

    Map(int getCOL, int getROW) {
        row = getROW; column = getCOL;
    }
    Point getFruit(snake SNAKE);
    Point fruit;
    void create_Map();
    vector<vector<object>> board;
    vector<vector<object>> show_Map(snake SNAKE);
};
Map MAP(Column_Board, Row_Board);

void render_Map(vector<vector<object>> MAP, int side_of_aUnit, SDL_Renderer *ren);

void Event_Handle(bool &in_game, bool &running, snake &SNAKE);

// main
int main(int argc, char* argv[])
{

    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, "Snake handsome" );

    bool in_game = true, running = true, play = false, menu = true;
    while(menu)
    {
       Start_Menu(renderer, play , menu , running, in_game );
        if (play)
        {
            Renderer_image(ScreenSurface, Gameover, window, "loading.jpg");
            SDL_RenderClear(renderer);
            SDL_Delay(700);
            while(running) {
                snake *SNAKE = new snake;
                MAP.fruit = MAP.getFruit(*SNAKE);
                (*SNAKE).HEAD = {Column_Board/2, Row_Board/2};
                (*SNAKE).body.push_back({Column_Board/2-1, Row_Board/2});
                int count=0;
                while(in_game) {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
                    SDL_RenderClear(renderer);

                    MAP.create_Map();

                    SDL_Color color_Score = {255, 0, 0};
                    SDL_Color color = {0, 98, 65};
                    renderText("SCORE:",color_Score, renderer, 10, 570, "Score.ttf",60);
                    renderText(to_string(count),color_Score, renderer, 210, 570,"Score.ttf",60);
                    renderText("SNAKE GAME",color, renderer, 400, 570,"snake.ttf",70);

                    Event_Handle(in_game, running, *SNAKE);

                    if(SNAKE->CRASH())
                    {
                        End_Menu(renderer, to_string(count));
                        SDL_Delay(2000);
                        running = 0;
                        break;
                    }

                    if( SNAKE->eatFruit(MAP.fruit) ) {
                        SNAKE->getLonger();
                        MAP.fruit = MAP.getFruit(*SNAKE);
                        count +=1;
                    }
                    SNAKE->Move(old_DIRECTION, Column_Board, Row_Board);

                    vector<vector<object>> update_Map = MAP.show_Map(*SNAKE);

                    render_Map(update_Map, side_of_aUnit, renderer);

                    SDL_RenderPresent(renderer);

                    SDL_Delay(100);
                }
                delete SNAKE;
            }
           menu = true;
        }
        else
        {
            exit(0);
        }
    }

    quitSDL(window, renderer, Gameover, ScreenSurface);

    return 0;
}

//snake

void snake :: event_handle(SDL_Event &event, bool &in_game, bool &running)
{
    if((event).type == SDL_KEYDOWN) {
        switch( (event).key.keysym.sym )
        {
            case SDLK_UP: DIRECTION = Up; break;
            case SDLK_DOWN: DIRECTION = Down; break;
            case SDLK_LEFT: DIRECTION = Left; break;
            case SDLK_RIGHT: DIRECTION = Right; break;
            case SDLK_ESCAPE: in_game = false; running =false; break;
            default: DIRECTION = Freeze; break;
        }
    }
}

void snake::Move(Direction &old_DIRECTION, int column, int row)
{
    old_Point = HEAD;
    while(true) {
        if(DIRECTION == Right && old_DIRECTION != Left ) {
            HEAD.x = (HEAD.x + 1)% column;
            old_DIRECTION = DIRECTION; break;
        }
        else if(DIRECTION == Left && old_DIRECTION != Right) {
            HEAD.x = (column + HEAD.x -1) % column;
            old_DIRECTION = DIRECTION;  break;
        }
        else if(DIRECTION == Down && old_DIRECTION != Up) {
            HEAD.y = (HEAD.y + 1) % row;
            old_DIRECTION = DIRECTION;  break;
        }
        else if(DIRECTION == Up && old_DIRECTION != Down) {
            HEAD.y = (row + HEAD.y - 1) % row;
            old_DIRECTION = DIRECTION;  break;
        }
        else if(DIRECTION==Freeze) {
            old_DIRECTION = DIRECTION; break;
        }
        else DIRECTION = old_DIRECTION;
    }
//    body.resize(body_CELL);
    if(DIRECTION != Freeze)
        for(int i=0;i<body.size();i++) {
            Point tmp_point = body[i];
            body [i] = old_Point;
            old_Point = tmp_point;
        }
}

bool snake::eatFruit(Point fruit)
{
    if(fruit.x == HEAD.x && fruit.y == HEAD.y) return 1;
    else return 0;
}

void snake::getLonger()
{
    body_CELL++;
    body.resize(body_CELL);

}

bool snake::CRASH() {
        for(int i=0;i<body.size();i++){
        if( (HEAD.x==body[i].x && HEAD.y==body[i].y) ) {cout<<"happened"<<endl;  return 1;}
    }
    if(HEAD.x == 0 || HEAD.y == 0 || HEAD.x == Column_Board-1|| HEAD.y == Row_Board-5)
    {
        cout<<"happened"<<endl;  return 1;
    }
    return 0;
}

// Map

void Map::create_Map()
{
    board.resize(row);
    for(int i=0;i<row;i++) board[i].assign(column, Blank);
}

Point Map::getFruit(snake SNAKE)
{
    Point fruit;
    bool show_Fruit = false;
    do {
        fruit.x = rand()% ((Column_Board-3)-3 +1)+3;

        fruit.y = rand()% ((Row_Board-7)-3 +1)+3;

        for(int i=0;i<SNAKE.body.size();i++) {
            if((fruit.x == SNAKE.body[i].x && fruit.y == SNAKE.body[i].y) ||
                    (fruit.x == SNAKE.HEAD.x && fruit.y == SNAKE.HEAD.y)) {
                show_Fruit = true;
                break;
            }
        }
    }
    while(show_Fruit);
    return fruit;
}

vector<vector<object>> Map::show_Map(snake SNAKE)
{
    board[SNAKE.HEAD.y][SNAKE.HEAD.x] = SnakeHEAD;
    for(int i=0;i<SNAKE.body.size();i++) {
        board [SNAKE.body[i].y][SNAKE.body[i].x] = Snake;
    }
    board[fruit.y][fruit.x] = Fruit;

    for (int i=0; i<Row_Board-4; i++)
    {
        for (int j=0; j<Column_Board; j++)
        {
            if (i==0) board[i][j] = Wall;
            if (j==0) board[i][j] = Wall;
            if (j==Column_Board-1) board[i][j] = Wall;
            if (i==Row_Board-5) board[i][j] = Wall;

        }
    }

    return board;
}

void render_Map(vector<vector<object>> MAP, int side_of_aUnit, SDL_Renderer *ren)
{
    for(int i=0;i<MAP.size();i++) {
        for(int j=0;j<MAP[0].size();j++)
        {
            SDL_Rect rect;
            if(MAP[i][j]== Snake) {
                SDL_SetRenderDrawColor(renderer, 228, 0, 0 ,255);
                rect.x = side_of_aUnit * j;
                rect.y = side_of_aUnit * i;
                rect.h = side_of_aUnit;
                rect.w = side_of_aUnit;
                SDL_RenderFillRect (ren,&rect);
            }
            if(MAP[i][j]== Fruit) {
                SDL_SetRenderDrawColor(renderer, 0, rand()%(255-150+1)-150, 0, 0);
                rect.x = side_of_aUnit * j;
                rect.y = side_of_aUnit * i;
                rect.h = side_of_aUnit;
                rect.w = side_of_aUnit;
                SDL_RenderFillRect (renderer,&rect);
            }
            if(MAP[i][j]== SnakeHEAD) {
                SDL_Texture *image = loadTexture("HEAD.bmp", renderer);
                renderTexture(image, renderer ,side_of_aUnit * j,rect.y = side_of_aUnit * i,side_of_aUnit, side_of_aUnit);
                SDL_DestroyTexture(image);
//                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//                rect.x = side_of_aUnit * j;
//                rect.y = side_of_aUnit * i;
//                rect.h = side_of_aUnit;
//                rect.w = side_of_aUnit;
//                SDL_RenderFillRect (renderer,&rect);
            }
            if(MAP[i][j]== Wall) {
                SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255);
                rect.x = side_of_aUnit * j;
                rect.y = side_of_aUnit * i;
                rect.h = side_of_aUnit;
                rect.w = side_of_aUnit;
                SDL_RenderFillRect (renderer,&rect);
            }
        }
    }
}

// handle
void Event_Handle(bool &in_game, bool &running, snake &SNAKE)
{
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            quitSDL(window, renderer, Gameover, ScreenSurface);
        }
        SNAKE.event_handle(event, in_game, running);
    }
}


