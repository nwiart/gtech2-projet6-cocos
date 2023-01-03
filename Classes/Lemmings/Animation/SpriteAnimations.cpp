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
	}

	// Umbrella deploy.
	frames.clear();
	frames.reserve(8);
	{
		for (int i = 0; i < 4; ++i) {
			frames.pushBack(SpriteFrame::create("lemming_sheet.png", Rect((i + 4) * 20, (2) * 20, 20, 20)));
		}

		Animation* a = Animation::createWithSpriteFrames(frames, 0.1F);
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
	Action* a = 0;

	switch (state) {
	case Lemming::STATE_WALK:            a = anim_walk;     break;
	case Lemming::STATE_BASHER:          a = anim_basher;     break;
	case Lemming::STATE_BLOCKER:         a = anim_blocker;  break;
	case Lemming::STATE_BOMBER:          a = anim_bomber;   break;
	case Lemming::STATE_DIGGER:          a = anim_digger;   break;
	case Lemming::STATE_DROWNING:        a = anim_drowning; break;
	case Lemming::STATE_EXIT:            a = anim_exit;     break;
	case Lemming::STATE_FALLING:         a = anim_falling;  break;
	case Lemming::STATE_STUNNED:         a = anim_stunned;  break;
	case Lemming::STATE_UMBRELLA_DEPLOY: a = anim_umbrelladeploy; break;
	case Lemming::STATE_UMBRELLA_FLOAT:  a = anim_umbrellafloat;  break;
	}

	l->runAction(a);
}
