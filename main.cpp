#include<iostream>
#include <SDL2/SDL.h>

class Board{
    public:
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    const int BOARD_HEIGHT = 30;
    const int BOARD_WIDTH = 30;
    void init(){
        window = SDL_CreateWindow("SDL window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
        renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
    }
};

class Fruit{
    public:
    int x_pos;
    int y_pos;
    const int BOARD_HEIGHT = 30;
    const int BOARD_WIDTH = 30;
    const int HEIGHT = 10;
    const int WIDTH = 10;
   
    SDL_Rect rect;
    
    void init(){
        rect.h = HEIGHT;
        rect.w = WIDTH;
    }

    void newFruit(){
        srand((unsigned) time(NULL));
        x_pos = rand() % BOARD_WIDTH;
        y_pos = rand() % BOARD_HEIGHT;
    }

    void drawFruit(SDL_Renderer* renderer){
            rect.x = x_pos*WIDTH;
            rect.y = y_pos*HEIGHT;
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &rect);
    }
};

class Snake{
    public:
    const int BOARD_HEIGHT = 30;
    const int BOARD_WIDTH = 30;
    const int HEIGHT = 10;
    const int WIDTH = 10;
    int x_pos = 0;
    int y_pos = 0;
    int x_pos_arr[30*30];
    int y_pos_arr[30*30];
    int dir = 1;
    int score = 1;
    SDL_Rect rect;


    void init(){
        rect.w = WIDTH;
        rect.h = HEIGHT; 
        for(int i = 0; i < BOARD_HEIGHT*BOARD_WIDTH; i++){
            x_pos_arr[i] = -1;
            y_pos_arr[i] = -1;
        }
        x_pos_arr[0] = x_pos;
        y_pos_arr[0] = y_pos;
    }
    void eat(Fruit &f){
        if(f.x_pos == x_pos && f.y_pos == y_pos){
            score += 1;
            f.newFruit();
        }
    }

    void move(int chdir){
        dir = chdir;
        if(dir == 0) y_pos -= 1;
        if(dir == 1) y_pos += 1;
        if(dir == 2) x_pos -= 1;
        if(dir == 3) x_pos += 1;
        for(int i = score-1; i > 0; i--){
            x_pos_arr[i] = x_pos_arr[i-1];
            y_pos_arr[i] = y_pos_arr[i-1];  
        }
        x_pos_arr[0] = x_pos;
        y_pos_arr[0] = y_pos;
    }

    void drawSnake(SDL_Renderer* renderer){   
        for(int i = 0; i < score; i++){
            rect.x = x_pos_arr[i]*WIDTH;
            rect.y = y_pos_arr[i]*HEIGHT;
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
};

int main (int argc, char** argv)
{   
    bool run = true;
    SDL_Event e;
    Board board;
    Snake snake;
    Fruit fruit;

    board.init();
    snake.init();
    fruit.init();
    fruit.newFruit();
    
    int dir = 1;
    while(run){
        while(SDL_PollEvent(&e) != 0){
            //User requests quit
            if(e.type == SDL_QUIT){
                run = false;
            }
            if(SDLK_a == e.key.keysym.sym){
                dir = 2;
            }
            if(SDLK_w == e.key.keysym.sym){
                dir = 0;
            }
            if(SDLK_s == e.key.keysym.sym){
                dir = 1;
            }
            if(SDLK_d == e.key.keysym.sym){
                dir = 3;
            }
        }
        SDL_RenderClear(board.renderer);
        snake.move(dir);
        snake.eat(fruit);
        fruit.drawFruit(board.renderer);
        snake.drawSnake(board.renderer);
        SDL_SetRenderDrawColor(board.renderer, 0, 0, 0, 255);
        SDL_RenderPresent(board.renderer);
        SDL_Delay(100);
    }

    SDL_DestroyWindow(board.window);
    SDL_Quit();

    return EXIT_SUCCESS;
}