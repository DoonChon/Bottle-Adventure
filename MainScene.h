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

    const int NormalSpeed = 20;
    int coin, ruby, star, level, exp, bottles, updated;
    vector<string> unlocked_bottle;
    vector<int> item_count;

    Size window;

    LayerColor* bg;
    Layer* ui;

    void onTouchesBegan(const std::vector<Touch*>& touches, Event* unused_event);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event* unused_event);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* unused_event);
    virtual void update(float dt);

    // implement the "static create()" method manually
    CREATE_FUNC(Main);
};

#endif