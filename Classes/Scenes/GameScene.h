#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GameScene : public cocos2d::Scene
{
public:
    GameScene(/* args */);
    ~GameScene();

    void menuCloseCallback(Ref *pSender);
    void exitScene(Ref *pSender);

    CREATE_FUNC(GameScene);

private:
};