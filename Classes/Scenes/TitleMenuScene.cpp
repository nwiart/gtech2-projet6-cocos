#include "TitleMenuScene.h"
#include "AppDelegate.h"
#include "GameScene.h"
#include "SettingsScene.h"

#include <math.h>

USING_NS_CC;
using namespace cocos2d::ui;

TitleMenu::TitleMenu()
{
}

TitleMenu::~TitleMenu()
{
}



bool TitleMenu::init()
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
    log("-------------------------- Title Menu ----------------------------------");

    // Setup the buttons
    Button* playButton = Button::create("play.png");
    playButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    playButton->addTouchEventListener(CC_CALLBACK_1(TitleMenu::launchGame, this));
    this->addChild(playButton, 2);

    Button* settingsButton = Button::create("options.png");
    settingsButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 - 50));
    settingsButton->addTouchEventListener(CC_CALLBACK_1(TitleMenu::changeToSettingsScene, this));
    this->addChild(settingsButton, 2);

    Button* exitButton = Button::create("exit.png");
    exitButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 - 100));
    exitButton->addTouchEventListener(CC_CALLBACK_1(TitleMenu::menuCloseCallback, this));
    this->addChild(exitButton, 2);

    return true;
}

void TitleMenu::launchGame(Ref* pSender)
{
    AppDelegate::openScene<GameScene>();
}

void TitleMenu::changeToSettingsScene(Ref* pSender)
{
    AppDelegate::openScene<SettingsScene>();
}

void TitleMenu::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}