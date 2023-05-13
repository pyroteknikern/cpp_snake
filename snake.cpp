#include<iostream>
#include<SDL2/SDL.h>
#include"snake.h"

void Board::init(){
    window = SDL_CreateWindow("SDL window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
    BOARD_WIDTH = 30;
    BOARD_HEIGHT = 30;
}    

void Board::handleEvents(bool *run, SDL_Event& event){
    while(SDL_PollEvent(&event) != 0){
        std::cout << &event << std::endl;
        if(event.type == SDL_QUIT){
            *run = false;
        }
    }
}

void Fruit::init(Board& board){
    BOARD_HEIGHT = board.BOARD_HEIGHT;
    BOARD_WIDTH = board.BOARD_WIDTH;
    HEIGHT = 10;
    WIDTH = 10;
    rect.h = HEIGHT;
    rect.w = WIDTH;
}

void Fruit::newFruit(){
    srand((unsigned) time(NULL));
    x_pos = rand() % BOARD_WIDTH;
    y_pos = rand() % BOARD_HEIGHT;
}

void Fruit::drawFruit(SDL_Renderer* renderer){
    rect.x = x_pos*WIDTH;
    rect.y = y_pos*HEIGHT;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void Snake::init(Board& board){
    score = 1;
    dir = 1;
    dir_index = 0;
    dir_array[0] = 1;
    y_pos = 0;
    x_pos = 0;
    WIDTH = 10;
    HEIGHT = 10;
    BOARD_WIDTH = board.BOARD_WIDTH;
    BOARD_HEIGHT = board.BOARD_HEIGHT;
    rect.w = WIDTH;
    rect.h = HEIGHT; 
    x_pos_arr[0] = x_pos;
    y_pos_arr[0] = y_pos;
}

void Snake::handleMoveEvents(bool* run, SDL_Event &event){
    bool key_pressed = false;
    while(SDL_PollEvent(&event) != 0){
        if(SDL_KEYDOWN == event.type){
            if(event.type == SDL_QUIT)*run = false;
            if(key_pressed == false){
                key_pressed = true;
                dir_index = 0;
            }
            if(SDLK_a == event.key.keysym.sym){
                dir = 2;
                dir_index += 1;
            }
            if(SDLK_w == event.key.keysym.sym){
                dir = 0;
                dir_index += 1;
            }
            if(SDLK_s == event.key.keysym.sym){
                dir = 1;
                dir_index += 1;
            }
            if(SDLK_d == event.key.keysym.sym){
                dir = 3;
                dir_index += 1;
            }
            dir_array[dir_index] = dir;
        }         
    }
    if(dir_index > 0){
        pop(dir_array, 10);
        dir_index -= 1;
    }
    dir = dir_array[0];
}


void Snake::eat(Fruit &f){
    if(f.x_pos == x_pos && f.y_pos == y_pos){
        score += 1;
        f.newFruit();
    }
}

void Snake::collide(bool* run){
    for(int i = 1; i < score; i++){
        if(x_pos == x_pos_arr[i] && y_pos == y_pos_arr[i]){
            die(run);
        } 
    }
}

void Snake::die(bool* run){
    run[0] = false;
}

void Snake::move(){
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

void Snake::drawSnake(SDL_Renderer* renderer){   
    for(int i = 0; i < score; i++){
        rect.x = x_pos_arr[i]*WIDTH;
        rect.y = y_pos_arr[i]*HEIGHT;
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
}


void append(int* arr, int append_val, int len){
    for(int i = len-1; i > 0; i--){
        arr[i] = arr[i-1];  
    }
    arr[0] = append_val;
}

void pop(int* arr, int len){
    for(int i = 0; i < len-1; i++){
        arr[i] = arr[i+1];  
    }
}