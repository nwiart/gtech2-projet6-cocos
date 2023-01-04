#include "SettingsScene.h"
#include "TitleMenuScene.h"
#include "AppDelegate.h"
#include "Scenes/GameScene.h"

#include <math.h>

USING_NS_CC;
using namespace cocos2d::ui;

SettingsScene::SettingsScene()
{
}

SettingsScene::~SettingsScene()
{
}

bool SettingsScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    // Aliases
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Setup the background
    /*Sprite* background = Sprite::create("background.png");
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, 0);

    // Setup the title
    Sprite* title = Sprite::create("title.png");
    title->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(title, 1);*/

    // Setup the buttons
    Button* settingsButton = Button::create("CloseNormal.png");
    settingsButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    //settingsButton->addTouchEventListener(CC_CALLBACK_1(TitleMenu::changeToSettingsScene, this));
    this->addChild(settingsButton, 2);

    Button* titleButton = Button::create("exit.png");
    titleButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 - 50));
    titleButton->addTouchEventListener(CC_CALLBACK_1(SettingsScene::changeToTitleScene, this));
    this->addChild(titleButton, 2);

    /*Button* exitButton = Button::create("Button_Disable.png");
    exitButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 - 100));
    exitButton->addTouchEventListener(CC_CALLBACK_1(SettingsScene::exitScene, this));
    this->addChild(exitButton, 2);*/

    return true;
}

void SettingsScene::changeToTitleScene(Ref* pSender)
{
    // Go to TitleMenu
    AppDelegate::openScene<TitleMenu>();
}

void SettingsScene::exitScene(Ref* pSender)
{
    // Remove the actual Scene
    Director::getInstance()->popScene();
}