#include <SDL3/SDL.h>

// Only for square structures
const int LED_GRID_SIZE = 16;

SDL_FRect box;

static inline void drawTiles(int *slotFirstParticleIndexMatrix, SDL_Renderer *renderer, int matrixWidth, int matrixHeight)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    int simTileWidth = matrixWidth / LED_GRID_SIZE;
    int simTileHeight = matrixHeight / LED_GRID_SIZE;
    box.w = simTileWidth;
    box.h = simTileHeight;
    for (int y = 0; y < LED_GRID_SIZE; y++)
    {
        for (int x = 0; x < LED_GRID_SIZE; x++)
        {
            if (slotFirstParticleIndexMatrix[y * LED_GRID_SIZE + x] != -1)
            {
                box.x = x * simTileWidth;
                box.y = y * simTileHeight;
                SDL_RenderRect(renderer, &box);
                SDL_RenderFillRect(renderer, &box);
            }
        }
    }
}