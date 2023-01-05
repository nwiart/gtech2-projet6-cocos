
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GameScene;
class WinningScene : public cocos2d::Scene
{
    public:

        static WinningScene* createScene() { return WinningScene::create(); }

        WinningScene();
        ~WinningScene();

        virtual bool init() override;
        
        void changeToTitleScene(Ref* pSender);
        void exitScene(Ref* pSender);
        
        CREATE_FUNC(WinningScene);

    private:

};