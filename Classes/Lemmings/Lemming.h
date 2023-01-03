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

	void move(float dx, float dy);

	void collideWall();

	void toggleDirection();

	bool isFalling() const { return m_state == STATE_FALLING; }

	void getAABB(lemmings::AABB& out) const;

	const cocos2d::Vec2& getDesiredDisplacement() const { return m_displacement; }

	void setDX(float dx) { m_displacement.x = dx; }
	void setDY(float dy) { m_displacement.y = dy; }
	void setState(State t);

	static Lemming* create();



private:

	cocos2d::Vec2 m_displacement;

	State m_state;
	Direction m_direction;
};
