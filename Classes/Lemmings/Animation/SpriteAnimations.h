#pragma once

#include <cocos2d.h>

class Lemming;


class SpriteAnimations
{
public:

	SpriteAnimations();

	void init();

	/// <summary>
	/// Play an animation on a lemming, based on a given state.
	/// </summary>
	/// <param name="l">The target lemming</param>
	/// <param name="state">The state (member of Lemming::State)</param>
	void playOn(Lemming* l, int state);


public:

	cocos2d::Action* anim_walk;
	cocos2d::Action* anim_basher;
	cocos2d::Action* anim_blocker;
	cocos2d::Action* anim_bomber;
	cocos2d::Action* anim_digger;
	cocos2d::Action* anim_drowning;
	cocos2d::Action* anim_exit;
	cocos2d::Action* anim_falling;
	cocos2d::Action* anim_splash;
	cocos2d::Action* anim_umbrelladeploy;
	cocos2d::Action* anim_umbrellafloat;
};
