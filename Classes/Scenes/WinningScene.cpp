#include "WinningScene.h"
#include "AppDelegate.h"
#include "TitleMenuScene.h"
#include "GameScene.h"

USING_NS_CC;
using namespace cocos2d::ui;

WinningScene::WinningScene()
{
}

WinningScene::~WinningScene()
{
}

bool WinningScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    // Win Title
    Label *winTitle = Label::createWithTTF("You Won!", "fonts/Marker Felt.ttf", 52);
    winTitle->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 250));
    this->addChild(winTitle, 1);

    // Win text
    Label *winText = Label::createWithTTF("You saved all the lemmings. What a beautiful soul you have. Thanks to you, they will live their joyful life in other worlds.", "fonts/Marker Felt.ttf", 20);
    winText->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 100));
    this->addChild(winText, 1);

    // Show stats
	Label* winStats = Label::createWithTTF("Stats : ", "fonts/Marker Felt.ttf", 36);
	winStats->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(winStats, 1);
    
	// Time spent
	Label* winTime = Label::createWithTTF("Time spent : ", "fonts/Marker Felt.ttf", 24);
	winTime->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 50));
	this->addChild(winTime, 1);
    
    // Lemmings saved
	Label* wLemmings = Label::createWithTTF("Lemmings saved : %i", "fonts/Marker Felt.ttf", 24);
	wLemmings->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 85));
	this->addChild(wLemmings, 1);

    Button *titleButton = Button::create("play.png", "play.png");
    titleButton->setTitleFontSize(24);
    titleButton->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 200));
    titleButton->addTouchEventListener(CC_CALLBACK_1(WinningScene::changeToTitleScene, this));
    this->addChild(titleButton);

    Button *exitButton = Button::create("exit.png", "exit.png");
    exitButton->setTitleFontSize(24);
    exitButton->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 250));
    exitButton->addTouchEventListener(CC_CALLBACK_1(WinningScene::exitScene, this));
    this->addChild(exitButton);

    return true;
}

void WinningScene::changeToTitleScene(Ref *pSender)
{
    // Go to TitleMenu
    AppDelegate::openScene<TitleMenu>();
}

void WinningScene::exitScene(Ref *pSender)
{
    // Exit the game
    Director::getInstance()->end();
}