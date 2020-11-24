﻿#include "MainScene.h"

Scene* Main::createScene()
{
    return Main::create();
}

bool Main::init()
{
    if (!Scene::init())
    {
        return false;
    }

    //init stat
    xp = {};
    yp = {};
    window = Director::getInstance()->getWinSize();

    bg = Layer::create();
    bg_img = Sprite::create("bg.png");
    bg_img->setContentSize(window);
    bg_img->setAnchorPoint(Vec2(0, 0));
    bg_img->setPosition(Vec2(0, 0));
    bg->addChild(bg_img, 1);
    this->addChild(bg, 0);

    ui = Layer::create();
    this->addChild(ui, 1);

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("slime.plist");
    slime = Sprite::createWithSpriteFrameName("slime1.png");
    slime->setPosition(Vec2(window.width / 2, window.height / 2));
    slime->setName("a");
    ui->addChild(slime);
    
    // 터치 이벤트 감지 -> android 지원 (iOS도 지원하고싶다...)
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(Main::onTouchesBegan, this);
    listener->onTouchesEnded = CC_CALLBACK_2(Main::onTouchesEnded, this);
    listener->onTouchesMoved = CC_CALLBACK_2(Main::onTouchesMoved, this);
    _eventDispatcher->addEventListenerWithFixedPriority(listener, 1);

    scheduleUpdate();
    
    return true;
}

void Main::onTouchesBegan(const std::vector<Touch*>& touches, Event* unused_event)
{
    Sprite* bottle = Sprite::create("bottle.png");
    bottle->setPosition(Vec2(window.width / 10, window.height / 2));
    bottle->setAnchorPoint(Vec2(0.5, 0.5));
    bottle->setName(to_string(bottles));
    ui->addChild(bottle, 2);
    bottles++;
}

void Main::onTouchesMoved(const std::vector<Touch*>& touches, Event* unused_event)
{
}

void Main::onTouchesEnded(const std::vector<Touch*>& touches, Event* unused_event)
{
    for (Touch* touch : touches) {
        float x = touch->getLocation().x - (window.width / 10);
        float y = touch->getLocation().y - (window.height / 2);
        xp.push_back(x);
        yp.push_back(y);
    }
}

void Main::update(float dt)
{
    for (int i = 0; i < bottles; i++) {
        if (xp.size() > i && yp.size() > i) {
            float toX = xp.at(i);
            float toY = yp.at(i);
            auto target = ui->getChildByName(to_string(i));
            if (target != nullptr) {
                target->setPositionX(target->getPositionX() + (toX / NormalSpeed));
                target->setPositionY(target->getPositionY() + (toY / NormalSpeed));
                target->setRotation(target->getRotation() + NormalSpeed);
                Rect targetRect = target->getBoundingBox();
                Rect slimeRect = slime->getBoundingBox();
                if (target->getPositionX() >= toX && target->getPositionY() >= toY) {
                    ui->removeChildByName(to_string(i));
                } else if (targetRect.intersectsRect(slimeRect)) {
                    ui->removeChildByName(to_string(i));
                    printf("충돌!!!");
                }
            }
        }
    }
    if (frame == 30) {
        slime->setSpriteFrame("slime2.png");
    }
    else if (frame == 60) {
        frame = 0;
        slime->setSpriteFrame("slime1.png");
    }
    frame++;
}
