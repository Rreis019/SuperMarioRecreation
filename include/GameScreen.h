#include "BaseScreen.h"
#include "Sprite.h"

class GameScreen : public BaseScreen
{
public:
    void events(SDL_Event events);
	void render();
	void onChangeScene();
private:
	std::vector<Sprite> sprites;
};
