#include "Lemming.h"

#include "Lemmings/Animation/SpriteAnimations.h"
#include "AppDelegate.h"

#include <cocos2d.h>


Lemming::Lemming()
	: m_state(STATE_NONE), m_direction(DIRECTION_RIGHT), m_falling(false), m_fallHeight(0.0F), m_dead(false), m_explodeTimer(5.0F)
{
	
}

void Lemming::update(float deltaTime)
{
	Sprite::update(deltaTime);

	this->setDX(0.0F);
	this->setDY(0.0F);

	float speed = 0.4F;// *cocos2d::Director::getInstance()->getScheduler()->getTimeScale();

	if (m_falling) {
		if (m_state != STATE_UMBRELLA_DEPLOY)
			speed *= 2;
		this->setDY(-speed);
	}
	else {
		switch (m_state)
		{
		case STATE_WALK:
		case STATE_BASHER:
		default:
			this->setDX((m_direction == DIRECTION_RIGHT) ? speed : -speed);
			break;

		case STATE_BLOCKER:
			break;

		case STATE_BOMBER:
			this->setDX((m_direction == DIRECTION_RIGHT) ? speed : -speed);
			m_explodeTimer -= deltaTime;
			if (m_explodeTimer <= 0.0F) {
				this->setState(STATE_BOMBER_EXPLODE);
			}
			break;

		case STATE_DIGGER:
			break;

		case STATE_EXIT:
			break;

		case STATE_SPLASH:
			m_dead = true;
			if (this->getActionManager()->getNumberOfRunningActions() == 0) {
				this->removeFromParentAndCleanup(true);
			}
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
	case DIRECTION_LEFT: this->setDirection(DIRECTION_RIGHT); break;
	case DIRECTION_RIGHT: this->setDirection(DIRECTION_LEFT); break;
	}
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
	m_state = t;

	// Play new animation.
	this->getActionManager()->removeAllActionsFromTarget(this);
	AppDelegate::getLemmingsAnimations().playOn(this, m_state);
}

void Lemming::setDirection(Direction d)
{
	m_direction = d;
	this->setFlippedX(m_direction == DIRECTION_LEFT);
}

Lemming* Lemming::create()
{
	Lemming* l = new Lemming();
	l->initWithFile("lemming_sheet.png");
	l->getTexture()->setAliasTexParameters();
	return l;
}
