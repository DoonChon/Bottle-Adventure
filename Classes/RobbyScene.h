#ifndef __ROBBY_SCENE_H__
#define __ROBBY_SCENE_H__

#pragma execution_character_set("utf-8")

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Robby : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	Size window;
	bool isPlay, isSettings;

	Layer* bg;
	Sprite* bg_1;
	Sprite* bg_2;
	Sprite* bg_21;
	Layer* ui;
	Label* title;
	Sprite* bg_bottle1;
	Sprite* bottle1_img;
	Label* bottle1_text;
	Sprite* bg_Locked;
	Sprite* Locked_img;
	Label* Locked_text;
	MenuItemLabel* play;
	MenuItemLabel* settings;
	Menu* menu;
	Sprite* ground;

	void playCallback(Ref* sender);
	void settingsCallback(Ref* sender);
	virtual void update(float dt);

	CREATE_FUNC(Robby);
};

#endif