#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#pragma execution_character_set("utf-8")

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class GameOver : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	Size window;
	UserDefault* saved_data;
	
	Label* title;
	Label* text;
	MenuItemLabel* back;
	Menu* menu;

	void backToRobby(Ref* sender);

	CREATE_FUNC(GameOver);
};

#endif