//
// Created by Max Godefroy on 16/04/2018.
//


#ifndef PROCEDURALFOREST_SDL_HANDLER_H
#define PROCEDURALFOREST_SDL_HANDLER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include <stdio.h>

#define TREE_HEIGHT 20
#define TREE_WIDTH 10

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 700
#define CELL_SIZE 100


typedef struct {
    SDL_Window *window;
} SDL_handler;


SDL_handler *initSDL();
void quitSDL(SDL_handler *handler);
void addAsset(SDL_handler *handler, int32_t x, int32_t y, const char *asset_name);


#endif
