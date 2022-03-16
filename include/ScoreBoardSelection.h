#include "BaseScreen.h"

class ScoreBoardSelection : public BaseScreen
{
public:
    void events(SDL_Event events);
	void render();
	void onChangeScene();
private:
};
