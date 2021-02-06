//
// Created by gaudh on 2/5/2021.
//

#ifndef PROJ_ANDROID_GAMESCENE_H
#define PROJ_ANDROID_GAMESCENE_H

#include <cocos/deprecated/CCDeprecated.h>
#include "cocos2d.h"
namespace PlatformerGame {
    class GameScene : public cocos2d::Scene {
    public:
        static cocos2d::Scene *createScene();

        virtual bool init();

        CREATE_FUNC(GameScene);
    private:

        cocos2d::TMXTiledMap *tileMap;

        void setViewPointCenter(cocos2d::CCPoint position);
    };
}

#endif //PROJ_ANDROID_GAMESCENE_H
