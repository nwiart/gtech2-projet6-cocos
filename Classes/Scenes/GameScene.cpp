#include "GameScene.h"
#include "AppDelegate.h"

#include "Lemmings/Lemming.h"

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

	for (int i = 0; i < 10; ++i) {
		Lemming* l = Lemming::create();
		//l->setScale(4);
		l->setPosition(Vec2((20 +i) * 16, 5 * 16 + 1));
		l->setState(i == 0 ? Lemming::STATE_BLOCKER : Lemming::STATE_WALK);
		m_lemmings.push_back(l);
		m_tileMap->addChild(l);
	}


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

		// Task buttons.
		for (int i = 0; i < NUM_BUTTONS - 1; ++i) {

			m_remainingTasksButtons[i] = Button::create(actionButtonTextures[i]);
			m_remainingTasksButtons[i]->setScale(width / m_remainingTasksButtons[i]->getContentSize().width);
			m_remainingTasksButtons[i]->setPosition(Vec2((i + 0.5F) * width, 0.5F * width));
			m_remainingTasksButtons[i]->setColor(Color3B(255, 255, 255));
			this->addChild(m_remainingTasksButtons[i]);

			m_remainingTasksLabels[i] = Label::createWithTTF("05", "fonts/Marker Felt.ttf", 36);
			m_remainingTasksLabels[i]->setPosition(Vec2((i + 0.5F) * width, width - 24));
			m_remainingTasksLabels[i]->setTextColor(Color4B(0, 0, 0, 255));
			this->addChild(m_remainingTasksLabels[i]);
		}

		// Assign callbacks.
		m_remainingTasksButtons[0]->addTouchEventListener(CC_CALLBACK_2(GameScene::selectBasherTask, this));
		m_remainingTasksButtons[1]->addTouchEventListener(CC_CALLBACK_2(GameScene::selectBlockerTask, this));

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
	Scene::update(d);

	// Get AABBs around the lemming.
	std::vector<lemmings::AABB> aabbs;
	TMXLayer* layer = m_tileMap->getLayer("Calque de Tuiles 1");

	Size mapSize  = m_tileMap->getMapSize();
	Size tileSize = layer->getMapTileSize();

	const int RADIUS = 1;

	for (int i = 0; i < (1 << speedUp); ++i) {
		for (Lemming* l : m_lemmings) {

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

			/*bool colX = false;

			lemmings::AABB lemmingBox;
			l->getAABB(lemmingBox);
			for (const lemmings::AABB& aabb : aabbs) {

				float newDx = dx;
				if (dx != 0.0F) newDx = lemmingBox.collideX(aabb, dx);
				if (newDx != dx) {
					dx = newDx;
					colX = true;
				}

				if (dy != 0.0F) dy = lemmingBox.collideY(aabb, dy);
			}

			if (colX) {
				l->collideWall();
			}*/

			int direction = (dx > 0) ? 1 : -1;
			int offset = direction * 4; // boxSize

			bool blockUnder = isTileCollidable(l->getPositionX() - offset, l->getPositionY() - 1) || isTileCollidable(l->getPositionX() + offset, l->getPositionY() - 1);

			if (l->isFalling()) {
				// Check if ground.
				if (blockUnder) {
					if (l->getFallTimer() > 2.0F) {
						l->setFalling(false);
						l->setState(Lemming::STATE_SPLASH);
					}
					else {
						l->setFalling(false);
						l->setPositionY(((int)(l->getPositionY() / 16)) * 16 + 1);
					}
				}
			}
			else {
				if (!blockUnder) {
					l->setFalling(true);
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
		}
	}
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
		minl->setState(selectedState);
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
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) selectedState = (selectedState != Lemming::STATE_BASHER) ? Lemming::STATE_BASHER : Lemming::STATE_NONE;
}

void GameScene::selectBlockerTask(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) selectedState = (selectedState != Lemming::STATE_BLOCKER) ? Lemming::STATE_BLOCKER : Lemming::STATE_NONE;
}
