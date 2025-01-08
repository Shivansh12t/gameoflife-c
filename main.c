#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

#define W_WIDTH 800
#define W_HEIGHT 600
#define CELL_WIDTH 10

#define COLOR_GREEN 0x39ff14
#define COLOR_GREEN_DARK 0x008000

void draw_grid(SDL_Surface* surface, int width, int height, int cell_width, Uint32 color){
    for (int x = 0; x <= width; x += cell_width){
        for (int y = 0; y <= height; y++){
            SDL_Rect pixel = (SDL_Rect) {x,y,1,1};
            SDL_FillRect(surface, &pixel, color);
        }
    }
    for (int y = 0; y <= height; y += cell_width){
        for (int x = 0; x <= width; x++){
            SDL_Rect pixel = (SDL_Rect) {x,y,1,1};
            SDL_FillRect(surface, &pixel, color);
        }
    }
}

int main(int argc, char* argv[]){
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("conway's game of life in C", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_WIDTH, W_HEIGHT, 0);

    SDL_Surface* surface = SDL_GetWindowSurface(window);

    SDL_Rect rect = (SDL_Rect) {30,40,50,60};
    SDL_FillRect(surface, &rect, COLOR_GREEN);

    draw_grid(surface, W_WIDTH, W_WIDTH, CELL_WIDTH, COLOR_GREEN_DARK);

    SDL_UpdateWindowSurface(window);

    SDL_Delay(5000); 
    return 0;
}