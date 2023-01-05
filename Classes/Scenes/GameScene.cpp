#include "GameScene.h"
#include "AppDelegate.h"


#include "Lemmings/Lemming.h"

#include "ui/CocosGUI.h"

#include <math.h>

USING_NS_CC;
using namespace cocos2d::ui;


bool GameScene::init()
{
	// Parent call.
	if (!Scene::init()) {
		return false;
	}

	// Default values.
	speedUp = 0;
	selectedState = Lemming::STATE_NONE;

	//this->setColor(Color3B(40, 127, 255));

	Size screenSize = Director::getInstance()->getVisibleSize();
	int width = screenSize.width / NUM_BUTTONS;

	m_tileMap = TMXTiledMap::create("maps/testmap.tmx");
	m_tileMap->setPosition(Vec2(0, width));
	m_tileMapLayer = m_tileMap->getLayer("Calque de Tuiles 1");
	//m_tileMap->setScale(2);
	this->addChild(m_tileMap);

	//for (int i = 0; i < 10; ++i) {
	//	Lemming* l = Lemming::create();
 //       m_remainingLemmings++;
	//	//l->setScale(4);
	//	l->setPosition(Vec2((20 +i) * 16, 5 * 16 + 1));
	//	l->setState(i == 0 ? Lemming::STATE_BLOCKER : Lemming::STATE_WALK);
	//	m_lemmings.push_back(l);
	//	m_tileMap->addChild(l);
	//}
	m_maxLemmings = 30;
	m_spawnedLemmings = 0;
	m_spawnTimer = 0.0F;


	// Create cursor sprite.
	m_cursorSprite = Sprite::create("cursor.png");

	// Create buttons and remaining count.
	{
		const char* actionButtonTextures[NUM_BUTTONS] = {
			"task_basher.png",
			"task_blocker.png",
			"CloseNormal.png",
			"CloseNormal.png",
			"CloseNormal.png",
			"CloseNormal.png",
		};

		// UI BUTTON
		////// Aliases
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		Button* titleButton = Button::create("pause.png");
		titleButton->setPosition(Vec2(visibleSize.width - 75, visibleSize.height - 20));
		titleButton->addTouchEventListener(
			[&](Ref* sender, Widget::TouchEventType type) {

				if (type == Widget::TouchEventType::ENDED) {
					PAUSED = true;
					Director::getInstance()->getScheduler()->setTimeScale(speedUp ? 2 : 1);
				}
			}
		);
		this->addChild(titleButton, 2);



		////////////// PAUSED GAME UI /////////////////////////

		// Create the background color of the pause menu
		m_bg = LayerColor::create(cocos2d::Color4B(50, 50, 50, 200));
		m_bg->setContentSize(cocos2d::Size(visibleSize.width, visibleSize.height));

		
		// Create the resume button
		m_resumeButton = Button::create("resume.png");
		m_resumeButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		m_resumeButton->addTouchEventListener(
			[&](Ref* sender, Widget::TouchEventType type) {

				if (type == Widget::TouchEventType::ENDED) {
					m_bg->setVisible(false);
					m_resumeButton->setVisible(false);
                    m_exitButton->setVisible(false);
					PAUSED = false;
					Director::getInstance()->startAnimation();
				}
			}
		);

		// Create the quit button
		m_exitButton = Button::create("exit.png");
		m_exitButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 100));
		m_exitButton->addTouchEventListener(
			[&](Ref* sender, Widget::TouchEventType type) {

				if (type == Widget::TouchEventType::ENDED) {
					Director::getInstance()->end();
				}
			}
		);
		this->addChild(m_bg, 2);
		this->addChild(m_exitButton, 2);
		this->addChild(m_resumeButton, 2);
		m_bg->setVisible(false);
		m_resumeButton->setVisible(false);
		m_exitButton->setVisible(false);

        // ------- Lemmings count.
		// ---- Remaining Lemmings
		m_remainingLemmingsLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 36);
        m_remainingLemmingsLabel->setPosition(Vec2(visibleSize.width - 20, visibleSize.height - 620));
        m_remainingLemmingsLabel->setColor(Color3B(0, 255, 255));
		this->addChild(m_remainingLemmingsLabel, 1);

        // ---- Win Lemmings
        m_winLemmingsLabel = Label::createWithTTF(std::to_string(m_winLemmings), "fonts/Marker Felt.ttf", 36);
        m_winLemmingsLabel->setPosition(Vec2(visibleSize.width - 60, visibleSize.height - 620));
        m_winLemmingsLabel->setColor(Color3B(0, 255, 255));
        this->addChild(m_winLemmingsLabel, 1);

        // ---- Lemmings that have been saved
        m_savedLemmingsLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 36);
        m_savedLemmingsLabel->setPosition(Vec2(visibleSize.width - 100, visibleSize.height - 620));
        m_savedLemmingsLabel->setColor(Color3B(0, 255, 255));
        this->addChild(m_savedLemmingsLabel, 1);

		// Task buttons.
		for (int i = 0; i < NUM_BUTTONS - 1; ++i) {

			m_remainingTasks[i] = 5;

			m_tasksButtons[i] = Button::create(actionButtonTextures[i]);
			m_tasksButtons[i]->setScale(width / m_tasksButtons[i]->getContentSize().width);
			m_tasksButtons[i]->setPosition(Vec2((i + 0.5F) * width, 0.5F * width));
			m_tasksButtons[i]->setColor(Color3B(255, 255, 255));
			this->addChild(m_tasksButtons[i]);

			m_remainingTasksLabels[i] = Label::createWithTTF("5", "fonts/Marker Felt.ttf", 36);
			m_remainingTasksLabels[i]->setPosition(Vec2((i + 0.5F) * width, width - 24));
			m_remainingTasksLabels[i]->setTextColor(Color4B(0, 0, 0, 255));
			this->addChild(m_remainingTasksLabels[i]);
		}

		// Assign callbacks.
		m_tasksButtons[0]->addTouchEventListener(CC_CALLBACK_2(GameScene::selectBasherTask, this));
		m_tasksButtons[1]->addTouchEventListener(CC_CALLBACK_2(GameScene::selectBlockerTask, this));

		// Speed up button.
		Button* btn = Button::create("CloseNormal.png");//actionButtonTextures[i]);
		btn->setScale(width / btn->getContentSize().width);
		btn->setPosition(Vec2((5 + 0.5F) * width, 0.5F * width));
		btn->setColor(Color3B(255, 255, 255));
		btn->addTouchEventListener(
			[&](Ref* sender, Widget::TouchEventType type) {

				if (type == Widget::TouchEventType::ENDED) {
					speedUp++;
					if (speedUp == 4) {
						speedUp = 0;
					}
					Director::getInstance()->getScheduler()->setTimeScale((float) (1 << speedUp));
				}
			}
		);
		this->addChild(btn);
	}

	auto eventListener = EventListenerTouchOneByOne::create();
	eventListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, m_tileMap);

	this->scheduleUpdate();

	return true;
}


