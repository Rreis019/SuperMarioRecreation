#include "Prefabs.h"
#include "Sprite.h"
#include "World.h"
#include "Logger.h"

//ENTS
#include "Coin.h"
#include "MysteryBox.h"
#include "Goomba.h"
#include "Mushroom.h"
#include "Bricks.h"
#include "Flower.h"
#include "Flag.h"
#include "Koopa.h"
#include "CarnPlant.h"
#include "MovingPlatform.h"
#include "Shell.h"
#include "InvisibleBlock.h"
#include "FireBallChain.h"
#include "Bowser.h"
#include "Particle.h"
#include "Axe.h"
#include "Sack.h"
#include "Lava.h"


std::vector<Ent*> prefabs = std::vector<Ent*>();

std::vector<Sprite> blockSprites = std::vector<Sprite>();
std::vector<Sprite> enemySprites = std::vector<Sprite>();
std::vector<Sprite> effectsSprites = std::vector<Sprite>();



Ent* getPrefab(int index,float  x,float y)
{
    if(index > (int)(prefabs.size())-1 ){
        log("Prefab index out of bounds: %d\n",index);
        return prefabs[0]->clone(); 
    }

    Ent* e = prefabs[index]->clone();
    e->pos.x = x;
    e->pos.y = y;
    return e;
}


