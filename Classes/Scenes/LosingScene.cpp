#include "LosingScene.h"
#include "AppDelegate.h"
#include "TitleMenuScene.h"
#include "GameScene.h"

USING_NS_CC;
using namespace cocos2d::ui;

LosingScene::LosingScene()
{
}

LosingScene::~LosingScene()
{
}

bool LosingScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    // Win Title
    Label *losingTitle = Label::createWithTTF("You Lost....", "fonts/Marker Felt.ttf", 52);
    losingTitle->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 250));
    this->addChild(losingTitle, 1);

    // Win text
    Label *losText = Label::createWithTTF("You failed in your faithful mission, to guide the lemmings to the magnificient landscape of LemmingLand.", "fonts/Marker Felt.ttf", 20);
    losText->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 100));
    this->addChild(losText, 1);

    // Show stats
	Label* losStats = Label::createWithTTF("Stats : ", "fonts/Marker Felt.ttf", 36);
	losStats->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(losStats, 1);
    
	// Time spent
	Label* winTime = Label::createWithTTF("Time spent : ", "fonts/Marker Felt.ttf", 24);
	winTime->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 50));
	this->addChild(winTime, 1);
    
    // Lemmings saved
	Label* wLemmings = Label::createWithTTF("Lemmings saved : ", "fonts/Marker Felt.ttf", 24);
	wLemmings->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 85));
	this->addChild(wLemmings, 1);

    Button *titleButton = Button::create("play.png", "play.png");
    titleButton->setTitleFontSize(24);
    titleButton->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 200));
    titleButton->addTouchEventListener(CC_CALLBACK_1(LosingScene::changeToTitleScene, this));
    this->addChild(titleButton);

    Button *exitButton = Button::create("exit.png", "exit.png");
    exitButton->setTitleFontSize(24);
    exitButton->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 250));
    exitButton->addTouchEventListener(CC_CALLBACK_1(LosingScene::exitScene, this));
    this->addChild(exitButton);

    return true;
}

void LosingScene::changeToTitleScene(Ref *pSender)
{
    // Go to TitleMenu
    AppDelegate::openScene<TitleMenu>();
}

void LosingScene::exitScene(Ref *pSender)
{
    // Exit the game
    Director::getInstance()->end();
}