#include "TitleMenu.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <iostream>

using namespace cocos2d::ui;

// FLT_EPSILON pour comparer des floats

using namespace cocos2d;
TitleMenu* TitleMenu::createScene()
{
    return TitleMenu::create();
}

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
    GameScene = Scene::create();
    GameScene->retain();
        
    SettingsScene = Scene::create();
	SettingsScene->retain();

    //titleMenu->retain();

   /* titleMenu->retain();*/

        
        cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
        
		Button* buttonPlay = Button::create("Button_Normal.png", "Button_Press.png", "Button_Disable.png");
		buttonPlay->setTitleText("Play");
		buttonPlay->setSizePercent(Vec2(1, 0.5));
		buttonPlay->setTitleColor(Color3B::RED);
        
        buttonPlay->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
            switch (type)
            {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                Director::getInstance()->pushScene(TransitionFade::create(2, GameScene, Color3B(0, 255, 255)));
				//TitleMenu::changeScene(sender);
                break;
            default:
                break;
            }
            });
        this->addChild(buttonPlay);
		buttonPlay->setPosition(Vec2(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.5 + origin.y));
        
        Button* buttonSettings = Button::create("Button_Normal.png", "Button_Press.png", "Button_Disable.png");
		buttonSettings->setTitleText("Settings");
		buttonSettings->setSizePercent(Vec2(1, 0.5));
		buttonSettings->setTitleColor(Color3B::RED);
		buttonSettings->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
                
				Director::getInstance()->pushScene(TransitionFade::create(2, SettingsScene, Color3B(0, 255, 255)));
                 break;
			default:
				break;
			}
        });
		titleMenu->addChild(buttonSettings);
		buttonSettings->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 100));
        

        Button* buttonExit = Button::create("Button_Normal.png", "Button_Press.png", "Button_Disable.png");
		buttonExit->setTitleText("Exit");
		buttonExit->setSizePercent(Vec2(1, 0.5));
		buttonExit->setTitleColor(Color3B::RED);
        buttonExit->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
            switch (type)
            {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
				Director::getInstance()->end();
				break;
			default:
				break;
            }
        });
        titleMenu->addChild(buttonExit);
        buttonExit->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 - 200));

        Button* buttonReturn = Button::create("Button_Normal.png", "Button_Press.png", "Button_Disable.png");
        buttonReturn->setTitleText("Play");
        buttonReturn->setSizePercent(Vec2(1, 0.5));
        buttonReturn->setTitleColor(Color3B::RED);

        buttonReturn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
            switch (type)
            {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                titleMenu->retain();
                Director::getInstance()->pushScene(TransitionFade::create(2, titleMenu, Color3B(0, 255, 255)));
                
                //TitleMenu::changeScene(sender);
                break;
            default:
                break;
            }
            });
        GameScene->addChild(buttonReturn);
        buttonReturn->setPosition(Vec2(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.5 + origin.y));
        


	/*	MenuItemFont* test = MenuItemFont::create("test", CC_CALLBACK_1(TitleMenu::menuCloseCallback, this));
		test->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 300));
        titleMenu->addChild(test);*/
        
        //auto exitItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",CC_CALLBACK_1(TitleMenu::menuCloseCallback, this));
        //auto launch = MenuItemImage::create("Button_Normal.png", "Button_Disable.png", CC_CALLBACK_1(TitleMenu::launchGame, this));
        //auto menu = Menu::create(exitItem,launch, NULL);
	/*	exitItem->setPosition(Vec2(50, 100));
        launch->setPosition(Vec2(0, 0));
		menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));*/
        //this->addChild(menu, 1);
        log(" --------------------------------------- Loaded Tilte Menu ------------------------------------------ ");
        return true;

}

void TitleMenu::changeScene(Ref* pSender)
{
    // Create new scene 

	Director::getInstance()->pushScene(TransitionFade::create(2, GameScene, Color3B(0, 255, 255)));
	log(" --------------------------------------- Launch Game ------------------------------------------ ");
}

void TitleMenu::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}


