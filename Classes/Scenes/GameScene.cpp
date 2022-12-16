#include "GameScene.h"

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

		Size screenSize = Director::getInstance()->getVisibleSize();
		int width = screenSize.width / NUM_BUTTONS;

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

			m_remainingTasksLabels[i] = Label::createWithTTF("05", "fonts/Marker Felt.ttf", 24);
			m_remainingTasksLabels[i]->setPosition(Vec2((i + 0.5F) * width, width));
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
					Director::getInstance()->setAnimationInterval(speedUp ? (1.0F / 120.0F) : (1.0F / 60.0F));
				}
			}
		);
		this->addChild(btn);
	}

	return true;
}
