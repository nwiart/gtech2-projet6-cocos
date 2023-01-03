#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GameScene : public cocos2d::Scene
{
public:

    static GameScene* createScene() { return GameScene::create(); }


    GameScene(/* args */) {}
    ~GameScene() {}

    virtual bool init() override;

    virtual void update(float d) override;

    void menuCloseCallback(Ref *pSender);
    void exitScene(Ref *pSender);

    CREATE_FUNC(GameScene);

private:

    static const int NUM_BUTTONS = 6;

    cocos2d::Sprite* m_cursorSprite;
    cocos2d::Label* m_remainingTasksLabels[NUM_BUTTONS - 1];

    cocos2d::TMXTiledMap* m_tileMap;

    bool speedUp;
};
