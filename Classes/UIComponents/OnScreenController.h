//
// Created by gaudh on 2/5/2021.
//

#ifndef PROJ_ANDROID_ONSCREENCONTROLLER_H
#define PROJ_ANDROID_ONSCREENCONTROLLER_H


#include "cocos2d.h"
#include <vector>

namespace PlatformerGame {
    class OnScreenController : public cocos2d::Layer {
    public:
        static cocos2d::Scene* createScene();
        virtual bool init();
        void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
        void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
        void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
        CREATE_FUNC(OnScreenController);

    private:
        cocos2d::Sprite* leftButton;
        cocos2d::Sprite* rightButton;
        cocos2d::Sprite* attackButton;
        cocos2d::Sprite* jumpButton;
        cocos2d::Sprite* closeButton;
    };
}


#endif //PROJ_ANDROID_ONSCREENCONTROLLER_H
