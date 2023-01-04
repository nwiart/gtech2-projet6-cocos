#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class SettingsScene : public cocos2d::Scene
{
    public:

        static SettingsScene* createScene() { return SettingsScene::create(); }

        SettingsScene(/* args */);
        ~SettingsScene();

        virtual bool init() override;
        
        void changeToTitleScene(Ref* pSender);
        void exitScene(Ref* pSender);
        
        CREATE_FUNC(SettingsScene);

    private:


};