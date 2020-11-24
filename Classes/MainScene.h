#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#pragma execution_character_set("utf-8")

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Main : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    const int NormalSpeed = 100;
    int coin = 0, ruby = 0, star = 0, level = 0, exp = 0, bottles = 0, updated = 0, frame = 0;
    vector<string> unlocked_bottle;
    vector<int> item_count;
    vector<float> xp, yp;

    Size window;

    Layer* bg;
    Sprite* bg_img;
    Sprite* slime;
    Layer* ui;

    void onTouchesBegan(const std::vector<Touch*>& touches, Event* unused_event);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event* unused_event);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* unused_event);
    virtual void update(float dt);

    // implement the "static create()" method manually
    CREATE_FUNC(Main);
};

#endif