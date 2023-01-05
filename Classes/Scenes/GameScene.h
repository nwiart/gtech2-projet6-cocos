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

    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);

    CREATE_FUNC(GameScene);

    /// Is tile collidable.
    /// Out-of-bounds coordinates always count as collision, as to keep lemmings from clipping out of the level.
    bool isTileCollidable(int tileX, int tileY) const;

    bool isTileCollidable(float worldX, float worldY) const;

    bool destroyTile(int tileX, int tileY);

    void explode(int tileX, int tileY);

    // Task selection functions
    void selectBasherTask(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
    void selectBlockerTask(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
    void selectBomberTask(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
    void selectDiggerTask(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
    void selectUmbrellaTask(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);

    // Getter of remaining lemmings
    int getRemainingLemmings() const { return m_remainingLemmings; }

    // Getter of timeSpent
    char *getTimeSpent() const { return m_timeSpent; }

private:
    static const int NUM_BUTTONS = 6;

    // Sprites
    cocos2d::Sprite *m_exitSprite;
    cocos2d::Sprite *m_cursorSprite;

    // Tasks buttons & fields
    cocos2d::ui::Button *m_tasksButtons[NUM_BUTTONS - 1];
    cocos2d::Label *m_remainingTasksLabels[NUM_BUTTONS - 1];

    // Map variables
    cocos2d::TMXTiledMap *m_tileMap;
    cocos2d::TMXLayer *m_tileMapLayer;

    // Labels for counting lemmings.
    cocos2d::Label *m_remainingLemmingsLabel;
    cocos2d::Label *m_savedLemmingsLabel;
    cocos2d::Label *m_winLemmingsLabel;

    // Vector of lemmings.
    std::vector<Lemming *> m_lemmings;
    std::vector<Lemming *> m_blockingLemmings;
    std::vector<Lemming *> m_explodingLemmings;

    Lemming::State selectedState;
    int speedUp;

    int m_remainingTasks[NUM_BUTTONS - 1];

    int m_maxLemmings;           // maximum number of lemmings that can be spawned
    int m_spawnedLemmings;       // lemmings that have been spawned
    int m_remainingLemmings = 0; // lemmings that have not exited the level
    int m_deadLemmings = 0;      // lemmings that have died
    int m_savedLemmings = 0;     // lemmings that have been saved
    int m_winLemmings = 5;       // lemmings that have to be saved to win
    float m_spawnTimer;
    char *m_timeSpent = ""; // time spent in the level

    // Paused menu variables
    cocos2d::ui::Button *m_resumeButton;
    cocos2d::ui::Button *m_exitButton;
    cocos2d::ui::Button *m_restartButton;
    cocos2d::LayerColor *m_bg;
    bool PAUSED = false;
};
