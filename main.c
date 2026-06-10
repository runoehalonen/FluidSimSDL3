#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdbool.h>
#include "headers/circle.h"
#include "headers/simulation.h"
#include "headers/fastdot.h"
#include "headers/drawtiles.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
Simulation simulation;

const int particleAmount = 100;
const int simulationWidth = 480;
const int simulationHeight = 480;

bool initVideo();
void endprogram();
bool makeWindow();
bool makeRenderer();
void loop();

int main()
{
    initProgram();
    simulationInit(&simulation, simulationWidth, simulationHeight, particleAmount);
    loop();
    endprogram();
    return 0;
}

int initProgram()
{
    // necessary for SDL3
    if (!initVideo() || !makeWindow() || !makeRenderer())
    {
        return 1;
    }
    return 0;
}

bool initVideo()
{
    bool success = SDL_Init(SDL_INIT_VIDEO);
    if (!success)
    {
        SDL_Log("Initialization failed! Cuz: %s\n", SDL_GetError());
    }
    return success;
}

bool makeWindow()
{
    window = SDL_CreateWindow("Hello, SDL!", simulationWidth, simulationHeight, 0);
    if (window == NULL)
    {
        SDL_Log("Window creation failed! Cuz: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

bool makeRenderer()
{
    renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL)
    {
        SDL_Log("Renderer creation failed! Cuz: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

void render()
{
    // Clears background with white sheet.
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
}

void update()
{
    SDL_RenderPresent(renderer);
}

float getDeltaTime(float lastTime)
{
    float now = SDL_GetTicks();
    float deltaTime = now - lastTime;
    return deltaTime;
}

void loop()
{
    Particle *particleCoordinatesArray;
    //  explanation in simulatio.h
    int *slotFirstParticleIndexMatrix;
    bool quit = false;
    float lastTime = SDL_GetTicks();
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {   
            // pressing x on window
            if (event.type == SDL_EVENT_QUIT)
            {
                quit = true;
            }
        }
        render();
        particleCoordinatesArray = getParticleCoordinates(&simulation);
        updateSimulation(&simulation, getDeltaTime(lastTime));
        lastTime = SDL_GetTicks();
        // comment for tile vision:
        for (int i = 0; i < simulation.particlePoolSize; i++)
        {
            drawDot(particleCoordinatesArray[i].x, particleCoordinatesArray[i].y);
        }
        // comment when using particle vision:
        // drawTiles(getSlotFirstParticleIndexMatrix(&simulation), renderer, simulationWidth, simulationHeight);

        // draw dots and update thing
        dotBufferFlush(renderer);
        update();
    }
}

void endprogram()
{
    simulationDestroy(&simulation);
    if (window != NULL)
    {
        SDL_DestroyWindow(window);
    }
    if (renderer != NULL)
    {
        SDL_DestroyRenderer(renderer);
    }
    SDL_Quit();
}