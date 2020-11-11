#include "HelloWorldScene.h"
#include "MainScene.h"

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    window = Director::getInstance()->getWinSize();

    file = FileUtils::getInstance();

    bg = LayerColor::create(Color4B(255, 255, 255, 255));
    this->addChild(bg, 0);

    ui = Layer::create();

    title = Label::createWithTTF("병들의 모험", "fonts/CookieRun Bold.ttf", 64);
    title->setPosition(Vec2(window.width / 2, (window.height / 2) + 128));
    title->setTextColor(Color4B(0, 0, 0, 255));
    ui->addChild(title, 0);

    // 프로그래스 바
    pg_bg = LayerColor::create(Color4B(0, 0, 0, 160), window.width, 60);
    pg_bg->setAnchorPoint(Vec2(0, 0));
    pg_bg->setPosition(Vec2(0, 0));
    ui->addChild(pg_bg, 0);

    pg_bar = LayerColor::create(Color4B(0, 200, 255, 255), window.width, 60);
    pg_bar->setAnchorPoint(Vec2(0, 0));
    pg_bar->setPosition(Vec2(-window.width, 0));
    ui->addChild(pg_bar, 1);

    // 로딩 텍스트
    loading = Label::createWithTTF("리소스 확인 중이에요!", "fonts/CookieRun Regular.ttf", 32);
    loading->setTextColor(Color4B(255, 255, 255, 255));
    loading->setPosition(Vec2(window.width / 2, 32));
    ui->addChild(loading, 2);

    // 다이얼로그 (로딩실패, 코딩 실패(...?))
    /* dialog_bg = LayerColor::create(Color4B(0, 0, 0, 120));
    dialog_bg->setAnchorPoint(Vec2(0, 0));
    dialog_bg->setPosition(Vec2(0, 0));

    dialog = LayerColor::create(Color4B(255, 255, 255, 255), window.width / 2, window.height / 2);
    dialog->setPosition(Vec2(window.width / 2, window.height / 2));
    dialog_bg->addChild(dialog, 1);

    dialog_title = Label::createWithTTF("오류가 발생했어요!", "fonts/CookieRun Bold.ttf", 32);
    dialog_title->setPosition(Vec2(window.width / 2, (dialog->getContentSize().height / 2) + dialog->getPositionY() - 48));
    dialog_title->setTextColor(Color4B(0, 0, 0, 255));
    dialog->addChild(dialog_title);

    dialog_msg = Label::createWithTTF("리소스를 찾을 수 없어요!\n게임을 재설치해주신 뒤 다시 시도해주세요.", "fonts/CookieRun Regular.ttf", 16);
    dialog_msg->setPosition(Vec2(window.width / 2, dialog->getPositionY() / 2));
    dialog_msg->setTextColor(Color4B(0, 0, 0, 255));
    dialog->addChild(dialog_msg);

    ok_button_frame = SpriteFrameCache::getInstance();
    ok_button_frame->addSpriteFramesWithFile("KR/OK_button.plist");

    dialog_normal_button = Sprite::createWithSpriteFrame(ok_button_frame->getSpriteFrameByName("OK_clickable.png"));
    dialog_normal_button->setContentSize(Size(108, 60));
    dialog_selected_button = Sprite::createWithSpriteFrame(ok_button_frame->getSpriteFrameByName("OK_clicked.png"));
    dialog_selected_button->setContentSize(Size(108, 60));

    dialog_button = MenuItemSprite::create(dialog_normal_button, dialog_selected_button, CC_CALLBACK_1(HelloWorld::menuCallback, this));
    dialog_menu = Menu::create(dialog_button, NULL);
    dialog_menu->setPosition(Vec2(window.width / 2, dialog->getPositionY() - (dialog->getContentSize().height / 2) + 54));
    dialog->addChild(dialog_menu);

    dialog_bg->setOpacity(0);

    ui->addChild(dialog_bg, 3); */

    this->addChild(ui, 1);

    scheduleOnce(SEL_SCHEDULE(&HelloWorld::check), 1.5f);

    return true;
}

void HelloWorld::startMain(float dt)
{
    Scene* scene = Main::create();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
}

void HelloWorld::check(float dt)
{
    int process = 0;
    vector<string> resources = { "bottle.png", "unlocked.png", "fonts/CookieRun Regular.ttf", "fonts/CookieRun Bold.ttf" };
    for (int i = 0; i < resources.size(); i++) {
        if (file->isFileExist(resources[i])) {
            pg_bar->setPositionX(pg_bar->getPositionX() + ((window.width / 2) / resources.size()));
            process++;
        }
    }
    if (process == resources.size()) {
        loading->setString("로딩중이에요...");
        scheduleOnce(SEL_SCHEDULE(&HelloWorld::startMain), 1.5f);
    }
    else {
        
    }
}

void HelloWorld::menuCallback(Ref* sender)
{
}
