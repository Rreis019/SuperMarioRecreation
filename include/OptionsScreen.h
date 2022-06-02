#include "BaseScreen.h"
#include "Sprite.h"

class OptionsScreen : public BaseScreen
{
public:
    void events(SDL_Event events);
	void render();
	void onChangeScene();
private:
};
