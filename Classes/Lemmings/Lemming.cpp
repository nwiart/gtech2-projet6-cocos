#include "Lemming.h"

#include "Lemmings/Animation/SpriteAnimations.h"


Lemming::Lemming()
	: m_state(STATE_WALK), m_direction(DIRECTION_RIGHT)
{
	
}

void Lemming::update(float deltaTime)
{
	Sprite::update(deltaTime);

	this->setPositionX(this->getPositionX() + (m_direction == DIRECTION_RIGHT) ? 1.0F : -1.0F);

	switch (m_state)
	{
	case STATE_WALK:
	default:
		//this->setPositionX(this->getPositionX() + (m_direction == DIRECTION_RIGHT) ? 1.0F : -1.0F);
		break;

	case STATE_BLOCKER:
		break;

	case STATE_BOMBER:
		break;

	case STATE_DIGGER:
		this->setPositionX(this->getPositionX() + (m_direction == DIRECTION_RIGHT) ? 1.0F : -1.0F);
		break;

	case STATE_EXIT:
		break;

	case STATE_FALLING:
		this->setPositionY(this->getPositionY() - 3.0F);
		break;

	case STATE_UMBRELLA_DEPLOY:
		break;

	case STATE_UMBRELLA_FLOAT:
		break;
	}
}

void Lemming::getAABB(lemmings::AABB& out) const
{
	float hx = 10.0F * 0.5F;
	float y = 10.0F;

	out.x0 = -hx;
	out.y0 =  0;
	out.x1 =  hx;
	out.y1 =  y;
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
