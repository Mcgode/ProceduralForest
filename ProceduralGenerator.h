//
// Created by Max Godefroy on 16/04/2018.
//

#ifndef PROCEDURALFOREST_PROCEDURALGENERATOR_H
#define PROCEDURALFOREST_PROCEDURALGENERATOR_H

#include <stdlib.h>
#include <time.h>

#include "SDL_handler.h"

struct AssetPosition {
    int32_t x;
    int32_t y;
    struct AssetPosition *next;
    char *asset;
};

typedef struct AssetPosition AssetPosition;

typedef struct {
    AssetPosition **list;
    char *asset;
    double lambda;
} AssetPositionList;

void generatePatch(
        uint64_t seed,
        int32_t patch_x, int32_t patch_y,
        int32_t graphical_offset_x, int32_t graphical_offset_y,
        AssetPositionList *list
);
void renderList(AssetPositionList *assets, SDL_handler *handler);
AssetPositionList *initList(const char *asset, double lambda);
void deleteList(AssetPositionList *assets);
AssetPositionList *fuseAssets(AssetPositionList **assets, uint8_t amount);


#endif
