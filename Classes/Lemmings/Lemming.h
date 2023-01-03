#pragma once

#include <cocos2d.h>

#include "AABB.h"


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
		STATE_SPLASH,
		STATE_STUNNED,
		STATE_BASHER,
		STATE_UMBRELLA_DEPLOY,
		STATE_UMBRELLA_FLOAT,
	};

	enum Direction
	{
		DIRECTION_LEFT,
		DIRECTION_RIGHT
	};


public:

	Lemming();

	virtual void update(float deltaTime) override;

	bool isFalling() const { return m_state == STATE_FALLING; }

	void getAABB(lemmings::AABB& out) const;

	void setState(State t);

	static Lemming* create();



private:

	State m_state;
	Direction m_direction;
};
