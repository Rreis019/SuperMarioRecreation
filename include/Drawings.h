#include <SDL2/SDL.h>

void drawFilledRect(SDL_Renderer* renderer,int x,int y,int w,int h,SDL_Color color);
void drawRect(SDL_Renderer* renderer,int x,int y ,int w ,int h ,int thickness,SDL_Color color);
void drawLine(SDL_Renderer* renderer,int x1,int y1,int x2,int y2,SDL_Color color);
void drawCircle(SDL_Renderer* renderer,int32_t centreX, int32_t centreY, int32_t radius);
void drawFilledCircle(SDL_Renderer* renderer,int x, int y, int radius,SDL_Color color);