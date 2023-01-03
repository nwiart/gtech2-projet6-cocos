#include "Lemming.h"

#include "Lemmings/Animation/SpriteAnimations.h"


Lemming::Lemming()
	: m_state(STATE_WALK), m_direction(DIRECTION_RIGHT)
{
	
}

void Lemming::update(float deltaTime)
{
	Sprite::update(deltaTime);

	switch (m_state)
	{
	case STATE_WALK:
	default:
		this->setDX((m_direction == DIRECTION_RIGHT) ? 1.0F : -1.0F);
		break;

	case STATE_BLOCKER:
		break;

	case STATE_BOMBER:
		break;

	case STATE_DIGGER:
		this->setDX((m_direction == DIRECTION_RIGHT) ? 1.0F : -1.0F);
		break;

	case STATE_EXIT:
		break;

	case STATE_FALLING:
		this->setDY(-3.0F);
		break;

	case STATE_UMBRELLA_DEPLOY:
		break;

	case STATE_UMBRELLA_FLOAT:
		break;
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
	m_state = t;

	// Play new animation.
	this->getActionManager()->removeAllActions();
	//SpriteAnimations::playOn(this, m_state);
}

Lemming* Lemming::create()
{
	Lemming* l = new Lemming();
	l->initWithFile("lemming_sheet.png");
	l->getTexture()->setAliasTexParameters();
	return l;
}
