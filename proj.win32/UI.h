#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class TitleMenu : public cocos2d::Scene
{

public:
    TitleMenu(/* args */);
	static TitleMenu* createScene();
	virtual bool init();

	void launchGame(Ref* pSender);
	void menuCloseCallback(Ref* pSender);
	void changeScene(Scene* pSender);
	void exitScene(Ref* pSender);
	cocos2d::Label* createLabel(std::string text, int fontSize, cocos2d::Color3B color, cocos2d::Vec2 position);
	cocos2d::Label* menuLabel;
	
	
	~TitleMenu();

	CREATE_FUNC(TitleMenu);

private: /* data */

//std::vector<MenuItem*> MenuItems;



};


