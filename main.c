#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "SDL_handler.h"
#include "ProceduralGenerator.h"


void pause() {
    bool keep_going = true;
    SDL_Event event;

    while (keep_going)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                keep_going = false;
            default:
                break;
        }
    }
}


int main(int argc, char **argv) {

    srand((uint32_t) time(NULL));
    srand((uint32_t) rand());

    int32_t x = 0,
            y = 0;
    uint64_t seed = ((uint64_t) rand() << 32) + ((uint64_t) rand());

    uint32_t i = 1;
    while (i < argc) {
        char *arg = argv[i];
        if (strcmp(arg, "--set-position") == 0) {
            printf("x = ");
            scanf("%d", &x);
            printf("y = ");
            scanf("%d", &y);
        } else if (strcmp(arg, "--set-seed") == 0) {
            printf("seed = ");
            scanf("%llu", &seed);
        } else {
            printf("Invalid parameter: %s", arg);
            exit(EXIT_FAILURE);
        }
        i ++;
    }

    printf("Seed: %llu\n", seed);
    printf("Starting position: (%d, %d)\n", x, y);


    SDL_handler *handler = initSDL();

    AssetPositionList *trees = initList("tree", 10.0);
    AssetPositionList *rocks = initList("rock", 4.0);
    for (int k = x - 4; k < x + 5; k++) {
        for (int l = y - 3; l < y + 4; l++) {
            generatePatch(seed, k, l, CELL_SIZE * (k - x + 4), CELL_SIZE * (l - y + 3), trees);
            generatePatch(seed, k, l, CELL_SIZE * (k - x + 4), CELL_SIZE * (l - y + 3), rocks);
        }
    }

    AssetPositionList *assets[2] = { rocks, trees };

    AssetPositionList *all_assets = fuseAssets(assets, 2);
    renderList(all_assets, handler);

    pause();

    deleteList(trees);
    deleteList(rocks);
    deleteList(all_assets);
    quitSDL(handler);

    return EXIT_SUCCESS;
}