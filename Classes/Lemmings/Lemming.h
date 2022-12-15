#pragma once

#include <cocos2d.h>


class Lemming : public cocos2d::Sprite
{
public:

	enum State
	{
		STATE_WALK,    // Default.
		STATE_BLOCKER,
		STATE_BOMBER,
		STATE_DIGGER,
		STATE_DROWNING,
		STATE_EXIT,
		STATE_FALLING,
		STATE_JUMP,
		STATE_SPLASH,
		STATE_UMBRELLA_DEPLOY,
		STATE_UMBRELLA_FLOAT,
	};


public:

	Lemming();

	virtual void update(float deltaTime) override;

	bool isFalling() const { return m_state == STATE_FALLING; }

	void setState(State t);

	static Lemming* create();



private:

	State m_state;
};
