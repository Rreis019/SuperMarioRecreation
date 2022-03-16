#pragma once
#include <string>
#include <vector>
#include "Ent.h"


extern std::vector<Sprite> blockSprites;
extern std::vector<Sprite> enemySprites;
extern std::vector<Sprite> effectsSprites;
extern std::vector<Ent*> prefabs;

void loadPrefabs();
Ent* getPrefab(int index,float  x,float y);

enum EBlockId
{
	INone = -1,
	ILeftGrass,
	IMiddleGrass,
	IRightGrass,
	ILeftDirt,
	IMiddleDirt,
	IRightDirt,
	ISolidBlock,
	IBrick,
	IBrickAzul,
	ICoin,
	IMysteryBox,
	IMysteryBoxCoin,
	IMysteryBoxMushroom,
	IMysteryBoxFlower,
	IMysteryBoxStar,
	IFlag,
	IStar,
	ITunnelTopLeftEnter,
	ITunnelTopRightEnter,
	ITunnelLeft,
	ITunnelRight,
	ITunnelLeftTopEnter,
	ITunnelTop,
	ITunnelLeftTop,
	ITunnelBottomEnter,
	ITunnelBottom,
	ITunnelLeftBottom,
	IGoomba,
	IRedMushroom,
	IFlower,
	IKoopa,
	IShell,
	ILeftUnderGroundGrass,
	IMiddleUnderGroundGrass,
	IRightUnderGroundGrass,
	IUnderGroundGrass,


	ILeftUnderGroundDirt,
	IMiddleUnderGroundDirt,
	IRightUnderGroundDirt,
	IBlueSolidBlock,


	IBlueGoomba,
	IRedKoopa,

	GreenPlataformLeft,
	GreenPlataformMiddle,
	GreenPlataformRight,

	SupportGreenGreenPlataformSingle,
	SupportGreenGreenPlataformLeft,
	SupportGreenGreenPlataformMiddle,
	SupportGreenGreenPlataformRight,

	
	IMovingPlatformUP,
	IMovingPlatformDOWN,
	IMovingPlatformLEFTRIGHT,
	CastleSmall,
	CastleBig,
	IInvisibleBlock,
	ICarnPlant,
	ILeftCornerDungeonBlock,
	ITopDungeonBlock,
	IRightCornerDungeonBlock,
	ILeftDungeonBlock, 
	ICenterDungeonBlock,
	IRightDungeonBlock,
	IStonee,
	IDungeonBlock1,
	IDungeonBlock2,
	IDungeonBlock3,
	IDungeonBlock4,
	IDungeonBlock5,
	IDungeonBlock6,
	IDungeonBlock7,
	IDungeonBlock8,
	IDungeonBlock9
};


