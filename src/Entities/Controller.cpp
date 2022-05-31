#include "Controller.h"
#include <SDL2/SDL.h>
#include "Input.h"
#include "World.h"
#include "Utils.h"
#include "Timer.h"
#include "Game.h"
#include "Fireball.h"
#include "Prefabs.h"
#include "SoundManager.h"
#include "Logger.h"

#define DELAY_TO_SHOOT 0.5f

PlayerControls player1Controls = {SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_SPACE, SDL_SCANCODE_LCTRL,SDL_SCANCODE_LSHIFT};
PlayerControls player2Controls =  {SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_UP, SDL_BUTTON_LEFT,SDL_SCANCODE_MINUS};

Controller::~Controller()
{
    //free all sprites  std::vector<std::vector<Sprite>> sprites;
    for(int i = 0; i < (int)sprites.size(); i++)
    {
        for(int j = 0; j < (int)sprites[i].size(); j++)
        {
            SDL_DestroyTexture(sprites[i][j].texture);
        }
    }
    log("Controller destroyed\n");
}

Controller::Controller()
{
    tag = ETags::TController;
    this->layer = ELayers::LPLAYER;
    this->controls = &player1Controls;
    init((char*)"Mario");
}

Controller::Controller(PlayerControls* controls,char* characterName)
{
    tag = ETags::TController;
    this->layer = ELayers::LPLAYER;
    this->controls = controls;
    init(characterName);
}

void Controller::init(char* characterName)
{
    sprites.push_back(std::vector<Sprite>());
    sprites.push_back(std::vector<Sprite>());
    sprites.push_back(std::vector<Sprite>());
    char path[256];
    char base[50];
    sprintf(base, "%s_", characterName);

    sprintf(path, "Resources/Controller/%s/Small/", characterName);
    loadMultipleImages(sprites[0], path, base);

    sprintf(path, "Resources/Controller/%s/Medium/", characterName);
    loadMultipleImages(sprites[1], path, base);


    sprintf(path, "Resources/Controller/%s/Fire/", characterName);
    loadMultipleImages(sprites[2], path, base);
    changeSprite(0);


    //create colidders
    this->coliders.push_back( {ECol::Solid, Vec2(0, 0), Vec2(16,16) });
}

void Controller::changeSprite(int spriteIndex)
{
    sprite = &sprites[this->controllerSize][spriteIndex];   
}

void Controller::centerCamera()
{
    if(followCamera != nullptr)
    {
        followCamera->pos.x = this->pos.x;
        followCamera->pos.x -= game.witdh/2;
        if(followCamera->pos.x < 0){followCamera->pos.x = 0;}
    }

}

void Controller::onStart(){
    this->deadAnimation = false;
    this->startDeadTime = 0;
    this->velocity = Vec2(0,0);
}

//https://stackoverflow.com/questions/17263580/how-do-i-keep-the-jump-height-the-same-when-using-delta-time
void Controller::onUpdate()
{
    if(deadAnimation){this->onDead();}

    if(this->pos.y > game.height){
        this->onDead();
    }

    this->velocity.y +=  (pow(world.gravity,2) * timer.deltaTime) * gravity;

    if(!this->isFreeze){this->movement();}

    //Move the player
    this->pos.y += velocity.y * timer.deltaTime;
    if(checkCollisionY()){
        this->isJumping = false;
    }

    this->pos.x += velocity.x;
    checkCollisionX();

    //if the player is out of bounds put him back in bounds
    if(this->pos.x < 0){
        this->pos.x = 0;
        if(this->followCamera != nullptr){
            this->followCamera->pos.x = 0;
        }
    }
    
    this->jumping();

    if(followCamera != nullptr)
    {
        if(this->pos.x > game.witdh/2){
            followCamera->pos.x += this->velocity.x ;

            for(int i = 0 ; i < world.getCurrentScene()->numBackgrounds;i++){
                world.getCurrentScene()->backgrounds[i]->scrollX(-(this->velocity.x * (0.4f + (i * 0.3)) ));
            }
        }
        
    }

    if(!this->isFreeze)
    {
        bool canAttack = false;
        if(controls->attack == SDL_BUTTON_LEFT){canAttack = isLeftButtonDown();}
        else{
            canAttack = isKeyDown(controls->attack);
        }
        if(canAttack && timeShoot <= 0 && this->controllerSize == ControllerSizes::CFIRE)
        {
            int dir = 0;
            if(this->flip == SDL_FLIP_HORIZONTAL){dir = -1;}
            else{dir = 1;}

            Fireball* fireball = new Fireball(&effectsSprites[0], dir);
            fireball->pos.x =  this->pos.x + (this->coliders[0].size.x/2);
            fireball->pos.y =  this->pos.y + (this->coliders[0].size.y/2);
            world.addEntity(fireball);
            timeShoot = DELAY_TO_SHOOT;
            animationShootTime = 0.1f;
            soundManager.playSFX("Fireball.wav");
        }

        if(timeShoot >= 0){timeShoot -= timer.deltaTime;}
        if(animationShootTime >= 0){animationShootTime -= timer.deltaTime;}
        if(animationShootTime > 0){this->changeSprite(10);}
    }

}

