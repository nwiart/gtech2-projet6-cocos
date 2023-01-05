#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "Lemmings/Lemming.h"

#include <vector>

class Lemming;

class GameScene : public cocos2d::Scene
{
public:
    static GameScene *createScene() { return GameScene::create(); }

    GameScene(/* args */) {}
    ~GameScene() {}

    virtual bool init() override;

    virtual void update(float d) override;

    void changeToPauseScene(Ref *pSender);
    void changeToGameScene(Ref *pSender);
    void menuCloseCallback(Ref *pSender);
    void exitScene(Ref *pSender);
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);

    CREATE_FUNC(GameScene);

    /// Is tile collidable.
    /// Out-of-bounds coordinates always count as collision, as to keep lemmings from clipping out of the level.
    bool isTileCollidable(int tileX, int tileY) const;

    bool isTileCollidable(float worldX, float worldY) const;

    bool destroyTile(int tileX, int tileY);

    void selectBasherTask(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
    void selectBlockerTask(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);

private:
    static const int NUM_BUTTONS = 6;

    cocos2d::Sprite *m_cursorSprite;
    cocos2d::ui::Button *m_remainingTasksButtons[NUM_BUTTONS - 1];
    cocos2d::Label *m_remainingTasksLabels[NUM_BUTTONS - 1];

    cocos2d::TMXTiledMap *m_tileMap;
    cocos2d::TMXLayer *m_tileMapLayer;

    std::vector<Lemming *> m_lemmings;

    bool speedUp;
    Lemming::State selectedState;

    cocos2d::ui::Button *m_resumeButton;
	cocos2d::ui::Button* m_exitButton;
    cocos2d::LayerColor *m_bg;
    bool PAUSED = false;
};
