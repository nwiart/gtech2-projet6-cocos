#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GameScene : public cocos2d::Scene
{
public:

    static GameScene* createScene() { return GameScene::create(); }


    GameScene(/* args */);
    ~GameScene();

    virtual bool init() override;

    void menuCloseCallback(Ref *pSender);
    void exitScene(Ref *pSender);

    CREATE_FUNC(GameScene);

private:


    cocos2d::Sprite* m_cursorSprite;
};