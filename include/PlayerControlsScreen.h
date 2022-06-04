#include "BaseScreen.h"
#include "Sprite.h"

class PlayerControlsScreen : public BaseScreen
{
public:
    void events(SDL_Event events);
	void render();
	void onChangeScene();
private:
};

extern int playerControlsIndex;