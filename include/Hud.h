#include <string>
#include <vector>
#include "Sprite.h"
class Hud
{
public:
    Hud(){};
    ~Hud(){};

    void init();
    void draw();
    void addCoin(int amount);
    void addScore(int amount);
    void setCoin(int amount);
    void setScore(int amount);

    int getScore() { return score; }
    int getCoin() { return coin; }

    int lifes = 5;
    float countdownTimer = 500;
    float countdownTimerMax = 500;
private:
    std::string coinStr = "x00";
    std::string scoreStr = "000000";
    std::vector<Sprite> coinSprites;

    int coin = 0;
    int score = 0;
};

extern Hud hud;