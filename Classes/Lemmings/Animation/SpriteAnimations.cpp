#include "SpriteAnimations.h"

#include "Lemmings/Lemming.h"

USING_NS_CC;


SpriteAnimations::SpriteAnimations()
{

}

void SpriteAnimations::init()
{
	Vector<SpriteFrame*> frames;

	// Walk.
	frames.reserve(8);
	{
		for (int i = 0; i < 8; ++i) {
			frames.pushBack(SpriteFrame::create("lemming_sheet.png", Rect(i * 20, 0, 20, 20)));
		}
		
		Animation* a = Animation::createWithSpriteFrames(frames, 0.1F);
		anim_walk = RepeatForever::create(Animate::create(a));
		anim_walk->retain();
	}

	// Basher.
	frames.clear();
	frames.reserve(32);
	{
		for (int j = 0; j < 2; ++j) {
			for (int i = 0; i < 16; ++i) {
				frames.pushBack(SpriteFrame::create("lemming_sheet.png", Rect((i) * 20, (j + 6) * 20, 20, 20)));
			}
		}

		Animation* a = Animation::createWithSpriteFrames(frames, 0.025F);
		anim_basher = RepeatForever::create(Animate::create(a));
		anim_basher->retain();
	}

	// Blocker.
	frames.clear();
	frames.reserve(16);
	{
		for (int i = 0; i < 16; ++i) {
			frames.pushBack(SpriteFrame::create("lemming_sheet.png", Rect((i) * 20, (3) * 20, 20, 20)));
		}
	
		Animation* a = Animation::createWithSpriteFrames(frames, 0.05F);
		anim_blocker = RepeatForever::create(Animate::create(a));
		anim_blocker->retain();
	}

	// Bomber.
	frames.clear();
	frames.reserve(16);
	{
		for (int j = 0; j < 2; ++j) {
			for (int i = 0; i < 16; ++i) {
				frames.pushBack(SpriteFrame::create("lemming_sheet.png", Rect((i) * 20, (j + 10) * 20, 20, 20)));
			}
		}

		Animation* a = Animation::createWithSpriteFrames(frames, 0.05F);
		anim_bomber = Animate::create(a);
		anim_bomber->retain();
	}

	// Digger.
	frames.clear();
	frames.reserve(8);
	{
		for (int i = 0; i < 8; ++i) {
			frames.pushBack(SpriteFrame::create("lemming_sheet.png", Rect((i) * 20, (8) * 20, 20, 20)));
		}

		Animation* a = Animation::createWithSpriteFrames(frames, 0.1F);
		anim_digger = RepeatForever::create(Animate::create(a));
		anim_digger->retain();
	}

	// Drowning.
	frames.clear();
	frames.reserve(16);
	{
		for (int i = 0; i < 16; ++i) {
			frames.pushBack(SpriteFrame::create("lemming_sheet.png", Rect((i) * 20, (12) * 20, 20, 20)));
		}

		Animation* a = Animation::createWithSpriteFrames(frames, 0.05F);
		anim_drowning = RepeatForever::create(Animate::create(a));
		anim_drowning->retain();
	}

	// Exit.
	frames.clear();
	frames.reserve(8);
	{
		for (int i = 0; i < 8; ++i) {
			frames.pushBack(SpriteFrame::create("lemming_sheet.png", Rect((i + 1) * 20, (1) * 20, 20, 20)));
		}

		Animation* a = Animation::createWithSpriteFrames(frames, 0.1F);
		anim_exit = Animate::create(a);
		anim_exit->retain();
	}

	// Falling.
	frames.clear();
	frames.reserve(4);
	{
		for (int i = 0; i < 4; ++i) {
			frames.pushBack(SpriteFrame::create("lemming_sheet.png", Rect((i) * 20, (2) * 20, 20, 20)));
		}

		Animation* a = Animation::createWithSpriteFrames(frames, 0.2F);
		anim_falling = RepeatForever::create(Animate::create(a));
		anim_falling->retain();
	}

	// Splash.
	frames.clear();
	frames.reserve(16);
	{
		for (int i = 0; i < 16; ++i) {
			frames.pushBack(SpriteFrame::create("lemming_sheet.png", Rect((i) * 20, (11) * 20, 20, 20)));
		}

		Animation* a = Animation::createWithSpriteFrames(frames, 0.2F);
		anim_splash = Animate::create(a);
		anim_splash->retain();
	}

	// Umbrella deploy.
	frames.clear();
	frames.reserve(8);
	{
		for (int i = 0; i < 4; ++i) {
			frames.pushBack(SpriteFrame::create("lemming_sheet.png", Rect((i + 4) * 20, (2) * 20, 20, 20)));
		}

		Animation* a = Animation::createWithSpriteFrames(frames, 0.05F);
		anim_umbrelladeploy = Animate::create(a);
	}

	// Umbrella float.
	frames.clear();
	frames.reserve(8);
	{
		for (int i = 0; i < 4; ++i) {
			frames.pushBack(SpriteFrame::create("lemming_sheet.png", Rect((i + 8) * 20, (2) * 20, 20, 20)));
		}
		for (int i = 0; i > -4; --i) {
			frames.pushBack(SpriteFrame::create("lemming_sheet.png", Rect((i + 11) * 20, (2) * 20, 20, 20)));
		}

		Animation* a = Animation::createWithSpriteFrames(frames, 0.1F);
		anim_umbrellafloat = RepeatForever::create(Animate::create(a));
	}
}

