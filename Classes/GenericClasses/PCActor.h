//
// Created by gaudh on 2/13/2021.
//

#ifndef PROJ_ANDROID_PCACTOR_H
#define PROJ_ANDROID_PCACTOR_H

#include <string>
#include <cocos/math/Vec2.h>
#include <UIComponents/OnScreenController.h>
#include "BaseActor.h"

namespace PlatformerGame {
    class PCActor : public BaseActor {
    private:
        PCActor(std::string enemyName, b2World* world, cocos2d::Vec2 pos);
        OnScreenController *m_onScreenController;
    public:
        static PCActor* CreatePOActor(b2World* world, cocos2d::Vec2 pos);
    };
}

#endif //PROJ_ANDROID_PCACTOR_H
