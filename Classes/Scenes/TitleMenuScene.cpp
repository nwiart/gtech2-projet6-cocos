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
   
    // Main title
	Sprite* title = Sprite::create("Lemmings-Title.png");
	title->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 150));
    title->setScale(1.5);
	this->addChild(title, 0);

    // Setup the buttons
    Button* playButton = Button::create("play.png");
    playButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 75));
    playButton->addTouchEventListener(CC_CALLBACK_1(TitleMenu::launchGame, this));
    this->addChild(playButton, 2);

    Button* settingsButton = Button::create("options.png");
    settingsButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 - 145));
    settingsButton->addTouchEventListener(CC_CALLBACK_1(TitleMenu::changeToSettingsScene, this));
    this->addChild(settingsButton, 2);

    Button* exitButton = Button::create("exit.png");
    exitButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 - 215));
    exitButton->addTouchEventListener(CC_CALLBACK_1(TitleMenu::exitScene, this));
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

void TitleMenu::exitScene(Ref* pSender)
{
    Director::getInstance()->end();
}