void loadPrefabs()
{
    log("Loading prefabs...\n");
    loadMultipleImages(blockSprites, "Resources/Blocks/", "Block_");
    loadMultipleImages(enemySprites, "Resources/Enemy/", "Enemy_");
    loadMultipleImages(effectsSprites, "Resources/Effects/", "Effects_");

   
    prefabs.push_back(new Ent(0, &blockSprites[0], ECol::Solid));//0 LeftGrass 
    prefabs.push_back(new Ent(0, &blockSprites[1], ECol::Solid));//1 MiddleGrass
    prefabs.push_back(new Ent(0, &blockSprites[2], ECol::Solid));//2 RightGrass
    
    prefabs.push_back(new Ent(0, &blockSprites[3], ECol::Solid));
    prefabs.push_back(new Ent(0, &blockSprites[4], ECol::Solid));
    prefabs.push_back(new Ent(0, &blockSprites[5], ECol::Solid));

    prefabs.push_back(new Ent(0, &blockSprites[6], ECol::Solid));//ISolidBlock
    prefabs.push_back(new Brick(&blockSprites[7],&particleSprites[9]));//IBrick
    prefabs.push_back(new Brick(&blockSprites[8],&particleSprites[25]));//IBlueBrick
    prefabs.push_back(new Coin(&blockSprites[9]));//ICoin

    prefabs.push_back(new MysteryBox(&blockSprites[13],EHoldNone));//IMysterBox
    prefabs.push_back(new MysteryBox(&blockSprites[13],EHoldCoin));//IMysterBox  with coin
    prefabs.push_back(new MysteryBox(&blockSprites[13],EHoldMushroom));//IMysterBox  with mushroom
    prefabs.push_back(new MysteryBox(&blockSprites[13],EHoldFlower));//IMysterBox  with flower
    prefabs.push_back(new MysteryBox(&blockSprites[13],EHoldStar));//IMysterBox  with star

    prefabs.push_back(new Flag(&blockSprites[18]));//IFlag
    prefabs.push_back(new Ent(0, &blockSprites[21], ECol::Solid));//IStar

    prefabs.push_back(new Ent((int)LTUBE, &blockSprites[25], ECol::Solid));//ITunnelTopEnterLeft
    prefabs.push_back(new Ent((int)LTUBE, &blockSprites[26], ECol::Solid));//ITunnelTopEnterRight
    prefabs.push_back(new Ent((int)LTUBE, &blockSprites[27], ECol::Solid));//ITunnelLeft
    prefabs.push_back(new Ent((int)LTUBE, &blockSprites[28], ECol::Solid));//ITunnelRight
    prefabs.push_back(new Ent((int)LTUBE, &blockSprites[29], ECol::Solid));//<- top enter ITunnelLeftTopEnter
    prefabs.push_back(new Ent((int)LTUBE, &blockSprites[30], ECol::Solid));// -- top ITunnelTop
    prefabs.push_back(new Ent((int)LTUBE, &blockSprites[31], ECol::Solid));//left and top ITunnelLeftTop,
    prefabs.push_back(new Ent((int)LTUBE, &blockSprites[32], ECol::Solid));//<- bottom enter ITunnelBottomEnter,
    prefabs.push_back(new Ent((int)LTUBE, &blockSprites[33], ECol::Solid));// -- bottom ITunnelBottom,
    prefabs.push_back(new Ent((int)LTUBE, &blockSprites[34], ECol::Solid));//left and bottom ITunnelLeftBottom,

    prefabs.push_back(new Goomba(&enemySprites[0]));//IGoomba
    prefabs.push_back(new Mushroom(&blockSprites[35]));//IRedMushroom
    prefabs.push_back(new Flower(&blockSprites[39]));//IFlower
    prefabs.push_back(new Koopa(&enemySprites[3],&enemySprites[7]));//IKoopa
    prefabs.push_back(new Shell(&enemySprites[7]));//IShell

    prefabs.push_back(new Ent(0, &blockSprites[43], ECol::Solid));//ILeftUnderGroundGrass
	prefabs.push_back(new Ent(0, &blockSprites[44], ECol::Solid));//IMiddleUnderGroundGrass,
	prefabs.push_back(new Ent(0, &blockSprites[45], ECol::Solid));//IRightUnderGroundGrass,
	prefabs.push_back(new Ent(0, &blockSprites[46], ECol::Solid));//IUnderGroundGrass,

	prefabs.push_back(new Ent(0, &blockSprites[47], ECol::Solid));//ILeftUnderGroundDirt,
	prefabs.push_back(new Ent(0, &blockSprites[48], ECol::Solid));//IMiddleUnderGroundDirt,
	prefabs.push_back(new Ent(0, &blockSprites[49], ECol::Solid));//IRightUnderGroundDirt,

	prefabs.push_back(new Ent(0, &blockSprites[50], ECol::Solid));//IBlueSolidBlock,

	prefabs.push_back(new Goomba(&enemySprites[35]));//IBlueGoomba, 11
	prefabs.push_back(new Koopa(&enemySprites[38],&enemySprites[38+4]));//IRedKoopa,

	prefabs.push_back(new Ent(0, &blockSprites[51], ECol::Solid));//GreenPlataformLeft
	prefabs.push_back(new Ent(0, &blockSprites[52], ECol::Solid));//GreenPlataformMiddle
	prefabs.push_back(new Ent(0, &blockSprites[53], ECol::Solid));//GreenPlataformRight

	prefabs.push_back(new Ent(0, &blockSprites[54]));//SupportGreenGreenPlataformSingle,
	prefabs.push_back(new Ent(0, &blockSprites[55]));//SupportGreenGreenPlataformLeft,
	prefabs.push_back(new Ent(0, &blockSprites[56]));//SupportGreenGreenPlataformMiddle,
	prefabs.push_back(new Ent(0, &blockSprites[57]));//SupportGreenGreenPlataformRight,


	prefabs.push_back(new MovingPlatform(&blockSprites[58],Vec2(0,-60)));// IMovingPlatformUP, Up
	prefabs.push_back(new MovingPlatform(&blockSprites[58],Vec2(0,60)));//Down
	prefabs.push_back(new MovingPlatform(&blockSprites[58],Vec2(30,0)));//Left and right

	prefabs.push_back(new Ent(0, &blockSprites[59]));//CastleSmall
	prefabs.push_back(new Ent(0, &blockSprites[60]));//CastleBig

	prefabs.push_back(new InvisibleBlock(&blockSprites[61]));//InvisibleBlock,

	prefabs.push_back(new CarnPlant(&enemySprites[12]));//ICarnPlant,

	for (int i = 0; i < 22; i++)
	{
		prefabs.push_back(new Ent(0, &blockSprites[62+i], ECol::Solid));
	}

	prefabs.push_back(new Lava(&blockSprites[84]));//Up Lava
	prefabs.push_back(new Ent(0, &blockSprites[92]));//Down Lava

	prefabs.push_back(new FireBallChain(&blockSprites[62+21]));//Fireball Chain
	prefabs.push_back(new Bowser(&enemySprites[47]));//Bowser
	prefabs.push_back(new Ent(0, &blockSprites[93]));//Corrente
	prefabs.push_back(new Axe(&blockSprites[94]));//Machado

	prefabs.push_back(new Sack(&enemySprites[54]));//Sack that contain TOAD



}


