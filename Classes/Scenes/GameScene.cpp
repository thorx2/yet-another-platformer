//
// Created by gaudh on 2/5/2021.
//

//#include <external/Box2D/include/Box2D/Dynamics/b2Body.h>
//#include <external/Box2D/include/Box2D/Collision/Shapes/b2PolygonShape.h>
//#include <external/Box2D/include/Box2D/Dynamics/b2Fixture.h>

#include "GameScene.h"

USING_NS_CC;

namespace PlatformerGame {

    enum
    {
        kFilterCategoryLevel = 0x01,
        kFilterCategorySolidObject = 0x02,
        kFilterCategoryNonSolidObject = 0x04
    };

    const float kPixelsPerMeter = 32.0f;
    const float kGravity = -kPixelsPerMeter / 0.7f; // adjust this to taste

    cocos2d::Scene *GameScene::createScene() {
        return GameScene::create();
    }

    bool GameScene::init() {
        if (!Scene::init()) {
            return false;
        }


        loadGameLevel("levels/LevelOne.tmx");

        auto worldLayer = tileMap->getLayer("World");

        this->addChild(tileMap, 1);

        return true;
    }

    void GameScene::setViewPointCenter(CCPoint position) {

        CCSize winSize = CCDirector::sharedDirector()->getWinSize();

        int x = MAX(position.x, winSize.width/2);
        int y = MAX(position.y, winSize.height/2);
        x = MIN(x, (tileMap->getMapSize().width * this->tileMap->getTileSize().width) - winSize.width / 2);
        y = MIN(y, (tileMap->getMapSize().height * tileMap->getTileSize().height) - winSize.height/2);
        CCPoint actualPosition = ccp(x, y);

        CCPoint centerOfView = ccp(winSize.width/2, winSize.height/2);
        CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
        this->setPosition(viewPoint);
    }

    void GameScene::loadGameLevel(std::string level) {

        createPhysicalWorld();

        tileMap = TMXTiledMap::create(level);

        prepareLayers();
    }

    void GameScene::prepareLayers()
    {
        for (auto& object : this->tileMap->getChildren())
        {
            auto layer = dynamic_cast<TMXLayer*>(object);
            if (layer != nullptr) {
                if (layer->getLayerName().compare("BGFake") != 0) {
                    this->createFixtures(layer);
                }
            }
        }
    }

    void GameScene::createFixtures(TMXLayer* layer)
    {
        // create all the rectangular fixtures for each tile
        Size layerSize = layer->getLayerSize();
        for (int y = 0; y < layerSize.height; y++)
        {
            for (int x = 0; x < layerSize.width; x++)
            {
                // create a fixture if this tile has a sprite
                auto tileSprite = layer->getTileAt(Point(x, y));
                if (tileSprite)
                    this->createRectangularFixture(layer, x, y, 1.1f, 1.1f);
            }
        }
    }

    void GameScene::createRectangularFixture(TMXLayer* layer, int x, int y, float width, float height)
    {
        // get position & size
        auto p = layer->getPositionAt(Point(x,y));
        auto tileSize = this->tileMap->getTileSize();
        const float pixelsPerMeter = 32.0f;

        // note: creating the 'world' member variable
        // is discussed in the next chapter

        // create the body
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(
                (p.x + (tileSize.width / 2.0f)) / pixelsPerMeter,
                (p.y + (tileSize.height / 2.0f)) / pixelsPerMeter
        );

        b2Body* body = world->CreateBody(&bodyDef);

        // define the shape
        b2PolygonShape shape;
        shape.SetAsBox(
                (tileSize.width / pixelsPerMeter) * 0.5f * width,
                (tileSize.width / pixelsPerMeter) * 0.5f * height
        );

        // create the fixture
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        fixtureDef.restitution = 0.0f;
        fixtureDef.filter.categoryBits = kFilterCategoryLevel;
        fixtureDef.filter.maskBits = 0xffff;
        body->CreateFixture(&fixtureDef);
    }

    void GameScene::createPhysicalWorld()
    {
        world = new b2World(b2Vec2(0.0f, kGravity));
        world->SetAllowSleeping(true);
        world->SetContinuousPhysics(true);
        world->SetContactListener(this);
    }
}