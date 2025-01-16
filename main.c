#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>

#define W_WIDTH 900
#define W_HEIGHT 600
#define CELL_WIDTH 15
#define LINE_WIDTH 2

#define COLOR_GREEN 0x39ff14
#define COLOR_GREEN_DARK 0x004d00
#define COLOR_BLACK 0x000000

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

void init_game_matrix(int rows, int cols, int game_matrix[]){
    
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            game_matrix[i*cols + j] = rand() > RAND_MAX * 7.0 / 10.0;
        }
    }
}

void draw_game_matrix(SDL_Surface* surface, int rows, int cols, int game_matrix[], Uint32 color_light, Uint32 color_dark){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (game_matrix[i*cols + j]){
                draw_cell(surface, j, i, color_light);
            } else {
                draw_cell(surface, j, i, color_dark);
            }
        }
    }
}

int count_ns(int i, int j, int rows, int cols, int game_matrix[]){
    int n_counter = 0;

    // left hand neighbour
    if (j > 0) n_counter += game_matrix[j - 1 + cols * i];

    // right hand neighbour
    if (j < cols - 1) n_counter += game_matrix[j + 1 + cols * i];

    // top neighbour
    if (i > 0) n_counter += game_matrix[j + cols * (i - 1)];

    // top left neighbour
    if (i > 0 && j > 0) n_counter += game_matrix[j - 1 + cols * (i - 1)];

    // top right neighbour
    if (i > 0 && j < cols - 1) n_counter += game_matrix[j + 1 + cols * (i - 1)];

    // down neighbour
    if (i < rows - 1) n_counter += game_matrix[j + cols * (i + 1)];

    // down left neighbour
    if (i < rows - 1 && j > 0) n_counter += game_matrix[j - 1 + cols * (i + 1)];

    // down right neighbour
    if (i < rows - 1 && j < cols - 1) n_counter += game_matrix[j + 1 + cols * (i + 1)];
    return n_counter;
}

void simulation_step(int rows, int cols, int game_matrix[]){
    int next_game_matrix[rows*cols];

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            int n_count = count_ns(i, j, rows, cols, game_matrix);
            int curr_cell_value = game_matrix[j + cols * i];

            // perform logic
            if      (curr_cell_value != 0 && n_count < 2) next_game_matrix[j + cols * i] = 0;
            else if (curr_cell_value != 0 && (n_count == 2 || n_count == 3)) next_game_matrix[j + cols * i] = 1;
            else if (curr_cell_value != 0 && n_count > 3) next_game_matrix[j + cols * i] = 0;
            else if (curr_cell_value == 0 && n_count == 3) next_game_matrix[j + cols * i] = 1;
            else next_game_matrix[j + cols * i] = 0;
        }
    }

    for (int i = 0; i < rows * cols; i++){
        game_matrix[i] = next_game_matrix[i];
    }
}

int main(int argc, char* argv[]){
    SDL_Init(SDL_INIT_VIDEO);
    srand(time(NULL)); // seeding the rand

    SDL_Window* window = SDL_CreateWindow("conway's game of life in C", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_WIDTH, W_HEIGHT, 0);
    SDL_Surface* surface = SDL_GetWindowSurface(window);


    const int cols = W_WIDTH / CELL_WIDTH;
    const int rows = W_HEIGHT / CELL_WIDTH;

    int game_matrix[rows*cols];
    init_game_matrix(rows, cols, game_matrix);

    draw_game_matrix(surface, rows, cols, game_matrix, COLOR_GREEN, COLOR_BLACK);

    draw_grid(surface, rows, cols, CELL_WIDTH, COLOR_GREEN_DARK);
    init_game_matrix(rows, cols, game_matrix);


    int simulation_loop = 1;
    SDL_Event event;
    while (simulation_loop){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                simulation_loop = 0;
            }
        }
        simulation_step(rows, cols, game_matrix);
        draw_game_matrix(surface, rows, cols, game_matrix, COLOR_GREEN, COLOR_BLACK);
        draw_grid(surface, rows, cols, CELL_WIDTH, COLOR_GREEN_DARK);
        SDL_UpdateWindowSurface(window);
        SDL_Delay(100);
    }

    SDL_UpdateWindowSurface(window);
    SDL_Delay(5000);
    SDL_Quit();
    return 0;
}


