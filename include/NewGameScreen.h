#include "BaseScreen.h"
#include "Sprite.h"
#include <string>

class NewGameScreen : public BaseScreen
{
public:
    #define MAX_SLOTS 3
    void events(SDL_Event events);
	void render();
	void onChangeScene();
private:
    std::string slotText[MAX_SLOTS]; 
    bool isSlotEmpty[MAX_SLOTS];
};
