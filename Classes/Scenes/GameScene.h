//
// Created by gaudh on 2/5/2021.
//

#ifndef PROJ_ANDROID_GAMESCENE_H
#define PROJ_ANDROID_GAMESCENE_H

#include "cocos2d.h"
namespace PlatformerGame {
    class GameScene : public cocos2d::Scene {
    public:
        static cocos2d::Scene *createScene();

        virtual bool init();

        CREATE_FUNC(GameScene);
    };
}

#endif //PROJ_ANDROID_GAMESCENE_H
