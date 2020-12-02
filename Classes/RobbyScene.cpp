#include "RobbyScene.h"
#include "MainScene.h"

Scene* Robby::createScene()
{
    return Robby::create();
}

bool Robby::init() {
    if (!Scene::init()) {
        return false;
    }

    window = Director::getInstance()->getWinSize();
    isPlay = false;
    isSettings = false;

    bg = Layer::create();
    this->addChild(bg, 0);

    bg_1 = Sprite::create("Robby_bg.png");
    bg_1->setAnchorPoint(Vec2(0, 0));
    bg_1->setPosition(Vec2(0, 0));
    bg_1->setContentSize(window);
    bg->addChild(bg_1, 1);

    ui = Layer::create();
    this->addChild(ui, 1);

    bg_2 = Sprite::create("Robby_cloud.png");
    bg_2->setAnchorPoint(Vec2(0, 0));
    bg_2->setPosition(Vec2(0, 0));
    bg_2->setContentSize(window);
    ui->addChild(bg_2);

    bg_21 = Sprite::create("Robby_cloud.png");
    bg_21->setAnchorPoint(Vec2(0, 0));
    bg_21->setPosition(Vec2(window.width, 0));
    bg_21->setContentSize(window);
    ui->addChild(bg_21);

    title = Label::createWithTTF("병들의 모험", "fonts/CookieRun Regular.ttf", 48);
    title->setPosition(Vec2(window.width / 2, window.height - 64));
    title->setTextColor(Color4B(0, 0, 0, 255));
    ui->addChild(title);

    bg_bottle1 = Sprite::create("picture.png");
    bg_bottle1->setScale(0.5f);
    bg_bottle1->setPosition(Vec2((window.width / 2) - 128, window.height / 2));
    ui->addChild(bg_bottle1);

    bottle1_img = Sprite::create("bottle.png");
    bottle1_img->setScale(1.2f);
    bottle1_img->setAnchorPoint(Vec2(0.5, 0));
    bottle1_img->setPosition(Vec2((window.width / 2) - 128, window.height / 2 + 16));
    ui->addChild(bottle1_img);

    bottle1_text = Label::createWithTTF("일반 병", "fonts/CookieRun Regular.ttf", 32);
    bottle1_text->setAnchorPoint(Vec2(0.5, 1));
    bottle1_text->setPosition(Vec2((window.width / 2) - 128, window.height / 2 - 16));
    bottle1_text->setTextColor(Color4B(0, 0, 0, 255));
    ui->addChild(bottle1_text);

    bg_Locked = Sprite::create("picture.png");
    bg_Locked->setScale(0.5f);
    bg_Locked->setPosition(Vec2((window.width / 2) + 128, window.height / 2));
    ui->addChild(bg_Locked);

    Locked_img = Sprite::create("locked.png");
    Locked_img->setScale(1.2f);
    Locked_img->setAnchorPoint(Vec2(0.5, 0));
    Locked_img->setPosition(Vec2((window.width / 2) + 128, window.height / 2 + 16));
    ui->addChild(Locked_img);

    Locked_text = Label::createWithTTF("더 많은 병이\n공개될 예정이에요.", "fonts/CookieRun Regular.ttf", 28, Size::ZERO, TextHAlignment::CENTER);
    Locked_text->setAnchorPoint(Vec2(0.5, 1));
    Locked_text->setPosition(Vec2((window.width / 2) + 128, window.height / 2 - 16));
    Locked_text->setTextColor(Color4B(0, 0, 0, 255));
    ui->addChild(Locked_text);

    auto play_label = Label::createWithTTF("플레이", "fonts/CookieRun Regular.ttf", 36);
    play_label->setTextColor(Color4B(0, 0, 0, 255));
    auto settings_label = Label::createWithTTF("설정", "fonts/CookieRun Regular.ttf", 36);
    settings_label->setTextColor(Color4B(0, 0, 0, 255));

    play = MenuItemLabel::create(play_label, CC_CALLBACK_1(Robby::playCallback, this));
    settings = MenuItemLabel::create(settings_label, CC_CALLBACK_1(Robby::settingsCallback, this));
    menu = Menu::create(play, settings, NULL);
    menu->setPosition(Vec2(window.width / 2, window.height / 8));
    menu->alignItemsVertically();
    ui->addChild(menu);

    ground = Sprite::create("bg_Robby_ground.png");
    ground->setPosition(Vec2(window.width / 2, -(window.height + (window.height / 2))));
    ground->setContentSize(Size(window.width, window.height + 164));
    this->addChild(ground, 2);

    scheduleUpdate();

    return true;
}

void Robby::playCallback(Ref* sender)
{
    isPlay = true;
}

void Robby::settingsCallback(Ref* sender)
{
    isSettings = true;
}

void Robby::update(float dt)
{
    bg_2->setPositionX(bg_2->getPositionX() - 1);
    bg_21->setPositionX(bg_21->getPositionX() - 1);
    if (bg_2->getPositionX() <= -window.width) {
        bg_2->setPositionX(window.width);
    }
    else if (bg_21->getPositionX() <= -window.width) {
        bg_21->setPositionX(window.width);
    }
    if (isPlay) {
        ui->setPositionY(ui->getPositionY() - 50);
        ground->setPositionY(ground->getPositionY() + 50);
        if (ui->getPositionY() <= -(window.height + (window.height / 2))) {
            Scene* scene = Main::create();
            Director::getInstance()->replaceScene(scene);
            this->unscheduleUpdate();
        }
    }
    else if (isSettings) {

    }
}
