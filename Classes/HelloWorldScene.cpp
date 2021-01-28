#include "HelloWorldScene.h"
#include "RobbyScene.h"
#include "AudioEngine.h"

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init() {
    if (!Scene::init()) {
        return false;
    }
    window = Director::getInstance()->getWinSize();
    bg = LayerColor::create(Color4B(0, 0, 0, 255));
    this->addChild(bg, 0);

    ui = Layer::create();
	this->addChild(ui, 1);

    author = Label::createWithTTF("병들의 모험", "fonts/CookieRun Bold.ttf", 64);
    if (author == nullptr) {
        return error("오류가 발생했어요!", "리소스를 찾을 수 없어 게임을 실행할 수 없어요. 게임 재설치 후 다시 시도해주세요.");
    }
    author->setTextColor(Color4B(255, 255, 255, 255));
    author->setPosition(Vec2(window.width / 2, window.height / 2));
    author->setOpacity(0);
    ui->addChild(author);

    loading = Label::createWithTTF("리소스를 불러오는 중이에요...", "fonts/CookieRun Bold.ttf", 32);
    loading->setTextColor(Color4B(255, 255, 255, 255));
    loading->setPosition(Vec2(window.width / 2, 32));
    ui->addChild(loading);

    auto author_in = FadeIn::create(0.5f);
    author->runAction(author_in);
    auto loading_in = FadeIn::create(0.5f);
    loading->runAction(loading_in);

    id = AudioEngine::play2d("SonkeiSuru_edited.mp3", true);
    AudioEngine::setVolume(id, 0.5f);

    for (int i = 0; i < (int) resources.size(); i++) {
        if (file->isFileExist(resources[i] + ".png") && file->isFileExist(resources[i] + ".plist")) {
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile(resources[i] + ".plist");
            valid++;
        }
        else {
            return error("오류가 발생했어요!", "리소스를 찾을 수 없어 게임을 실행할 수 없어요. 게임 재설치 후 다시 시도해주세요.");
        }
    }
    if (valid == (int) resources.size()) {
        this->schedule(SEL_SCHEDULE(&HelloWorld::animation), 1.0f);
    }
	return true;
}

bool HelloWorld::error(string title, string msg)
{
    AudioEngine::stop(id);
    ccMessageBox(msg.c_str(), title.c_str());
    return false;
}

void HelloWorld::animation(float dt)
{
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, Robby::createScene()));
}
