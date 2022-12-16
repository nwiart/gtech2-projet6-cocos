#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GameScene : public cocos2d::Scene
{
public:
<<<<<<< HEAD

    static GameScene* createScene() { return GameScene::create(); }


    GameScene(/* args */);
    ~GameScene();

    virtual bool init() override;

=======
    GameScene(/* args */);
    ~GameScene();

>>>>>>> 1bf4bb53c33835cb5f652e345494a4ac4001ee47
    void menuCloseCallback(Ref *pSender);
    void exitScene(Ref *pSender);

    CREATE_FUNC(GameScene);

private:
<<<<<<< HEAD


    cocos2d::Sprite* m_cursorSprite;
=======
>>>>>>> 1bf4bb53c33835cb5f652e345494a4ac4001ee47
};