void GameScene::update(float d)
{

	if (PAUSED) {
		// Set Buttons and Background Menu visible.
		Director::getInstance()->stopAnimation();
		m_bg->setVisible(true);
		m_exitButton->setVisible(true);
		m_resumeButton->setVisible(true);
		return;
	}

	Scene::update(d);

	int speedUpFactor = (1 << speedUp);

	// Spawn logic.
	if (m_spawnedLemmings != m_maxLemmings) {

		m_spawnTimer += d;

		if (m_spawnTimer >= 2.0F) {

			m_spawnTimer -= 2.0F;
			m_spawnedLemmings++;

			Lemming* l = Lemming::create();
			log("Lemming created : %c", std::to_string(m_lemmings.size()));
			//l->setScale(4);
			l->setPosition(Vec2(5 * 16, 23 * 16 + 1));
			l->setState(Lemming::STATE_WALK);
			m_lemmings.push_back(l);
			m_tileMap->addChild(l);

			m_remainingLemmingsLabel->setString(std::to_string(m_lemmings.size()));
		}
	}

	// Get AABBs around the lemming.
	std::vector<lemmings::AABB> aabbs;
	TMXLayer* layer = m_tileMap->getLayer("Calque de Tuiles 1");

	Size mapSize = m_tileMap->getMapSize();
	Size tileSize = layer->getMapTileSize();

	const int RADIUS = 1;

	for (int i = 0; i < speedUpFactor; ++i) {

		auto it = m_lemmings.begin();
		while (it != m_lemmings.end()) {

			Lemming* l = *it;

			if (l->isDead()) {
				it = m_lemmings.erase(it);
				m_remainingLemmingsLabel->setString(std::to_string(m_lemmings.size()));
				continue;
			}

			l->update(d);

			int xPos = (l->getPositionX() / tileSize.width);
			int yPos = mapSize.height - (l->getPositionY() / tileSize.height);

			for (int y = std::max(0, yPos - RADIUS); y <= std::min((int)mapSize.height - 1, yPos + RADIUS); ++y) {
				for (int x = std::max(0, xPos - RADIUS); x <= std::min((int)mapSize.width - 1, xPos + RADIUS); ++x) {

					int pixelX = (x * tileSize.width);
					int pixelY = (mapSize.height - y - 1) * tileSize.height;

					uint32_t tileID = layer->getTileGIDAt(Vec2(x, y));
					if (tileID != 0) {

						lemmings::AABB aabb(pixelX, pixelY, pixelX + tileSize.width, pixelY + tileSize.height);
						aabbs.push_back(aabb);
					}
				}
			}

			float dx = l->getDesiredDisplacement().x;
			float dy = l->getDesiredDisplacement().y;

			int direction = (dx > 0) ? 1 : -1;
			int offset = direction * 4; // boxSize

			bool blockUnder = isTileCollidable(l->getPositionX() - offset, l->getPositionY() - 1) || isTileCollidable(l->getPositionX() + offset, l->getPositionY() - 1);

			if (l->isFalling()) {
				// Check if ground.
				if (blockUnder) {
					l->setFalling(false);
					if (abs(l->getPositionY() - l->getFallHeight()) > 5.0F * 16.0F) {
						l->setState(Lemming::STATE_SPLASH);
					}
					else {
						l->setPositionY(((int)(l->getPositionY() / 16)) * 16 + 1);
					}
				}
			}
			else {
				if (!blockUnder) {
					l->setFalling(true);
					l->setFallHeight(l->getPositionY());
				}
				else {
					// Horizontal collision.
					if (isTileCollidable(l->getPositionX() + offset, l->getPositionY())) {

						switch (l->getState())
						{
						case Lemming::STATE_WALK:
							if (isTileCollidable(l->getPositionX() + offset, l->getPositionY() + 16)) {
								l->collideWall();
							}
							else {
								l->setPositionY(l->getPositionY() + 16);
							}
							break;

						case Lemming::STATE_BASHER:
							bool success = this->destroyTile(xPos + direction, yPos);
							if (!success) {
								l->collideWall();
							}
							break;
						}
					}
				}
			}

			l->move(dx, dy);

			it++;
		}
	}
}


