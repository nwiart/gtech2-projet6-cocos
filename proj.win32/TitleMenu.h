#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class TitleMenu : public cocos2d::Scene
{

public:
    TitleMenu(/* args */);
	static TitleMenu* createScene();
	virtual bool init();

	void changeScene(Ref* pSender);
	void menuCloseCallback(Ref* pSender);
	void changeScene(Scene* pSender);
	
	
	~TitleMenu();

	CREATE_FUNC(TitleMenu);

	TitleMenu* titleMenu;
	Scene* GameScene;
	Scene* SettingsScene;

private: /* data */

//std::vector<MenuItem*> MenuItems;



};


