#include "BaseScreen.h"
#include "Sprite.h"

class VideoScreen : public BaseScreen
{
public:
	~VideoScreen(){};
	VideoScreen();
	void render();
	void events(SDL_Event events);
	void onChangeScene();
	void onChangedResolution();

private:
	std::vector<Sprite> sprites;
	int flickTime = 0;
	bool drawHand = false;
};