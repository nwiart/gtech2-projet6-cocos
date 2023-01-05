
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class LosingScene : public cocos2d::Scene
{
    public:

        static LosingScene* createScene() { return LosingScene::create(); }

        LosingScene();
        ~LosingScene();

        virtual bool init() override;
        
        void changeToTitleScene(Ref* pSender);
        void exitScene(Ref* pSender);
        
        CREATE_FUNC(LosingScene);

    private:

};