//
// Created by gaudh on 2/5/2021.
//

#ifndef PROJ_ANDROID_MAINSCENE_H
#define PROJ_ANDROID_MAINSCENE_H

#include "cocos2d.h"

namespace PlatformerGame {
    class MainScene : public cocos2d::Scene {
    public:
        static cocos2d::Scene *createScene();

        virtual bool init();

        CREATE_FUNC(MainScene);
    };
}


#endif //PROJ_ANDROID_MAINSCENE_H
