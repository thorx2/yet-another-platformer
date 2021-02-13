//
// Created by gaudh on 2/5/2021.
//

#ifndef PROJ_ANDROID_GAMESCENE_H
#define PROJ_ANDROID_GAMESCENE_H

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include <UIComponents/OnScreenController.h>
#include <cocos/base/CCValue.h>
#include <GenericClasses/BaseActor.h>

namespace PlatformerGame {
    class GameScene : public cocos2d::Scene, b2ContactListener {
    public:
        static cocos2d::Scene *createScene();

        virtual bool init();

        CREATE_FUNC(GameScene);

        virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;

    private:

        OnScreenController* m_onScreenController;

        cocos2d::CustomCommand _customCommand;
        cocos2d::Mat4 _modelViewMV;

        void onDraw();

        int m_objectCount = 0;

        cocos2d::TMXTiledMap *m_tileMap;

        b2World* m_world;

        double currentTime = 0;
        double lastTickTime = 0;
        double accumulator = 0;

        void setViewPointCenter(cocos2d::CCPoint position);

        void loadGameLevel(std::string level);

        void createRectangularFixture(cocos2d::TMXLayer* layer, int x, int y, float width, float height);

        void createFixtures(cocos2d::TMXLayer* layer);

        void prepareLayers();

        void createPhysicalWorld();

        void update(float delta);

        double getCurrentTimeInSeconds();

        void addObjects();

        BaseActor* addObject(std::string className, cocos2d::ValueMap& properties);
    };
}

#endif //PROJ_ANDROID_GAMESCENE_H
