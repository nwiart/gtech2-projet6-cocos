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
	speedUp = false;


	Size screenSize = Director::getInstance()->getVisibleSize();
	int width = screenSize.width / NUM_BUTTONS;

	m_tileMap = TMXTiledMap::create("maps/testmap.tmx");
	m_tileMap->setPosition(Vec2(0, width));
	m_tileMap->setScale(2);
	this->addChild(m_tileMap);

	Lemming* l = Lemming::create();
	l->setScale(4);
	l->setPosition(Vec2(0, 0));
	AppDelegate::getLemmingsAnimations().playOn(l, Lemming::STATE_WALK);
	this->addChild(l);


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
	Scene::update(d);

	std::vector<lemmings::AABB> aabbs;
	TMXLayer* l = m_tileMap->getLayer("Calque de Tuiles 1");

	Size size = l->getMapTileSize();

	int xPos=0, yPos=31, radius=3;
	for (int y = std::max(0, yPos - radius); y <= std::min((int) size.height, yPos + radius); ++y) {
		for (int x = std::max(0, xPos - radius); x <= xPos + radius; ++x) {
			
			uint32_t tileID = l->getTileGIDAt(Vec2(x, y));
			if (tileID != 0) {

				Vec2 pos = l->getPositionAt(Vec2(x, y));
				lemmings::AABB aabb(0, 0, 0,0 );
				aabbs.push_back(aabb);
			}
		}
	}

	__asm {
		int 3
	}
}
