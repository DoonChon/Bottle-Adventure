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
    xp = {};
    yp = {};
    slime_hp = {};
    slime_frame = {};
    slime_data = {};
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

    stat = Label::createWithTTF("잡은 슬라임: 0", "fonts/CookieRun Regular.ttf", 32);
    stat->setAnchorPoint(Vec2(0, 1));
    stat->setPosition(Vec2(0, window.height));
    stat->setTextColor(Color4B(0, 0, 0, 255));
    ui->addChild(stat);

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("slime.plist");
    
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
        float x = touch->getLocation().x;
        float y = touch->getLocation().y - (window.height / 2);
        xp.push_back(x);
        yp.push_back(y);
    }
}

void Main::update(float dt)
{
    // 병 날리기
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
                if (target->getPositionX() >= window.width) {
                    ui->removeChildByName(to_string(i));
                }
                else {
                    for (int j = 0; j < slimes; j++) {
                        auto s = ui->getChildByName("s" + to_string(j));
                        if (s != nullptr) {
                            Rect slimeRect = s->getBoundingBox();
                            if (targetRect.intersectsRect(slimeRect)) {
                                ui->removeChildByName(to_string(i));
                                slime_hp[j] -= NormalBottle;
                                auto hpb = ui->getChildByName("sp" + to_string(j));
                                if (hpb != nullptr) {
                                    hpb->setContentSize(Size(30, 10));
                                }
                                auto to = TintTo::create(0.3f, Color3B(255, 0, 0));
                                s->runAction(to);
                                auto an = TintTo::create(0.3f, Color3B(Color4B(255, 255, 255, 255)));
                                s->runAction(an);
                                if (slime_hp[j] <= 0) {
                                    ui->removeChildByName("s" + to_string(j));
                                    exp++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    stat->setString("잡은 슬라임: " + to_string(exp));

    /* 슬라임 이미지 설정
        if (frame == 30) {
            slime->setSpriteFrame("slime2.png");
        }
        else if (frame == 60) {
            frame = 0;
            slime->setSpriteFrame("slime1.png");
        }
        //slime->setPositionX(slime->getPositionX() - 0.5);
        frame++;*/

    // 슬라임 생성
    if (random(0, 200) == 100) {
        auto slime = Sprite::createWithSpriteFrameName("slime1.png");
        slime->setPosition(Vec2(window.width, random(100, (int) window.height - 100)));
        slime->setName("s" + to_string(slimes));
        ui->addChild(slime);
        LayerColor* hp_bar = LayerColor::create(Color4B(255, 0, 0, 255));
        hp_bar->setContentSize(Size(90, 10));
        hp_bar->setPositionY(slime->getContentSize().height);
        hp_bar->setName("sp" + to_string(slimes));
        slime->addChild(hp_bar);
        slimes++;
        slime_hp.push_back(30);
        slime_frame.push_back(frame);
        slime_data.push_back(slime);
    }
    // 슬라임 움직이기
    for (int h = 0; h < slimes; h++) {
        auto asd = ui->getChildByName("s" + to_string(h));
        if (asd != nullptr) {
            asd->setPositionX(asd->getPositionX() - 0.7);
            /*if (frame == 30 && slime_data[h] != nullptr) {
                slime_data[h]->setSpriteFrame("slime1.png");
            }
            else if (frame == 60 && slime_data[h] != nullptr) {
                slime_data[h]->setSpriteFrame("slime2.png");
                frame = 0;
            }*/
        }
    }
    //frame++;
}

void Main::asdf(float dt)
{
    
}

/* int random()
{
    srand((unsigned int)time(NULL));
    int num = rand();
    return (int)num % 10;
} */