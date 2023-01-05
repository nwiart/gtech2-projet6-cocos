#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class TitleMenu : public cocos2d::Scene
{

public:
    TitleMenu(/* args */);
	~TitleMenu();

	
	static TitleMenu* createScene() { return TitleMenu::create(); }
	virtual bool init() override;

	void launchGame(Ref* pSender);

	void changeToSettingsScene(Ref* pSender);
	
	void exitScene(Ref* pSender);

	
	
	

	CREATE_FUNC(TitleMenu);

	TitleMenu* titleMenu;
	

};


