#include "LivingEnt.h"
#include "Camera.h"
#include <vector>

enum ControllerSizes{
    CSMALL = 0,
    CMEDIUM,
    CFIRE,
    CSTAR
};

struct PlayerControls
{
    int down = 0;
    int left = 0;
    int right = 0;
    int jump = 0;
    int attack = 0;
    int run = 0;
};

class Controller : public LivingEnt
{
    public:
        //Pixels per second
        float currentSpeed = 0;
        float walkSpeed = 120.0f;
        float runSpeed = 180.0f;

        //0 -> left 1 -> right
        int currentDir = 0;
        
        //FLAGS
        bool isJumping = false;
        bool isFreeze = false;
        bool deadAnimation = false;
        bool godMode = false;
        bool gravity = true;
        bool flickering = false;
        bool deathMusicPlayed = false;

        //Jump
        int jumpStartTime = 0;
        int jumpLimit = 250;
        #define jumpForce -350.0f

        float elapsedTime = 0;
        int startDeadTime = 0;

        float timeShoot = 0;
        float animationShootTime = 0.0f;

        PlayerControls* controls;
        Camera * followCamera = nullptr;

        void setImortal(float secondsImortal);
        void changeSize(ControllerSizes size);
        ControllerSizes getSize();

        void freeze(){isFreeze = true; this->velocity = Vec2(0,0);}
        ~Controller();
        Controller();
        Controller(PlayerControls* controls,char* characterName);
        bool onColide(Ent* ent,int colIndex);
        void changeSprite(int spriteIndex);
        void onStart();
        void onRender();
        void onUpdate();
	    void onDead();
        void centerCamera();
        void moveLeft();
        void moveRight();
        void takeDamage();
    private:
        float godModeSeconds = 0;
        void movement();
        void jumping();
        void init(char* characterName);
        std::vector<std::vector<Sprite>> sprites;
        ControllerSizes controllerSize = CMEDIUM;
};


extern PlayerControls player1Controls;
extern PlayerControls player2Controls;