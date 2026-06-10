#include <SDL3/SDL.h>

#define MAX_DOTS 1000
#define POINTS_PER_DOT 9

static SDL_FPoint dotPointBuffer[MAX_DOTS * POINTS_PER_DOT];
static int dotCount = 0;

static inline void drawDot(int32_t x, int32_t y) {
    if (dotCount >= MAX_DOTS) return;
    SDL_FPoint* p = &dotPointBuffer[dotCount * POINTS_PER_DOT];
    p[0] = (SDL_FPoint){x,   y  };
    p[1] = (SDL_FPoint){x+1, y+1};
    p[2] = (SDL_FPoint){x-1, y-1};
    p[3] = (SDL_FPoint){x+1, y-1};
    p[4] = (SDL_FPoint){x-1, y+1};
    p[5] = (SDL_FPoint){x+1, y  };
    p[6] = (SDL_FPoint){x-1, y  };
    p[7] = (SDL_FPoint){x,   y+1};
    p[8] = (SDL_FPoint){x,   y-1};
    dotCount++;
}

static inline void dotBufferFlush(SDL_Renderer* renderer) {
    if (dotCount == 0) return;
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderPoints(renderer, dotPointBuffer, dotCount * POINTS_PER_DOT);
    dotCount = 0;
}