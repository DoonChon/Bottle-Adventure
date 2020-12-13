#include "MainScene.h"
#include "RobbyScene.h"
#include "Shake.h"
#include "GameOverScene.h"

Scene* Main::createScene()
{
    return Main::create();
}

bool Main::init()
{
    /*if (!Scene::init())
    {
        return false;
    }*/

    //init stat
    xp = {};
    yp = {};
    slime_hp = {};
    slime_frame = {};
    slime_data = {};
    slime_a = {};
    coin_frames = {};
    is_defeat = {};
    touch_frames = {};
    player_frames = {};
    window = Director::getInstance()->getWinSize();
    NormalBottle = 10;
    saved_data = UserDefault::getInstance();
    if (saved_data->getDoubleForKey("val1") != 0) {
        coin = saved_data->getDoubleForKey("val1");
    }

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bottle_bg.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Robby_cloud.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bottle.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("coin.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bg_color.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("slime.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("touch.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("button_play.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("button_bg.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("player.plist");

    bg = Layer::create();
    bg_img = Sprite::create("bg.png");
    bg_img->setContentSize(window);
    bg_img->setAnchorPoint(Vec2(0, 0));
    bg_img->setPosition(Vec2(0, 0));
    bg->addChild(bg_img, 1);
    this->addChild(bg, 0);

    slime_layer = Layer::create();
    this->addChild(slime_layer, 1);

    ui = Layer::create();
    this->addChild(ui, 2);

    // 코인 정보
    bg_coins = Sprite::createWithSpriteFrameName("bg_gray.png");
    bg_coins->setContentSize(Size(248, 60));
    bg_coins->setAnchorPoint(Vec2(0, 1));
    bg_coins->setPosition(Vec2(64, window.height - 16));
    this->addChild(bg_coins, 4);

    coin_icon = Sprite::createWithSpriteFrameName("coin_1.png");
    coin_icon->setPosition(Vec2(64, bg_coins->getPositionY() - 30));
    coin_icon->setContentSize(Size(60, 60));
    this->addChild(coin_icon, 5);

    coins = Label::createWithTTF("0", "fonts/CookieRun Regular.ttf", 32, Size::ZERO, TextHAlignment::RIGHT);
    coins->setTextColor(Color4B(0, 0, 0, 255));
    coins->setAnchorPoint(Vec2(1, 0.5));
    coins->setPosition(Vec2(bg_coins->getContentSize().width + 24, bg_coins->getPositionY() - 30));
    this->addChild(coins, 5);

    // 애니메이션 정의 및 버튼 불러오기
    

    SpriteFrame* coin_frame_1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("coin_1.png");
    SpriteFrame* coin_frame_2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("coin_2.png");
    SpriteFrame* coin_frame_3 = SpriteFrameCache::getInstance()->getSpriteFrameByName("coin_3.png");
    SpriteFrame* coin_frame_4 = SpriteFrameCache::getInstance()->getSpriteFrameByName("coin_4.png");
    coin_frames.pushBack(coin_frame_1);
    coin_frames.pushBack(coin_frame_2);
    coin_frames.pushBack(coin_frame_3);
    coin_frames.pushBack(coin_frame_4);

    for (int a = 1; a < 10; a++) {
        string b = "touch_";
        b.append(to_string(a));
        b.append(".png");
        touch_frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(b));
    }
    for (int a = 1; a < 7; a++) {
        string b = "player_";
        b.append(to_string(a));
        b.append(".png");
        player_frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(b));
    }
    /*touch_frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("touch_2.png"));
    touch_frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("touch_3.png"));
    touch_frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("touch_4.png"));
    touch_frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("touch_5.png"));
    touch_frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("touch_6.png"));*/

    auto button = Sprite::createWithSpriteFrameName("button_bottles.png");
    button->setContentSize(Size(80, 80));
    auto selected = Sprite::createWithSpriteFrameName("button_bottles_selected.png");
    selected->setContentSize(Size(80, 80));
    auto main = Sprite::createWithSpriteFrameName("button_main.png");
    main->setContentSize(Size(80, 80));
    auto main_selected = Sprite::createWithSpriteFrameName("button_main_selected.png");
    main_selected->setContentSize(Size(80, 80));
    bottle_list = MenuItemSprite::create(button, selected, CC_CALLBACK_1(Main::bottles_menu, this));
    go_main = MenuItemSprite::create(main, main_selected, CC_CALLBACK_1(Main::main_menu, this));
    menu = Menu::create(bottle_list, go_main, NULL);
    menu->setAnchorPoint(Vec2(1, 1));
    menu->setPosition(Vec2(window.width - 110, window.height - 45));
    menu->alignItemsHorizontally();
    this->addChild(menu, 2);

    // 플레이어
    player = Sprite::createWithSpriteFrameName("player_1.png");
    player->setPosition(Vec2(window.width / 10, window.height / 2));
    ui->addChild(player);

    player_hp = LayerColor::create(Color4B(255, 0, 0, 255), 100.0f, 10.0f);
    player_hp->setPositionY(player->getContentSize().height);
    player->addChild(player_hp);

    //병 메뉴
    bottle_list_layer = Layer::create();
    bottle_list_layer->setContentSize(Size(window.width, window.height / 2 + 100));
    bottle_list_layer->setPosition(Vec2(0, -(window.height / 2) - 100));
    this->addChild(bottle_list_layer, 3);

    auto closed = Sprite::createWithSpriteFrameName("button_close.png");
    closed->setContentSize(Size(80, 80));
    auto close_selected = Sprite::createWithSpriteFrameName("button_close_selected.png");
    close_selected->setContentSize(Size(80, 80));
    close = MenuItemSprite::create(closed, close_selected, CC_CALLBACK_1(Main::menu_close, this));
    close_menu = Menu::create(close, NULL);
    close_menu->setAnchorPoint(Vec2(1, 0));
    close_menu->setPosition(Vec2(window.width - 64, (window.height / 2) + 64));
    bottle_list_layer->addChild(close_menu, 3);

    bg_bottles = Sprite::create("bg_bottles.png");
    bg_bottles->setContentSize(Size(window.width, window.height / 2));
    bg_bottles->setAnchorPoint(Vec2(0, 0));
    bg_bottles->setPosition(Vec2(0, 0));
    bottle_list_layer->addChild(bg_bottles);
    
    normal_bottle = Sprite::createWithSpriteFrameName("normal_bottle.png");
    normal_bottle->setPosition(Vec2(128, (window.height / 2) - normal_bottle->getContentSize().height - 32));
    normal_bottle->setScale(1.2f);
    bottle_list_layer->addChild(normal_bottle, 1);

    normal_bottle_text = Label::createWithTTF("일반 병", "fonts/CookieRun Regular.ttf", 32);
    normal_bottle_text->setPosition(Vec2(128, normal_bottle->getPositionY() - 64));
    normal_bottle_text->setTextColor(Color4B(0, 0, 0, 255));
    bottle_list_layer->addChild(normal_bottle_text, 1);

    normal_bottle_stat = Label::createWithTTF("사용 중", "fonts/CookieRun Regular.ttf", 28);
    normal_bottle_stat->setPosition(Vec2(128, 128));
    normal_bottle_stat->setTextColor(Color4B(0, 0, 0, 255));
    bottle_list_layer->addChild(normal_bottle_stat, 2);

    auto bg_button = Sprite::createWithSpriteFrameName("bg_button.png");
    bg_button->setContentSize(Size(normal_bottle_stat->getContentSize().width + 32, normal_bottle_stat->getContentSize().height + 32));
    auto bg_button_sel = Sprite::createWithSpriteFrameName("bg_button_selected.png");
    bg_button_sel->setContentSize(Size(normal_bottle_stat->getContentSize().width + 32, normal_bottle_stat->getContentSize().height + 32));
    auto bg_button_disable = Sprite::createWithSpriteFrameName("bg_button_selected.png");
    bg_button_disable->setContentSize(Size(normal_bottle_stat->getContentSize().width + 32, normal_bottle_stat->getContentSize().height + 32));

    normal_bottle_select = MenuItemSprite::create(bg_button, bg_button_sel, bg_button_disable, CC_CALLBACK_1(Main::bottle_clicked, this));
    normal_bottle_select->setPosition(normal_bottle_stat->getPosition());
    normal_bottle_select->setEnabled(false);
    bottle_btn_list = Menu::create(normal_bottle_select, NULL);
    bottle_btn_list->setContentSize(window);
    bottle_btn_list->setAnchorPoint(Vec2(0, 0));
    bottle_btn_list->setPosition(Vec2(0, 0));
    bottle_list_layer->addChild(bottle_btn_list, 1);

    // 터치 이벤트 감지 -> android 지원 (iOS도 지원하고싶다...)
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(Main::onTouchesBegan, this);
    listener->onTouchesEnded = CC_CALLBACK_2(Main::onTouchesEnded, this);
    listener->onTouchesMoved = CC_CALLBACK_2(Main::onTouchesMoved, this);
    _eventDispatcher->addEventListenerWithFixedPriority(listener, 1);

    this->scheduleUpdate();
    
    return true;
}

void Main::onTouchesBegan(const std::vector<Touch*>& touches, Event* unused_event)
{
    if (!pause) {
        Sprite* bottle = Sprite::createWithSpriteFrameName("normal_bottle.png");
        bottle->setPosition(Vec2((window.width / 10) - 20, window.height / 2));
        bottle->setAnchorPoint(Vec2(0.5, 0.5));
        bottle->setName("temp");
        ui->addChild(bottle, 2);
    }
}

void Main::onTouchesMoved(const std::vector<Touch*>& touches, Event* unused_event)
{
}

void Main::onTouchesEnded(const std::vector<Touch*>& touches, Event* unused_event)
{
    if (!pause) {
        for (Touch* touch : touches) {
            // 병 생성 & 움직임
            ui->removeChildByName("temp");
            Sprite* bottle = Sprite::createWithSpriteFrameName("normal_bottle.png");
            bottle->setPosition(Vec2((window.width / 10) - 10, window.height / 2));
            bottle->setAnchorPoint(Vec2(0.5, 0.5));
            bottle->setName(to_string(bottles));
            ui->addChild(bottle, 2);
            float x = touch->getLocation().x;
            float y = touch->getLocation().y;
            xp.push_back(x);
            yp.push_back(y);
            float distance = sqrtf((x - ((window.width / 10) - 20)) * (x - ((window.width / 10) - 20)) + (y - window.height / 2) * (y - window.height / 2));
            //단, 이렇게 구한 값은 픽셀값이므로 값이 크기때문에 적당히 줄여서 계산해준다.
            auto action = MoveTo::create(distance / 1000, Vec2(x, y));
            auto action_del = CallFuncN::create(CC_CALLBACK_1(Main::remove_ui, this, bottle));
            ui->getChildByName(to_string(bottles))->runAction(Sequence::create(action, action_del, NULL));
            bottles++;

            // 클릭 이벤트
            Sprite* t = Sprite::createWithSpriteFrameName("touch_1.png");
            t->setContentSize(Size(80, 80));
            t->setScale(0.3f);
            t->setPosition(touch->getLocation());
            Animation* touch_ani = Animation::createWithSpriteFrames(touch_frames, 0.02f);
            Animate* animate = Animate::create(touch_ani);
            Action* action2 = Repeat::create(animate, 1);
            ui->addChild(t);
            t->runAction(action2);
            auto fade = FadeTo::create(0.18f, 0);
            auto scale = ScaleTo::create(0.18f, 0.9f);
            auto action_de = CallFuncN::create(CC_CALLBACK_1(Main::remove_ui, this, t));
            t->runAction(Sequence::create(Spawn::create(fade, scale, NULL), action_de, NULL));

            // 플레이어 애니메이션
            Animation* n_ani = Animation::createWithSpriteFrames(player_frames, 0.02f);
            Animate* animate_n = Animate::create(n_ani);
            auto action_n = Repeat::create(animate_n, 1);
            player->runAction(action_n);
        }
    }
}

void Main::update(float dt)
{
    if (!pause) {
        // 병 날리기
        for (int i = 0; i < bottles; i++) {
            if (xp.size() > i && yp.size() > i) {
                float toX = xp.at(i);
                float toY = yp.at(i);
                auto target = ui->getChildByName(to_string(i));
                if (target != nullptr) {
                    target->setRotation(target->getRotation() + NormalSpeed);
                    Rect targetRect = target->getBoundingBox();
                    // 충돌 감지
                    for (int j = 0; j < slimes; j++) {
                        auto s = slime_layer->getChildByName("s" + to_string(j));
                        if (s != nullptr) {
                            auto hpb = s->getChildByName("sp" + to_string(j));
                            Rect slimeRect = s->getBoundingBox();
                            Rect playerRect = player->getBoundingBox();
                            if (targetRect.intersectsRect(slimeRect)) {
                                ui->removeChildByName(to_string(i));
                                //Director::getInstance()->getTextureCache()->removeUnusedTextures();
                                slime_hp[j] -= NormalBottle;
                                if (hpb != nullptr) {
                                    hpb->setContentSize(Size(slime_hp[j] * 3, 10));
                                }
                                auto to = TintTo::create(0.05f, Color3B(255, 0, 0));
                                auto an = TintTo::create(0.1f, Color3B(Color4B(255, 255, 255, 255)));
                                s->runAction(Sequence::create(to, an, NULL));
                                if (slime_hp[j] <= 0 && !is_defeat[j]) {
                                    is_defeat[j] = true;
                                    s->stopAllActions();
                                    Animation* coin_ani = Animation::createWithSpriteFrames(coin_frames, 0.2f);
                                    Animate* animate_coin = Animate::create(coin_ani);
                                    coin_action = RepeatForever::create(animate_coin);
                                    auto c = Sprite::createWithSpriteFrameName("coin_1.png");
                                    c->setPosition(s->getPosition());
                                    slime_layer->addChild(c);
                                    c->runAction(coin_action);
                                    auto jump = JumpTo::create(0.5, c->getPosition(), 50, 1);
                                    auto fade = FadeTo::create(0.2, 0);
                                    auto action_del = CallFuncN::create(CC_CALLBACK_1(Main::remove_slime, this, c));
                                    c->runAction(Sequence::create(jump, fade, action_del, NULL));
                                    auto action1 = FadeTo::create(0.1f, 0);
                                    auto action3 = CallFuncN::create(CC_CALLBACK_1(Main::remove_slime, this, s));
                                    auto action4 = Sequence::create(action1, action3, NULL);
                                    coin++;
                                    saved_data->setDoubleForKey("val1", coin);
                                    if (hpb != nullptr) {
                                        hpb->runAction(Sequence::create(action1, NULL));
                                    }
                                    s->runAction(action4);
                                    exp++;
                                    play_coin++;
                                }
                            }
                        }
                    }
                }
            }
        }

        coins->setString(to_string((int)coin));

        // 슬라임 생성
        if (random(0, 100) == 50) {
            auto slime = Sprite::createWithSpriteFrameName("slime1.png");
            slime->setPosition(Vec2(window.width, random(100, (int)window.height - 150)));
            slime->setName("s" + to_string(slimes));
            slime_layer->addChild(slime);
            SpriteFrame* slime_frame_1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("slime1.png");
            SpriteFrame* slime_frame_2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("slime2.png");
            slime_a.pushBack(slime_frame_1);
            slime_a.pushBack(slime_frame_2);
            Animation* slime_ani = Animation::createWithSpriteFrames(slime_a, 0.2f);
            Animate* animate = Animate::create(slime_ani);
            slime_action = RepeatForever::create(animate);
            slime->runAction(slime_action);
            LayerColor* hp_bar = LayerColor::create(Color4B(255, 0, 0, 255), 90.0f, 10.0f);
            hp_bar->setPositionY(slime->getContentSize().height);
            hp_bar->setName("sp" + to_string(slimes));
            slime->addChild(hp_bar);
            slimes++;
            slime_hp.push_back(30);
            slime_frame.push_back(frame);
            slime_data.push_back(slime);
            is_defeat.push_back(false);
            auto slime_move = MoveTo::create(10.0f, Vec2(window.width / 10 + (player->getContentSize().width / 2), window.height / 2));
            auto player_damage = CallFuncN::create(CC_CALLBACK_1(Main::player_damage, this, player));
            slime->runAction(Sequence::create(slime_move, player_damage, NULL));
        }
    }
}

void Main::bottles_menu(Ref* sender)
{
    if (pause) {
        auto move = MoveTo::create(0.2f, Vec2(0, -(window.height / 2) - 100));
        bottle_list_layer->runAction(EaseInOut::create(move, 2.0f));
        for (int i = 0; i < slimes; i++) {
            auto s = slime_layer->getChildByName("s" + to_string(i));
            if (s != nullptr) {
                s->resume();
            }
        }
    }
    else {
        auto move = MoveTo::create(0.2f, Vec2(0, 0));
        bottle_list_layer->runAction(EaseInOut::create(move, 2.0f));
        for (int i = 0; i < slimes; i++) {
            auto s = slime_layer->getChildByName("s" + to_string(i));
            if (s != nullptr) {
                s->pause();
            }
        }
    }
    pause = !pause;
}

void Main::main_menu(Ref* sender)
{
    if (!pause) {
        this->unscheduleUpdate();
        pause = true;
    }
    else {
    }
    Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ALL_AT_ONCE);
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, Robby::createScene()));

}

