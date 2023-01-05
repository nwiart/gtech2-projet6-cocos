#include "PauseScene.h"
#include "TitleMenuScene.h"
#include "SettingsScene.h"
#include "GameScene.h"
#include "AppDelegate.h"

#include "ui/CocosGUI.h"
#include <math.h>

USING_NS_CC;
using namespace cocos2d::ui;

PauseScene::PauseScene(/* args */)
{
}

PauseScene::~PauseScene()
{
}

bool PauseScene::init()
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

    Button *settingsButton = Button::create("CloseNormal.png");
    settingsButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    // settingsButton->addTouchEventListener(CC_CALLBACK_1(TitleMenu::changeToSettingsScene, this));
    this->addChild(settingsButton, 2);

    Button *exitButton = Button::create("resume.png");
    exitButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 - 50));
    exitButton->addTouchEventListener(CC_CALLBACK_1(PauseScene::changeToGameScene, this));
    this->addChild(exitButton, 2);

    Button *exitGameButton = Button::create("exit.png");
    exitGameButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 - 100));
    exitGameButton->addTouchEventListener(CC_CALLBACK_1(PauseScene::menuCloseCallback, this));
    this->addChild(exitGameButton, 2);

    return true;
}

void PauseScene::changeToGameScene(Ref *pSender)
{
    // Go to the Game Scene
    AppDelegate::openScene<GameScene>();
}

void PauseScene::exitScene(Ref *pSender)
{
    // Remove the actual Scene
    Director::getInstance()->popScene();
}

void PauseScene::menuCloseCallback(Ref *pSender)
{
    // Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}
