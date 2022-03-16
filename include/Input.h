#include "Vec2.h"
#include <SDL2/SDL.h>

void inputEvents(SDL_Event& event);
void inputReset();

bool isKeyDown(int index);
bool isKeyPressed(int index);
bool isLeftButtonDown();
bool isRightButtonDown();
Vec2 getMousePos();
bool isleftMouseClicked();
bool isRightMouseClicked();