void Controller::moveLeft()
{
    velocity.x = (currentSpeed * timer.deltaTime) * -1;
    currentDir = 1;
    elapsedTime = 0;
    //walk animation

    if(!isJumping){
        int delay = this->currentSpeed == runSpeed ? 50 : 100; 
        
        changeSprite(ANIMATION(0,3,delay));
    }
}

void Controller::moveRight()
{
    velocity.x = currentSpeed * timer.deltaTime;
    currentDir = 0;
    elapsedTime = 0;
    //walk animation
    if(!isJumping){changeSprite(ANIMATION(0,3,50));}
}

void Controller::movement()
{
    if(godMode)
    {
        godModeSeconds -= timer.deltaTime;
        if(godModeSeconds < 0)
        {
            godModeSeconds = 0;
            godMode = false;
            flickering = false;
        }
    }

    currentSpeed = isKeyDown(controls->run) ? runSpeed : walkSpeed;
    if(isKeyDown(controls->left)){
        moveLeft();
    }
    else if(isKeyDown(controls->right)){
        moveRight();
    }
    else{
        //idle
        if(this->velocity.x != 0 && isGrounded){ // friction
            elapsedTime+= timer.deltaTime;
            float percentage = elapsedTime / 0.2f;
            this->velocity.x = lerp(currentSpeed,0, percentage) * timer.deltaTime;
        }
        else{ this->velocity.x = 0;}
        if(!isJumping){ changeSprite(0);}
    }
}

void Controller::jumping()
{
    if(this->isFreeze){return;}
    //Jump  
    isGrounded = (int)(this->velocity.y) == 0 && isGrounded;
    
    if(isGrounded){isJumping = false;}

    if(isKeyDown(controls->jump) && isGrounded){
        velocity.y = -250;
        soundManager.playSFX("jump.wav");
        isJumping = true;
        jumpStartTime = timer.startTick;
    }

    bool JumpHold = (jumpStartTime + jumpLimit ) > timer.startTick;

    if(JumpHold && isKeyDown(controls->jump)){
        velocity.y += -(pow(45,2)* timer.deltaTime);
        changeSprite(4);
        isJumping = true;
    }

}

void Controller::onRender()
{
    if(this->flickering)
    {
        int draw = ANIMATION(0,2,75);
        if(draw == 0){return;}
    }

    Vec2 out = {0,0};
    if(world.currentCamera != NULL){
         world.currentCamera->W2S(this, out);
    }
    else{ out = this->pos; }    
    this->flip = currentDir == 1 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    this->sprite->draw(out.x,out.y,this->flip);
    this->drawColiders(out);
}

void Controller::onDead()
{
    if(!this->isAlive){return;}

    //if controller is diferent small then change to small
    if(this->controllerSize != ControllerSizes::CSMALL){
        this->controllerSize = ControllerSizes::CSMALL;
    }

    changeSprite(10);

    if(this->startDeadTime == 0){
        soundManager.playMusic("player Down.mp3",1);
        this->startDeadTime = timer.startTick;
        this->isFreeze = true;
        this->coliders.clear();
        this->velocity.y = -500;//Bounce the player up
        this->velocity.x = 0;
        log("died \n");
    }

    if(timer.startTick > this->startDeadTime + 2000)
    {
        this->isAlive = false;
        world.numPlayers-= 1;
        
        if(this->followCamera == nullptr){return;}
        for(int i = 0;i < world.controllers.size();i++)
        {
            Controller* c = (Controller*)world.controllers[i];
            if(this == c){continue;}
            c->followCamera = this->followCamera;
            c->followCamera->pos.x = c->pos.x;
            c->followCamera->pos.x -= game.witdh/2;
            if(c->followCamera->pos.x < 0){c->followCamera->pos.x = 0;}
            break;
        }
  
    }
}

void Controller::takeDamage(){
    if(godMode){return;}
    soundManager.playSFX("PowerDown.wav");
    if(this->controllerSize == ControllerSizes::CSMALL)
    {
        this->deadAnimation = true;
    }
    else{
        this->changeSize(ControllerSizes((int)this->controllerSize - 1));
        this->setImortal(0.5f);
        flickering = true;
    }
}

bool Controller::onColide(Ent* ent,int colIndex) {
    if(this->deadAnimation){return true;}
    if(ent->tag == TShell || ent->tag == TBowser|| ent->tag == TController || ent->tag == TToad || ent->tag == TFireball){return false;}
    return true;
}

void Controller::setImortal(float secondsImortal)
{
    this->godMode = true;
    this->godModeSeconds = secondsImortal;
}


void Controller::changeSize(ControllerSizes size)
{
    this->controllerSize = size;
    changeSprite(0);
    int difY = this->sprite->h - (int)this->coliders[0].size.y;
    this->pos.y -= difY;
    this->coliders[0].size = Vec2(this->sprite->w,this->sprite->h);
}

ControllerSizes Controller::getSize()
{
    return this->controllerSize;
}