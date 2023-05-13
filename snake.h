#ifndef snake_hpp
#define snake_hpp
#include<iostream>
#include<SDL2/SDL.h>



class Board{
    public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    int BOARD_HEIGHT;
    int BOARD_WIDTH;
    void init();
    void handleEvents(bool*, SDL_Event&);
};

class Fruit{
    public:
    int x_pos;
    int y_pos;
    int BOARD_HEIGHT;
    int BOARD_WIDTH;
    int HEIGHT;
    int WIDTH;
    SDL_Rect rect;
    void init(Board&);
    void newFruit();
    void drawFruit(SDL_Renderer* renderer);
};

class Snake{
    public:
    int BOARD_HEIGHT;
    int BOARD_WIDTH;
    int HEIGHT;
    int WIDTH;
    int x_pos;
    int y_pos;
    int x_pos_arr[900];
    int y_pos_arr[900];
    int dir;
    int dir_index;
    int dir_array[10];
    int score;
    SDL_Rect rect;
    void init(Board&);
    void handleMoveEvents(bool*, SDL_Event&);
    void eat(Fruit&);
    void collide(bool*);
    void die(bool*);
    void move();
    void drawSnake(SDL_Renderer*); 
};

void append(int* ,int, int);
void pop(int*, int);

#endif