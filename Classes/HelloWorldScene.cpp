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
    finished = false;

    file = FileUtils::getInstance();

    bg = LayerColor::create(Color4B(255, 255, 255, 255));
    this->addChild(bg, 0);

    ui = Layer::create();

    title = Label::createWithTTF("������ ����", "fonts/CookieRun Bold.ttf", 64);
    if (title == nullptr) {
        ccMessageBox("���� ������ �ջ�Ǿ� ������ �Ұ����մϴ�. ���� �缳ġ �� �ٽ� �õ����ּ���.", "���� �߻�!");
    }
    title->setPosition(Vec2(window.width / 2, (window.height / 2) + 128));
    title->setTextColor(Color4B(0, 0, 0, 255));
    ui->addChild(title, 0);

    // ���α׷��� ��
    pg_bg = LayerColor::create(Color4B(0, 0, 0, 160), window.width, 60);
    pg_bg->setAnchorPoint(Vec2(0, 0));
    pg_bg->setPosition(Vec2(0, 0));
    ui->addChild(pg_bg, 0);

    pg_bar = LayerColor::create(Color4B(0, 200, 255, 255), window.width, 60);
    pg_bar->setAnchorPoint(Vec2(0, 0));
    pg_bar->setPosition(Vec2(-window.width, 0));
    ui->addChild(pg_bar, 1);

    // �ε� �ؽ�Ʈ
    loading = Label::createWithTTF("���ҽ� Ȯ�� ���̿���!", "fonts/CookieRun Regular.ttf", 32);
    loading->setTextColor(Color4B(255, 255, 255, 255));
    loading->setPosition(Vec2(window.width / 2, 32));
    ui->addChild(loading, 2);

    // ���̾�α�
    dialog_bg = LayerColor::create(Color4B(0, 0, 0, 160));
    dialog_bg->setPosition(Vec2(0, 0));

    dialog = Sprite::create("dialog.png");
    dialog->setPosition(Vec2(window.width / 2, window.height / 2));
    dialog->setContentSize(Size(window.width / 2, window.height / 2));
    dialog_bg->addChild(dialog);

    dialog_title = Label::createWithTTF("������ �߻��߾��!", "fonts/CookieRun Bold.ttf", 32);
    dialog_title->setPosition(Vec2(window.width / 2, window.height / 2 + 84));
    dialog_title->setTextColor(Color4B(3, 154, 229, 255));
    dialog_bg->addChild(dialog_title);

    dialog_msg = Label::createWithTTF("���ҽ��� ã�� �� �����!\n������ �缳ġ���ֽ� �� �ٽ� �õ����ּ���.", "fonts/CookieRun Regular.ttf", 24);
    dialog_msg->setPosition(Vec2(window.width / 2, window.height / 2));
    dialog_msg->setTextColor(Color4B(0, 0, 0, 255));
    dialog_bg->addChild(dialog_msg);

    ok_button_frame = SpriteFrameCache::getInstance();
    ok_button_frame->addSpriteFramesWithFile("KR/OK_button.plist");

    dialog_normal_button = Sprite::createWithSpriteFrame(ok_button_frame->getSpriteFrameByName("OK_clickable.png"));
    dialog_normal_button->setContentSize(Size(108, 60));
    dialog_selected_button = Sprite::createWithSpriteFrame(ok_button_frame->getSpriteFrameByName("OK_clicked.png"));
    dialog_selected_button->setContentSize(Size(108, 60));

    dialog_button = MenuItemSprite::create(dialog_normal_button, dialog_selected_button, CC_CALLBACK_1(HelloWorld::menuCallback, this));
    dialog_menu = Menu::create(dialog_button, NULL);
    dialog_menu->setPosition(Vec2(window.width / 2, window.height / 3));
    dialog_bg->addChild(dialog_menu); 

    ui->addChild(dialog_bg, 3);
    dialog_bg->setVisible(false);
    dialog_bg->setOpacity(0);

    this->addChild(ui, 1);

    // ��ġ �̺�Ʈ ���� -> android ���� (iOS�� �����ϰ�ʹ�...)
    auto listen = EventListenerTouchAllAtOnce::create();
    listen->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
    listen->onTouchesEnded = CC_CALLBACK_2(HelloWorld::onTouchesEnded, this);
    listen->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
    _eventDispatcher->addEventListenerWithFixedPriority(listen, 1);
    HelloWorld::check();
    return true;
}

void HelloWorld::startMain(float dt)
{
}

void HelloWorld::check()
{
    int process = 0;
    vector<string> resources = { "bottle.png", "unlocked.png", "fonts/CookieRun Regular.ttf", "fonts/CookieRun Bold.ttf" };
    for (int i = 0; i < resources.size(); i++) {
        if (file->isFileExist(resources[i])) {
            pg_bar->setPositionX(pg_bar->getPositionX() + ((window.width / 1) / resources.size()));
            process++;
        }
    }
    if (process == resources.size()) {
        loading->setString("�ε����̿���!");
        finished = true;
    }
    else {
        
    }
}

void HelloWorld::error(string filename)
{
    FadeTo* fade = FadeTo::create(0.3f, 160);
    dialog_bg->setVisible(true);
    dialog_bg->runAction(fade);
}

void HelloWorld::menuCallback(Ref* sender)
{
}

void HelloWorld::onTouchesBegan(const std::vector<Touch*>& touches, Event* unused_event)
{
}

void HelloWorld::onTouchesMoved(const std::vector<Touch*>& touches, Event* unused_event)
{
}

void HelloWorld::onTouchesEnded(const std::vector<Touch*>& touches, Event* unused_event)
{
    if (finished) {
        auto pScene = Main::createScene();
        Director::getInstance()->replaceScene(pScene);
    }
}
