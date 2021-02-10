//
// Created by gaudh on 2/5/2021.
//

#ifndef PROJ_ANDROID_ONSCREENCONTROLLER_H
#define PROJ_ANDROID_ONSCREENCONTROLLER_H


#include "cocos2d.h"
#include <ui/UIButton.h>
#include <vector>

namespace PlatformerGame {
    class OnScreenController : public cocos2d::Layer {
    public:
        static cocos2d::Scene* createScene();
        virtual bool init();
        CREATE_FUNC(OnScreenController);

    private:
        cocos2d::ui::Button* leftButton;
        cocos2d::ui::Button* rightButton;
        cocos2d::ui::Button* attackButton;
        cocos2d::ui::Button* jumpButton;
        cocos2d::ui::Button* closeButton;
    };
}


#endif //PROJ_ANDROID_ONSCREENCONTROLLER_H
