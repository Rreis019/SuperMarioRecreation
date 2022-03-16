#include "Drawings.h"

void drawFilledRect(SDL_Renderer* renderer ,int x,int y,int w,int h, SDL_Color color)
{
 	SDL_Rect rect = {x,y,w,h};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

void drawRect(SDL_Renderer* renderer,int x,int y ,int w ,int h ,int thickness,SDL_Color color)
{
	drawFilledRect(renderer,x - thickness,y,thickness,h,color); //  Left border -> |
	drawFilledRect(renderer,x + w,y,thickness,h,color); //  Right border -> |
	drawFilledRect(renderer,x-thickness,y- thickness ,w + thickness*2,thickness,color); //  Top border -> -
	drawFilledRect(renderer,x-thickness,y+h,w + thickness*2,thickness,color); //  Bottom border -> -
} 

void drawLine(SDL_Renderer* renderer,int x1,int y1,int x2,int y2,SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

//https://stackoverflow.com/questions/38334081/howto-draw-circles-arcs-and-vector-graphics-in-sdl
void drawCircle(SDL_Renderer* renderer,int32_t centreX, int32_t centreY, int32_t radius)
{
   const int32_t diameter = (radius * 2);

   int32_t x = (radius - 1);
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

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


void drawFilledCircle(SDL_Renderer* renderer,int x, int y, int radius,SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r,color.g,color.b,color.a);
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

