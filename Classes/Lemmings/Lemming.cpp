#include "Lemming.h"

#include "Lemmings/Animation/SpriteAnimations.h"


Lemming::Lemming()
	: m_state(STATE_WALK)
{

}

void Lemming::update(float deltaTime)
{
	Sprite::update(deltaTime);

	switch (m_state)
	{
	case STATE_WALK:
	default:
		break;

	case STATE_BLOCKER:
		break;

	case STATE_BOMBER:
		break;

	case STATE_DIGGER:
		break;

	case STATE_EXIT:
		
		break;

	case STATE_FALLING:

	case STATE_JUMP:
		break;

	case STATE_UMBRELLA_DEPLOY:
		break;

	case STATE_UMBRELLA_FLOAT:
		break;
	}
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
