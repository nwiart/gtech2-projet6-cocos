// #include "Scenes/TitleMenuScene.h"
// #include "cocos2d.h"
//
// #include "Lemmings/Lemming.h"
// #include "Lemmings/Animation/SpriteAnimations.h"
//
// using namespace cocos2d;
// TitleMenu* TitleMenu::createScene()
//{
//	return TitleMenu::create();
// }

bool TitleMenu::init()
{
    if (!Scene::init())
    {
        return false;
    }

    SpriteAnimations s;

    Scene *secondScene = Scene::create();
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    // auto button = cocos2d::ui::Button::create("Button_Press.png");

    auto exitItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(TitleMenu::menuCloseCallback, this));
    auto launch = MenuItemImage::create("Button_Normal.png", "Button_Disable.png", CC_CALLBACK_1(TitleMenu::launchGame, this));
    auto menu = Menu::create(exitItem, launch, NULL);
    exitItem->setPosition(Vec2(50, 100));
    launch->setPosition(Vec2(0, 0));
    menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(menu, 1);
    log(" --------------------------------------- Loaded Tilte Menu ------------------------------------------ ");

    Lemming *l = Lemming::create();
    l->runAction(s.anim_umbrellafloat);
    l->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    l->setScale(10);
    this->addChild(l, 1);

    return true;
}

void TitleMenu::launchGame(Ref *pSender)
{

    log(" --------------------------------------- Launch Game ------------------------------------------ ");

    // Create new scene
    Scene *secondScene = Scene::create();
    Director::getInstance()->pushScene(TransitionFade::create(2, secondScene, Color3B(0, 255, 255)));
}

void TitleMenu::menuCloseCallback(Ref *pSender)
{
    // Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}
