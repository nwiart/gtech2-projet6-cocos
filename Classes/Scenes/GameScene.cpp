#include "GameScene.h"
#include "AppDelegate.h"
#include "PauseScene.h"

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
	speedUp = false;

	//this->setColor(Color3B(40, 127, 255));

	Size screenSize = Director::getInstance()->getVisibleSize();
	int width = screenSize.width / NUM_BUTTONS;

	m_tileMap = TMXTiledMap::create("maps/testmap.tmx");
	m_tileMap->setPosition(Vec2(0, width));
	m_tileMapLayer = m_tileMap->getLayer("Calque de Tuiles 1");
	//m_tileMap->setScale(2);
	this->addChild(m_tileMap);

	Lemming* l = Lemming::create();
	//l->setScale(4);
	l->setPosition(Vec2(20 * 16, 5 * 16 + 1));
	AppDelegate::getLemmingsAnimations().playOn(l, Lemming::STATE_WALK);
	m_lemmings.push_back(l);
	m_tileMap->addChild(l);


	// Create cursor sprite.
	m_cursorSprite = Sprite::create("cursor.png");

	// Create buttons and remaining count.
	{
		const char* actionButtonTextures[NUM_BUTTONS] = {
			"",
			"",
			"",
			"",
			"",
			"",
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

		m_resumeButton = Button::create("resume.png");
		m_resumeButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		m_resumeButton->addTouchEventListener(
			[&](Ref* sender, Widget::TouchEventType type) {

				if (type == Widget::TouchEventType::ENDED) {
					m_bg->setVisible(false);
					m_resumeButton->setVisible(false);
					PAUSED = false;
					Director::getInstance()->startAnimation();
				}
			}
		);
		this->addChild(m_bg, 2);
		this->addChild(m_resumeButton, 2);
		m_bg->setVisible(false);
		m_resumeButton->setVisible(false);

		m_resumeButton->retain();
		m_bg->retain();



		// Task buttons.
		for (int i = 0; i < NUM_BUTTONS - 1; ++i) {

			Button* btn = Button::create("CloseNormal.png");//actionButtonTextures[i]);
			btn->setScale(width / btn->getContentSize().width);
			btn->setPosition(Vec2((i + 0.5F) * width, 0.5F * width));
			btn->setColor(Color3B(255, 255, 255));
			btn->addTouchEventListener(
				[&](Ref* sender, Widget::TouchEventType type) {

					m_remainingTasksLabels[i]->setString(std::to_string(55));
				}
			);
			this->addChild(btn);

			m_remainingTasksLabels[i] = Label::createWithTTF("05", "fonts/Marker Felt.ttf", 36);
			m_remainingTasksLabels[i]->setPosition(Vec2((i + 0.5F) * width, width - 36));
			m_remainingTasksLabels[i]->setColor(Color3B(255, 127, 0));
			m_remainingTasksLabels[i]->setTextColor(Color4B(255, 127, 0, 255));
			this->addChild(m_remainingTasksLabels[i]);
		}

		// Speed up button.
		Button* btn = Button::create("CloseNormal.png");//actionButtonTextures[i]);
		btn->setScale(width / btn->getContentSize().width);
		btn->setPosition(Vec2((5 + 0.5F) * width, 0.5F * width));
		btn->setColor(Color3B(255, 255, 255));
		btn->addTouchEventListener(
			[&](Ref* sender, Widget::TouchEventType type) {

				if (type == Widget::TouchEventType::ENDED) {
					speedUp = !speedUp;
					Director::getInstance()->getScheduler()->setTimeScale(speedUp ? 2 : 1);
				}
			}
		);
		this->addChild(btn);
	}

	this->scheduleUpdate();

	return true;
}


void GameScene::update(float d)
{

	if (PAUSED) {
		log("-------------------------- PAUSED ----------------------------------");
		// Change color of bakckground, abd make buttons visible

		Director::getInstance()->stopAnimation();
		m_bg->setVisible(true);
		m_resumeButton->setVisible(true);
		return;
	}

	Scene::update(d);

	// Get AABBs around the lemming.
	std::vector<lemmings::AABB> aabbs;
	TMXLayer* layer = m_tileMap->getLayer("Calque de Tuiles 1");

	Size mapSize = m_tileMap->getMapSize();
	Size tileSize = layer->getMapTileSize();

	const int RADIUS = 1;

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

		log("%d %d %d", xPos, yPos, aabbs.size());

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

		// Horizontal collision.
		int offset = (dx > 0) ? 5 : -5;
		if (isTileCollidable(l->getPositionX() + offset, l->getPositionY())) {
			if (isTileCollidable(l->getPositionX() + offset, l->getPositionY() + 16)) {
				l->collideWall();
			}
			else {
				l->setPositionY(l->getPositionY() + 16);
			}
		}

		l->move(dx, dy);
	}
}

void GameScene::changeToPauseScene(Ref* pSender)
{
	AppDelegate::openScene<PauseScene>();
}

void GameScene::changeToGameScene(Ref* pSender)
{
	AppDelegate::openScene<GameScene>();
	bool PAUSED = false;
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