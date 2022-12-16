#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class SettingsScene : public cocos2d::Scene
{
    public:
        SettingsScene(/* args */);
        ~SettingsScene();

        
        void menuCloseCallback(Ref* pSender);
        void exitScene(Ref* pSender);
        
        CREATE_FUNC(SettingsScene);

    private:


};