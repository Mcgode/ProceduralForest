//
// Created by Max Godefroy on 16/04/2018.
//

#include "ProceduralGenerator.h"


static uint8_t poisson_law(double p, double lambda) {
    uint8_t k = 0;
    double last_increment = lambda * exp(-lambda);
    double total = last_increment;

    while (total < p && k < 255) {
        k++;
        last_increment *= lambda / (double) k;
        total += last_increment;
    }
    return k;
}



static void insert(AssetPositionList *assets, int32_t x, int32_t y) {

    AssetPosition *current_position = assets->list[y];
    AssetPosition *last_position = NULL;

    AssetPosition *new_position = calloc(1, sizeof(AssetPosition));
    new_position->x = x;
    new_position->y = y;


    while (current_position != NULL) {
        if (current_position->x > x) {
            break;
        }
        last_position = current_position;
        current_position = current_position->next;
    }

    new_position->next = current_position;
    if (last_position == NULL) {
        assets->list[y] = new_position;
    } else {
        last_position->next = new_position;
    }
}



void generatePatch(
        uint64_t seed,
        int32_t patch_x, int32_t patch_y,
        int32_t graphical_offset_x, int32_t graphical_offset_y,
        AssetPositionList *list)
{
    srand((uint32_t) (seed + patch_x * 1345653 + patch_y * 1745653 + list->asset[0] * 15689));

    double x = (double) rand() / (double) RAND_MAX;
    if (x < 0) x = -x;

    uint8_t amount_of_assets = poisson_law(x, list->lambda);

    printf("p = %f => %d assets (RAND_MAX = %d)\n", x, amount_of_assets, RAND_MAX);

    for (uint8_t i = 0; i < amount_of_assets; i++) {
        srand((uint32_t) rand());
        insert(list, rand() % CELL_SIZE + graphical_offset_x, rand() % CELL_SIZE + graphical_offset_y);
    }
}



void deleteList(AssetPositionList *assets) {
    for (int32_t y = 0; y < WINDOW_HEIGHT; y++) {
        AssetPosition *current_position = assets->list[y];
        while (current_position != NULL) {
            AssetPosition *next = current_position->next;
            if (current_position->asset != NULL) free(current_position->asset);
            free(current_position);
            current_position = next;
        }
    }
    free(assets->list);
    free(assets->asset);
    free(assets);
}


AssetPositionList *initList(const char *asset, double lambda)
{
    AssetPositionList *assets = malloc(sizeof(AssetPositionList));

    assets->list = calloc(WINDOW_HEIGHT, sizeof(AssetPosition *));

    assets->asset = calloc(strlen(asset) + 1, sizeof(char));
    strcpy(assets->asset, asset);

    assets->lambda = lambda;

    return assets;
}



void renderList(AssetPositionList *assets, SDL_handler *handler)  {
    for (int32_t y = 0; y < WINDOW_HEIGHT; y++) {
        AssetPosition *current_position = assets->list[y];
        while (current_position != NULL) {
            addAsset(handler, current_position->x, current_position->y, current_position->asset);
            current_position = current_position->next;
        }
    }
}


AssetPositionList *fuseAssets(AssetPositionList **assets, uint8_t amount) {

    AssetPositionList *fused_assets = initList("all", 0);
    for (int32_t y = 0; y < WINDOW_HEIGHT; y++) {
        for (uint8_t i = 0; i < amount; i++) {
            AssetPosition *current_position = assets[i]->list[y];
            while (current_position != NULL) {

                AssetPosition *fa_position = fused_assets->list[y];
                AssetPosition *last_fa_position = NULL;

                AssetPosition *new_position = malloc(sizeof(AssetPosition));
                new_position->x = current_position->x;
                new_position->y = current_position->y;
                new_position->asset = calloc(strlen(assets[i]->asset) + 1, sizeof(char));
                strcpy(new_position->asset, assets[i]->asset);

                while (fa_position != NULL) {
                    if (fa_position->x > current_position->x) {
                        break;
                    }
                    last_fa_position = fa_position;
                    fa_position = fa_position->next;
                }

                new_position->next = fa_position;
                if (last_fa_position == NULL) {
                    fused_assets->list[y] = new_position;
                } else {
                    last_fa_position->next = new_position;
                }

                current_position = current_position->next;
            };
        }
    }

    return fused_assets;

}