#include "ScoreBoardScreen.h"
#include "ScreenManager.h"
#include "LevelManager.h"
#include "World.h"
#include "KeyGui.h"
#include "ScoreSave.h"
#include <Windows.h>
#include "Logger.h"

bool isScoreBoardOnline = false;
Table scoreboard;

void ScoreBoardScreen::events(SDL_Event events)
{
    keyGui.events(events);

    if (events.type == SDL_KEYUP && events.key.keysym.sym == SDLK_ESCAPE)
	{
		 screenManager.changeScreen(SCOREBOARD_SELECTION_SCREEN);
	}
}

void ScoreBoardScreen::render()
{
    world.render();
	scoreboard.draw();
}

void ScoreBoardScreen::onChangeScene()
{
    keyGui.currentIndex = 0;
    levelManager.loadLevel("Resources/Levels/ScoreScreen.txt");
	world.maxPlayers = -1;

	log("online: %d\n", isScoreBoardOnline);
	scoreboard = Table();
	scoreboard.drawHeader = false;
	scoreboard.x = 75;
	scoreboard.y = 25;
	scoreboard.addCollum("", 30);	//Position
	scoreboard.addCollum("", 175); //Nome
	scoreboard.addCollum("", 58); //Score

	std::vector<ScoreSaveData> scores;
	if(isScoreBoardOnline)
	{
		if(!scoreSave.loadOnline(scores)){
			return;
		}
	}
	else{
		scores = scoreSave.loadLocal();
	}

	for (int i = 0; i < scores.size(); i++)
	{
		if(scores[i].score == -1){break;}
		std::string pos = std::to_string(i+1) + ".";
		scoreboard.addItem(pos);
		scoreboard.addItem(scores[i].personName);
		scoreboard.addItem(std::to_string(scores[i].score));
	}
}