void SpriteAnimations::playOn(Lemming* l, int state)
{
	Vector<SpriteFrame*> frames;
	Action* a = 0;

	if (l->isFalling()) {
		a = anim_falling;
	}
	else {
		switch (state)
		{
		case Lemming::STATE_NONE: a = 0; break;
		case Lemming::STATE_WALK: a = anim_walk; break;
		case Lemming::STATE_BASHER: a = anim_basher; break;
		case Lemming::STATE_BLOCKER: a = anim_blocker; break;
		case Lemming::STATE_BOMBER: a = anim_bomber; break;
		case Lemming::STATE_SPLASH: a = anim_splash; break;

			// Digger.
			/*frames.clear();
			frames.reserve(8);
			{
				for (int i = 0; i < 8; ++i) {
					frames.pushBack(SpriteFrame::create("lemming_sheet.png", Rect((i) * 20, (8) * 20, 20, 20)));
				}

				Animation* a = Animation::createWithSpriteFrames(frames, 0.1F);
				anim_digger = RepeatForever::create(Animate::create(a));
				anim_digger->retain();
			}

			// Drowning.
			frames.clear();
			frames.reserve(16);
			{
				for (int i = 0; i < 16; ++i) {
					frames.pushBack(SpriteFrame::create("lemming_sheet.png", Rect((i) * 20, (12) * 20, 20, 20)));
				}

				Animation* a = Animation::createWithSpriteFrames(frames, 0.05F);
				anim_drowning = RepeatForever::create(Animate::create(a));
				anim_drowning->retain();
			}

			// Exit.
			frames.clear();
			frames.reserve(8);
			{
				for (int i = 0; i < 8; ++i) {
					frames.pushBack(SpriteFrame::create("lemming_sheet.png", Rect((i + 1) * 20, (1) * 20, 20, 20)));
				}

				Animation* a = Animation::createWithSpriteFrames(frames, 0.1F);
				anim_exit = Animate::create(a);
				anim_exit->retain();
			}*/

			// Falling.
		case Lemming::STATE_UMBRELLA_DEPLOY: a = anim_umbrelladeploy; break;
		case Lemming::STATE_UMBRELLA_FLOAT: a = anim_umbrellafloat; break;
		}
	}

	if (a) {
		l->runAction(a->clone());
	}
}
