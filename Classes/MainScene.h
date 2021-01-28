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

    int NormalSpeed = 100;
    int NormalBottle = 10;
    int playerHp = 100;
    double coin = 0;
    int ruby = 0, star = 0, level = 0, exp = 0, bottles = 0, updated = 0, frame = 0, slimes = 0;
    double play_coin = 0;
    bool pause = false;
    vector<string> unlocked_bottle;
    vector<int> item_count, slime_hp, slime_frame;
    vector<bool> is_defeat;
    vector<float> xp, yp;
    vector<Sprite*> slime_data;
    cocos2d::Vector<SpriteFrame*> slime_a, coin_frames, touch_frames, player_frames;

    Size window;
    UserDefault* saved_data;

    Layer* bg;
    Sprite* bg_img;
    // Sprite* slime;
    Layer* slime_layer;
    Layer* ui;
    Sprite* coin_icon;
    Label* coins;
    Sprite* bg_coins;
    Sprite* player;
    LayerColor* player_hp;

    MenuItemSprite* bottle_list;
    MenuItemSprite* go_main;
    Menu* menu;

    MenuItemSprite* close;
    Menu* close_menu;

    Node* temp;
    Action* slime_action;
    Action* coin_action;

    // º´ ¸Þ´º
    Layer* bottle_list_layer;
    Sprite* bg_bottles;
    Sprite* normal_bottle;
    Sprite* locked;
    Label* normal_bottle_text;
    Label* normal_bottle_stat;
    Label* locked_text;
    MenuItemSprite* normal_bottle_select;
    Menu* bottle_btn_list;

    void onTouchesBegan(const std::vector<Touch*>& touches, Event* unused_event);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event* unused_event);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* unused_event);
    virtual void update(float dt);
    void bottles_menu(Ref* sender);
    void main_menu(Ref* sender);
    void menu_close(Ref* sender);
    void remove_slime(Ref* sender, Ref* Object);
    void remove_ui(Ref* sender, Ref* Object);
    void player_damage(Ref* sender, Ref* Object);
    void bottle_clicked(Ref* sender);
    void game_over();
    void createSlime(int type);

    // implement the "static create()" method manually
    CREATE_FUNC(Main);
};

#endif