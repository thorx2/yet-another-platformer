//
// Created by gaudh on 2/5/2021.
//

#ifndef PROJ_ANDROID_GAMESCENE_H
#define PROJ_ANDROID_GAMESCENE_H

#include "cocos2d.h"
#include <Box2D/Box2D.h>

namespace PlatformerGame {
    class GameScene : public cocos2d::Scene, b2ContactListener {
    public:
        static cocos2d::Scene *createScene();

        virtual bool init();

        CREATE_FUNC(GameScene);
    private:

        cocos2d::TMXTiledMap *tileMap;

        b2World* world;

        void setViewPointCenter(cocos2d::CCPoint position);

        void loadGameLevel(std::string level);

        void createRectangularFixture(cocos2d::TMXLayer* layer, int x, int y, float width, float height);

        void createFixtures(cocos2d::TMXLayer* layer);

        void prepareLayers();

        void createPhysicalWorld();
    };
}

#endif //PROJ_ANDROID_GAMESCENE_H