void GameScene::changeToGameScene(Ref* pSender)
{
	AppDelegate::openScene<GameScene>();
	bool PAUSED = false;
}

bool GameScene::onTouchBegan(Touch* touch, Event* unused_event)
{
	Vec2 coords = touch->getLocationInView();
	coords.y = 768 - coords.y - (1024 / 6.0F);

	float minDist = 100.0F;
	Lemming* minl = 0;
	for (Lemming* l : m_lemmings) {

		Vec2 d = l->getPosition() - coords;
		float dist = d.length();

		if (dist < minDist) {
			minl = l;
			minDist = dist;
		}
	}

	if (minl && selectedState != Lemming::STATE_NONE) {

		int buttonID = 0;
		switch (selectedState) {
		case Lemming::STATE_BASHER: buttonID = 0; break;
		case Lemming::STATE_BLOCKER: buttonID = 1; break;
		}

		// Decrement remaining task and update display.
		m_remainingTasks[buttonID]--;
		m_remainingTasksLabels[buttonID]->setString(std::to_string(m_remainingTasks[buttonID]));

		// Update lemming state.
		minl->setState(selectedState);

		// If exhausted, deselect state automatically.
		if (m_remainingTasks[buttonID] == 0) {
			selectedState = Lemming::STATE_NONE;
		}
	}

	return true;
}

bool GameScene::isTileCollidable(int tileX, int tileY) const
{
	Size mapSize = m_tileMap->getMapSize();
	if (tileX < 0 || tileX >= mapSize.width || tileY < 0 || tileY >= mapSize.height)
		return true;

	return m_tileMapLayer->getTileGIDAt(Vec2(tileX, tileY)) != 0;
}

bool GameScene::isTileCollidable(float worldX, float worldY) const
{
	int xPos = (worldX / 16);
	int yPos = m_tileMap->getMapSize().height - (worldY / 16);

	return this->isTileCollidable(xPos, yPos);
}

bool GameScene::destroyTile(int tileX, int tileY)
{
	Size mapSize = m_tileMap->getMapSize();
	if (tileX < 0 || tileX >= mapSize.width || tileY < 0 || tileY >= mapSize.height)
		return false;

	m_tileMapLayer->setTileGID(0, Vec2(tileX, tileY));
	return true;
}

void GameScene::selectBasherTask(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (m_remainingTasks[0] > 0) {
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
			selectedState = (selectedState != Lemming::STATE_BASHER) ? Lemming::STATE_BASHER : Lemming::STATE_NONE;
		}
	}
}

void GameScene::selectBlockerTask(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (m_remainingTasks[1] > 0) {
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
			selectedState = (selectedState != Lemming::STATE_BLOCKER) ? Lemming::STATE_BLOCKER : Lemming::STATE_NONE;
		}
	}
}
