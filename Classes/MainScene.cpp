#include "MainScene.h"

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
    coin = 0;
    ruby = 0;
    star = 0;
    level = 0;
    exp = 0;
    bottles = 0;
    updated = 0;

    bg = LayerColor::create(Color4B(255, 255, 255, 255));
    this->addChild(bg, 0);

    ui = Layer::create();

    this->addChild(ui, 1);
    
    window = Director::getInstance()->getWinSize();

    // 터치 이벤트 감지 -> windows & android 모두 지원 (Mac / iOS도 지원하고싶다...)
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
    PolygonInfo pinfo = AutoPolygon::generatePolygon("bottle.png");
    Sprite* bottle = Sprite::create(pinfo);
    bottle->setPosition(Vec2(window.width / 10, window.height / 3));
    bottle->setScale(0.3);
    bottle->setName(to_string(bottles));
    ui->addChild(bottle, 2);
    bottles++;
}

void Main::onTouchesMoved(const std::vector<Touch*>& touches, Event* unused_event)
{
}

void Main::onTouchesEnded(const std::vector<Touch*>& touches, Event* unused_event)
{
}

void Main::update(float dt)
{
    if (bottles != updated) {
        for (int i = 0; i < bottles; i++) {
            Node* target = ui->getChildByName(to_string(i));
            target->setPositionX(target->getPositionX() + 10);
        }
        updated++;
    }
}
