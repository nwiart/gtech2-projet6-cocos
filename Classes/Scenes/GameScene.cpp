#include "GameScene.h"

USING_NS_CC;
using namespace cocos2d::ui;


bool GameScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	// Create cursor sprite.
	m_cursorSprite = Sprite::create("cursor.png");

	// Create buttons and remaining count.
	const int NUM_BUTTONS = 6;
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
		for (int i = 0; i < NUM_BUTTONS; ++i) {

			Button* btn = Button::create(actionButtonTextures[i]);
			btn->setContentSize(Size(width, width));
			btn->setPosition(Vec2(i * width, screenSize.height - width));
			btn->addTouchEventListener(
				[&](Ref* sender, Widget::TouchEventType type) {

				}
			);
			this->addChild(btn);

			Label* label = Label::create();
			label->setPosition(Vec2(i * width, screenSize.height - width));
			label->setColor(Color3B(255, 127, 0));
			label->setString("05");
		}
	}

	return true;
}
