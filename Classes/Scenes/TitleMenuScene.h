#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class TitleMenu : public cocos2d::Scene
{

public:
    TitleMenu(/* args */);
	~TitleMenu();

	
	static TitleMenu* createScene();
	virtual bool init();


	void changeToGameScene(Ref* pSender);
	void changeToSettingsScene(Ref* pSender);
	
	
	void changeScene(Ref* pSender);

	void launchGame(Ref* pSender);
	void menuCloseCallback(Ref* pSender);

	void exitScene(Ref* pSender);

	
	
	

	CREATE_FUNC(TitleMenu);

	TitleMenu* titleMenu;
	Scene* GameScene;
	Scene* SettingsScene;

private: 





};


