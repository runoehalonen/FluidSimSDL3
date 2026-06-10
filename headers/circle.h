#include <SDL3/SDL.h>

void drawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
const int32_t diameter = (radius * 2);

int32_t x = (radius - 1);
int32_t y = 0;
int32_t tx = 1;
int32_t ty = 1;
int32_t error = (tx - diameter);

while (x >= y)
{
  SDL_Log("Iteration");
// Each of the following renders an octant of the circle
const SDL_FPoint points[8] = {
    {centreX + x, centreY - y},
    {centreX + x, centreY + y},
    {centreX - x, centreY - y},
    {centreX - x, centreY + y},
    {centreX + y, centreY - x},
    {centreX + y, centreY + x},
    {centreX - y, centreY - x},
    {centreX - y, centreY + x}
};
SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
SDL_RenderPoints(renderer, points, 8);

  if (error <= 0)
  {
  	++y;
  	error += ty;
  	ty += 2;
  }

  if (error > 0)
  {
  	--x;
  	tx += 2;
  	error += (tx - diameter);
  }
}
}