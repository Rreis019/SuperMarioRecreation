#include "BaseScreen.h"
#include "Sprite.h"

enum EGameOverType
{
	GameOver,
	TimeUp
};

extern EGameOverType gameOverType;

class GameOverScreen : public BaseScreen
{
public:
	~GameOverScreen(){};
	GameOverScreen();
	void render();
	void events(SDL_Event events);
	void onChangeScene();
	void onChangedResolution();

private:
	std::vector<Sprite> sprites;
	int flickTime = 0;
	bool drawHand = false;
};