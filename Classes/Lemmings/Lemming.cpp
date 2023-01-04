#include "Lemming.h"

#include "Lemmings/Animation/SpriteAnimations.h"
#include "AppDelegate.h"

#include <cocos2d.h>


Lemming::Lemming()
	: m_state(STATE_NONE), m_direction(DIRECTION_RIGHT), m_falling(false)
{
	
}

void Lemming::update(float deltaTime)
{
	Sprite::update(deltaTime);

	this->setDX(0.0F);
	this->setDY(0.0F);

	float speed = 0.4F;// *cocos2d::Director::getInstance()->getScheduler()->getTimeScale();

	if (m_falling) {
		this->setDY(-speed);
		m_fallTimer += deltaTime;
	}
	else {
		m_fallTimer = 0;
		switch (m_state)
		{
		case STATE_WALK:
		default:
			this->setDX((m_direction == DIRECTION_RIGHT) ? speed : -speed);
			break;

		case STATE_BASHER:
			this->setDX((m_direction == DIRECTION_RIGHT) ? speed : -speed);
			break;

		case STATE_BLOCKER:
			break;

		case STATE_BOMBER:
			break;

		case STATE_DIGGER:
			this->setDX((m_direction == DIRECTION_RIGHT) ? speed : -speed);
			break;

		case STATE_EXIT:
			break;

		case STATE_SPLASH:
			this->removeFromParentAndCleanup(true);
			break;

		case STATE_UMBRELLA_DEPLOY:
			break;

		case STATE_UMBRELLA_FLOAT:
			break;
		}
	}
}

void Lemming::move(float dx, float dy)
{
	this->setPosition(this->getPosition() + cocos2d::Vec2(dx, dy));
}

void Lemming::collideWall()
{
	this->toggleDirection();
}

void Lemming::toggleDirection()
{
	switch (m_direction)
	{
	case DIRECTION_LEFT: m_direction = DIRECTION_RIGHT; break;
	case DIRECTION_RIGHT: m_direction = DIRECTION_LEFT; break;
	}

	this->setFlippedX(m_direction == DIRECTION_LEFT);
}

void Lemming::getAABB(lemmings::AABB& out) const
{
	float hx = 10.0F * 0.5F;
	float y = 10.0F;

	out.x0 = -hx + this->getPositionX();
	out.y0 =  this->getPositionY();
	out.x1 =  hx + this->getPositionX();
	out.y1 =  y + this->getPositionY();
}

void Lemming::setState(State t)
{
	if (m_state != t) {
		m_state = t;

		// Play new animation.
		this->getActionManager()->removeAllActionsFromTarget(this);
		AppDelegate::getLemmingsAnimations().playOn(this, m_state);
	}
}

Lemming* Lemming::create()
{
	Lemming* l = new Lemming();
	l->initWithFile("lemming_sheet.png");
	l->getTexture()->setAliasTexParameters();
	return l;
}
