#include "HelloWorldScene.h"
#include "RobbyScene.h"
#include "AudioEngine.h"

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init() {
    /*if (!Scene::init()) {
        return false;
    }*/

    window = Director::getInstance()->getWinSize();

    file = FileUtils::getInstance();

    bg = LayerColor::create(Color4B(0, 0, 0, 255));
    this->addChild(bg, 0);

    ui = Layer::create();
	this->addChild(ui, 1);

    author = Label::createWithTTF("Made by YH", "fonts/CookieRun Bold.ttf", 64);
    author->setTextColor(Color4B(255, 255, 255, 255));
    author->setPosition(Vec2(window.width / 2, window.height / 2));
    author->setOpacity(0);
    ui->addChild(author);

    dchs_cc = Label::createWithTTF("Doonchon HS Code Club", "fonts/CookieRun Bold.ttf", 64);
    dchs_cc->setTextColor(Color4B(255, 255, 255, 255));
    dchs_cc->setPosition(Vec2(window.width / 2, window.height / 2));
    dchs_cc->setOpacity(0);
    ui->addChild(dchs_cc);

    auto author_in = FadeIn::create(0.5f);
    author->runAction(author_in);

    this->schedule(SEL_SCHEDULE(&HelloWorld::animation), 1.0f);

    int id = AudioEngine::play2d("SonkeiSuru_edited.mp3", true);
    AudioEngine::setVolume(id, 0.5f);

	return true;
}

void HelloWorld::animation(float dt)
{
    auto author_out = FadeOut::create(0.5f);
    auto dchs_cc_in = FadeIn::create(0.5f);
    auto dchs_cc_out = FadeOut::create(0.5f);

    switch (repeated) {
    case 0:
        author->runAction(author_out);
        break;
    case 1:
        dchs_cc->runAction(dchs_cc_in);
        break;
    case 2:
        dchs_cc->runAction(dchs_cc_out);
        break;
    case 3:
        Director::getInstance()->replaceScene(TransitionFade::create(0.5f, Robby::createScene()));
    }
    repeated++;
}