void Main::menu_close(Ref* sender)
{
    if (pause) {
        auto move = MoveTo::create(0.2f, Vec2(0, -(window.height / 2) - 100));
        bottle_list_layer->runAction(EaseInOut::create(move, 2.0f));
        pause = !pause;
        for (int i = 0; i < slimes; i++) {
            auto s = slime_layer->getChildByName("s" + to_string(i));
            if (s != nullptr) {
                s->resume();
            }
        }
    }
}

void Main::remove_slime(Ref* sender, Ref* Object)
{
    slime_layer->removeChild((Sprite*)sender);
}

void Main::remove_ui(Ref* sender, Ref* Object)
{
    ui->removeChild((Sprite*)sender);
}

void Main::player_damage(Ref* sender, Ref* Object)
{
    auto to = (Sprite*)sender; // 슬라임
    auto from = (Sprite*)Object; // 플레이어

    auto tao = TintTo::create(0.05f, Color3B(255, 5, 5));
    auto aan = TintTo::create(0.1f, Color3B(Color4B(255, 255, 255, 255)));
    from->runAction(Sequence::create(tao, aan, NULL));
    slime_layer->removeChild(to, false);
    playerHp -= 5;
    player_hp->setContentSize(Size((float)playerHp, 10.0f));
    if (playerHp <= 0) {
        game_over();
    }
}

void Main::bottle_clicked(Ref* sender)
{
}

void Main::game_over()
{
    saved_data->setDoubleForKey("val2", play_coin);
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GameOver::createScene()));
}

/* int random()
{
    srand((unsigned int)time(NULL));
    int num = rand();
    return (int)num % 10;
} */