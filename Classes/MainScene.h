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
    const int NormalBottle = 10;
    int coin = 0, ruby = 0, star = 0, level = 0, exp = 0, bottles = 0, updated = 0, frame = 0, slimes = 0;
    vector<string> unlocked_bottle;
    vector<int> item_count, slime_hp, slime_frame;
    vector<float> xp, yp;
    vector<Sprite*> slime_data;

    Size window;

    Layer* bg;
    Sprite* bg_img;
    Layer* ui;
    Label* stat;

    Node* temp;

    void onTouchesBegan(const std::vector<Touch*>& touches, Event* unused_event);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event* unused_event);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* unused_event);
    void update(float dt);
    void asdf(float dt);
    void fadeOut(float dt);

    // implement the "static create()" method manually
    CREATE_FUNC(Main);
};

#endif