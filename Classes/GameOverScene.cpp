#include "GameOverScene.h"
#include "RobbyScene.h"

Scene* GameOver::createScene()
{
    return GameOver::create();
}

bool GameOver::init() {
    /*if (!Scene::init()) {
        return false;
    }*/

    window = Director::getInstance()->getWinSize();
    saved_data = UserDefault::getInstance();

    double a = saved_data->getDoubleForKey("val1");
    double b = saved_data->getDoubleForKey("val2");
    a -= b;
    saved_data->setDoubleForKey("val1", a);

    title = Label::createWithTTF("게임 오버!", "fonts/CookieRun Regular.ttf", 48);
    title->setPosition(Vec2(window.width / 2, window.height - 64));
    this->addChild(title);

    text = Label::createWithTTF(to_string((int)saved_data->getDoubleForKey("val2")) + "코인을 잃으셨어요...",
        "fonts/CookieRun Regular.ttf", 32);
    text->setPosition(Vec2(window.width / 2, window.height / 2));
    this->addChild(text);

    auto label = Label::createWithTTF("메인으로 돌아가기", "fonts/CookieRun Regular.ttf", 32);
    back = MenuItemLabel::create(label, CC_CALLBACK_1(GameOver::backToRobby, this));
    menu = Menu::create(back, NULL);
    menu->setPosition(Vec2(window.width / 2, 128));
    this->addChild(menu);

    return true;
}

void GameOver::backToRobby(Ref* sender)
{
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, Robby::createScene()));
}