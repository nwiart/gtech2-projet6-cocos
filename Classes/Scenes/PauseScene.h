#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include <vector>

class PauseScene : public cocos2d::Scene
{
public:
    static PauseScene* createScene() { return PauseScene::create(); }

    PauseScene(/* args */);
    ~PauseScene();

    virtual bool init() override;
    
    void changeToGameScene(Ref* pSender);
    void exitScene(Ref* pSender);
    void menuCloseCallback(Ref* pSender);

    CREATE_FUNC(PauseScene);

};