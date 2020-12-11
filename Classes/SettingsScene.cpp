#include "SettingsScene.h"
#include "RobbyScene.h"

Scene* Settings::createScene()
{
    return Settings::create();
}

bool Settings::init()
{
    /*if (!Scene::init()) {
        return false;
    }*/

    return true;
}