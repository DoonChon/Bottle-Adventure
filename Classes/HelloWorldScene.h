#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#pragma execution_character_set("utf-8")

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    Size window;
    int valid = 0;
    int id;
    vector<string> resources = {"bottle_bg", "Robby_cloud", "bottle", "coin", "bg_color"};

    FileUtils* file = FileUtils::getInstance();

    LayerColor* bg;
    Layer* ui;

    Label* author;
    Label* loading;

    bool error(string title, string msg);
    void animation(float dt);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
