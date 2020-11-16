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
    bool finished = false;

    FileUtils* file;
    SpriteFrameCache* ok_button_frame;

    Label* title;
    Label* loading;
    Label* dialog_title;
    Label* dialog_msg;

    Sprite* dialog_normal_button;
    Sprite* dialog_selected_button;

    MenuItemSprite* dialog_button;
    Menu* dialog_menu;

    LayerColor* bg;
    Layer* ui;
    LayerColor* pg_bg;
    LayerColor* pg_bar;
    LayerColor* dialog_bg;
    LayerColor* dialog;

    void startMain();
    void check();
    void menuCallback(Ref* sender);
    void onTouchesBegan(const std::vector<Touch*>& touches, Event* unused_event);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event* unused_event);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* unused_event);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
