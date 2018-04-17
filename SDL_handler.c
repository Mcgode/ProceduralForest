//
// Created by Max Godefroy on 16/04/2018.
//

#include "SDL_handler.h"

SDL_handler *initSDL() {

    SDL_handler *handler = malloc(sizeof(SDL_handler));

    SDL_Window* sdl_window = NULL;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1)
    {
        fprintf(stderr, "SDL Init error (%s)\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    sdl_window = SDL_CreateWindow(
            "Procedural forest",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            WINDOW_WIDTH, WINDOW_HEIGHT,
            SDL_WINDOW_SHOWN
    );

    if(sdl_window == NULL)
    {
        fprintf(stderr,"Window creation error: %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Surface *window_surface = SDL_GetWindowSurface(sdl_window);
    if (window_surface == NULL) {
        fprintf(stderr, "Could not load window surface: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    Uint32 background_color = SDL_MapRGB(window_surface->format, 255, 255, 255);
    SDL_FillRect(window_surface, NULL, background_color);

    SDL_UpdateWindowSurface(sdl_window);

    handler->window = sdl_window;

    return handler;
}

void quitSDL(SDL_handler *handler)
{
    SDL_DestroyWindow(handler->window);
    SDL_Quit();
    free(handler);
}


static char *cat4(const char *s1, const char *s2, const char *s3, const char *s4)
{
    char *string = calloc(strlen(s1) + strlen(s2) + strlen(s3) + strlen(s4) + 1, sizeof(char));
    strcpy(string, s1);
    strcat(string, s2);
    strcat(string, s3);
    strcat(string, s4);

    return string;
}


void addAsset(SDL_handler *handler, int32_t x, int32_t y, const char *asset_name) {

    char *filepath = cat4(SOURCE_DIR, "/images/", asset_name, ".png");
    SDL_Surface *tree = NULL;
    tree = IMG_Load(filepath);
    free(filepath);

    if (tree == NULL) {
        fprintf(stderr, "Could not load image: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Rect position;

    uint32_t image_width = 10;
    uint32_t image_height = 20;

    if (strcmp(asset_name, "rock") == 0) image_height = 10;

    position.x = x - image_width / 2;
    position.y = y - image_height;

    SDL_Surface *window = SDL_GetWindowSurface(handler->window);
    if (window == NULL) {
        fprintf(stderr, "Could not load window surface: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_BlitSurface(tree, NULL, window, &position);

    SDL_UpdateWindowSurface(handler->window);
}
