#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "Lemmings/Lemming.h"

#include <vector>

class Lemming;

class GameScene : public cocos2d::Scene
{
public:

	static GameScene* createScene() { return GameScene::create(); }


	GameScene(/* args */) {}
	~GameScene() {}

	virtual bool init() override;

	virtual void update(float d) override;

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	void menuCloseCallback(Ref *pSender);
	void exitScene(Ref *pSender);

	CREATE_FUNC(GameScene);



	/// Is tile collidable.
	/// Out-of-bounds coordinates always count as collision, as to keep lemmings from clipping out of the level.
	bool isTileCollidable(int tileX, int tileY) const;

	bool isTileCollidable(float worldX, float worldY) const;

	bool destroyTile(int tileX, int tileY);

	void selectBasherTask(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void selectBlockerTask(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);



private:

	static const int NUM_BUTTONS = 6;

	cocos2d::Sprite* m_cursorSprite;
	cocos2d::ui::Button* m_tasksButtons[NUM_BUTTONS - 1];
	cocos2d::Label* m_remainingTasksLabels[NUM_BUTTONS - 1];

	cocos2d::TMXTiledMap* m_tileMap;
	cocos2d::TMXLayer* m_tileMapLayer;

	std::vector<Lemming*> m_lemmings;

	Lemming::State selectedState;
	int speedUp;
	int m_remainingTasks[NUM_BUTTONS - 1];

	// Lemmings spawn.
	int m_maxLemmings;
	int m_spawnedLemmings;
	float m_spawnTimer;
};
