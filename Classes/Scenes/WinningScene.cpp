#include "WinningScene.h"
#include "AppDelegate.h"
#include "TitleMenuScene.h"

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

    /*Sprite *background = Sprite::create("winning.png");
    background->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background);*/

    Button *titleButton = Button::create("play.png", "play.png");
    titleButton->setTitleText("Back to Title");
    titleButton->setTitleFontSize(24);
    titleButton->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 100));
    titleButton->addTouchEventListener(CC_CALLBACK_1(WinningScene::changeToTitleScene, this));
    this->addChild(titleButton);

    Button *exitButton = Button::create("exit.png", "exit.png");
    exitButton->setTitleText("Exit");
    exitButton->setTitleFontSize(24);
    exitButton->setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 200));
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