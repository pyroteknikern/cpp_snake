#include<iostream>
#include<SDL2/SDL.h>
#include"snake.h"

int main (int argc, char** argv)
{   
    bool run = true;
    Board board;
    Snake snake;
    Fruit fruit;
    board.init();
    snake.init(board);
    fruit.init(board);
    fruit.newFruit();
    while(run){
        snake.handleMoveEvents(&run, board.event);
        SDL_RenderClear(board.renderer);
        snake.move();
        snake.eat(fruit);
        snake.collide(&run);
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