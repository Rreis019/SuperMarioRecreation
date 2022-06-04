#include "BaseScreen.h"
#include "Sprite.h"

class AudioScreen : public BaseScreen
{
public:
	~AudioScreen(){};
	AudioScreen();
	void render();
	void events(SDL_Event events);
	void onChangeScene();
	void onChangedResolution();

private:
	std::vector<Sprite> sprites;
	int flickTime = 0;
	bool drawHand = false;
};