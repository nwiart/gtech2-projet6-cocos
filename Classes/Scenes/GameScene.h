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


	void changeToGameScene(Ref *pSender);
	void menuCloseCallback(Ref *pSender);
	void exitScene(Ref *pSender);
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);

    // Getters of Lemmings
    const int getTotalNumberOfLemmings() const { return m_spawnedLemmings; }
    const int getRemainingNumberOfLemmings() const { return m_remainingLemmings; }

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

	cocos2d::Sprite* m_cursorSprite;
	cocos2d::ui::Button* m_tasksButtons[NUM_BUTTONS - 1];
	cocos2d::Label* m_remainingTasksLabels[NUM_BUTTONS - 1];

	cocos2d::TMXTiledMap *m_tileMap;
	cocos2d::TMXLayer *m_tileMapLayer;

	std::vector<Lemming *> m_lemmings;

	Lemming::State selectedState;
	int speedUp;
	int m_remainingTasks[NUM_BUTTONS - 1];



    cocos2d::Label* m_remainingLemmingsLabel = 0;
	cocos2d::Label* m_savedLemmingsLabel = 0;
	cocos2d::Label* m_winLemmingsLabel = 0;
		

    cocos2d::ui::Button *m_resumeButton;
    cocos2d::ui::Button *m_exitButton;
    cocos2d::LayerColor *m_bg;
    bool PAUSED = false;

	// Lemmings spawn.
	int m_maxLemmings; // maximum number of lemmings that can be spawned
	int m_spawnedLemmings; // lemmings that have been spawned
    int m_remainingLemmings; // lemmings that have not exited the level
    int m_deadLemmings; // lemmings that have died
    int m_savedLemmings; // lemmings that have been saved
    int m_winLemmings = 10; // lemmings that have to be saved to win
	float m_spawnTimer;


};
