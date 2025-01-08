#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

#define W_WIDTH 900
#define W_HEIGHT 600
#define CELL_WIDTH 30
#define LINE_WIDTH 2

#define COLOR_GREEN 0x39ff14
#define COLOR_GREEN_DARK 0x004d00

void draw_grid(SDL_Surface* surface, int rows, int cols, int cell_width, Uint32 color){
    int width = cols * cell_width;
    int height = rows * cell_width;

    for (int y = 0; y <= rows; y++){
        SDL_Rect pixel = (SDL_Rect) {0, y*cell_width, width, LINE_WIDTH};
        SDL_FillRect(surface, &pixel, color);
    }
    for (int x = 0; x <= cols; x++){
        SDL_Rect pixel = (SDL_Rect) {x*cell_width, 0, LINE_WIDTH, height};
        SDL_FillRect(surface, &pixel, color);
    }
}

void draw_cell(SDL_Surface* surface, int cell_x, int cell_y, Uint32 color){
    cell_x *= CELL_WIDTH;
    cell_y *= CELL_WIDTH;

    // bixel means big pixel :)
    SDL_Rect bixel = (SDL_Rect){cell_x, cell_y, CELL_WIDTH, CELL_WIDTH};
    SDL_FillRect(surface, &bixel, color);
}

int main(int argc, char* argv[]){
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("conway's game of life in C", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_WIDTH, W_HEIGHT, 0);
    SDL_Surface* surface = SDL_GetWindowSurface(window);

    int cols = W_WIDTH / CELL_WIDTH;
    int rows = W_HEIGHT / CELL_WIDTH;

    draw_cell(surface, 5, 8, COLOR_GREEN);
    draw_cell(surface, 11, 15, COLOR_GREEN);
    draw_cell(surface, 23, 4, COLOR_GREEN);
    draw_cell(surface, 23, 5, COLOR_GREEN);
    draw_cell(surface, 1, 13, COLOR_GREEN);
    draw_grid(surface, rows, cols, CELL_WIDTH, COLOR_GREEN_DARK);

    SDL_UpdateWindowSurface(window);

    SDL_Delay(5000); 
    return 0;
}