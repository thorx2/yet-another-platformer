//
// Created by gaudh on 2/5/2021.
//

//#include <external/Box2D/include/Box2D/Dynamics/b2Body.h>
//#include <external/Box2D/include/Box2D/Collision/Shapes/b2PolygonShape.h>
//#include <external/Box2D/include/Box2D/Dynamics/b2Fixture.h>

#include <cocos/2d/CCNode.h>
#include <GenericClasses/EnemyPlayer.h>
#include <UIComponents/OnScreenController.h>
#include <B2DebugDraw/B2DebugDrawLayer.h>
#include "GameScene.h"

USING_NS_CC;

namespace PlatformerGame {

    enum {
        kFilterCategoryLevel = 0x01,
        kFilterCategorySolidObject = 0x02,
        kFilterCategoryNonSolidObject = 0x04
    };

    const float kPixelsPerMeter = 32.0f;
    const float kGravity = -kPixelsPerMeter / 0.7f;

    const float kUpdateInterval = 1.0f / 60.0f;
    const double kSecondsPerUpdate = 0.1;

    cocos2d::Scene *GameScene::createScene() {
        return GameScene::create();
    }

    bool GameScene::init() {
        if (!Scene::init()) {
            return false;
        }

        loadGameLevel("levels/LevelOne.tmx");

        auto worldLayer = m_tileMap->getLayer("World");

        auto layer = OnScreenController::create();

        this->addChild(layer, 3);

        this->addChild(m_tileMap, -1);

        this->addChild(B2DebugDrawLayer::create(m_world, 1), 9999);

        scheduleUpdate();

        return true;
    }

    void GameScene::draw(Renderer renderer, const Mat4 &transform, uint32_t flags)
    {
        GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION );
        Director* director = Director::getInstance();
        CCASSERT(nullptr != director, "Director is null when seting matrix stack");
        director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
        m_world->DrawDebugData();
        director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    }

    void GameScene::setViewPointCenter(CCPoint position) {

        CCSize winSize = CCDirector::sharedDirector()->getWinSize();

        int x = MAX(position.x, winSize.width/2);
        int y = MAX(position.y, winSize.height/2);
        x = MIN(x, (m_tileMap->getMapSize().width * this->m_tileMap->getTileSize().width) - winSize.width / 2);
        y = MIN(y, (m_tileMap->getMapSize().height * m_tileMap->getTileSize().height) - winSize.height / 2);
        CCPoint actualPosition = ccp(x, y);

        CCPoint centerOfView = ccp(winSize.width/2, winSize.height/2);
        CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
        this->setPosition(viewPoint);
    }

    void GameScene::loadGameLevel(std::string level) {

        createPhysicalWorld();

        m_tileMap = TMXTiledMap::create(level);

        prepareLayers();

        addObjects();
    }

    void GameScene::prepareLayers() {
        for (auto& object : this->m_tileMap->getChildren()) {
            auto layer = dynamic_cast<TMXLayer*>(object);
            if (layer != nullptr) {
                if (layer->getLayerName().compare("BGFake") != 0) {
                    this->createFixtures(layer);
                }
            }
        }
    }

    void GameScene::createFixtures(TMXLayer* layer) {
        Size layerSize = layer->getLayerSize();
        for (int y = 0; y < layerSize.height; y++)
        {
            for (int x = 0; x < layerSize.width; x++)
            {
                auto tileSprite = layer->getTileAt(Point(x, y));
                if (tileSprite) {
                    this->createRectangularFixture(layer, x, y, 32, 32);
                }
            }
        }
    }

    void GameScene::createRectangularFixture(TMXLayer* layer, int x, int y, float width, float height) {
        auto p = layer->getPositionAt(Point(x,y));
        auto tileSize = this->m_tileMap->getTileSize();
        const float pixelsPerMeter = 32.0f;

        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(
                (p.x + (tileSize.width / 2.0f)) / pixelsPerMeter,
                (p.y + (tileSize.height / 2.0f)) / pixelsPerMeter
        );

        b2Body* body = m_world->CreateBody(&bodyDef);

        b2PolygonShape shape;
        shape.SetAsBox(
                (tileSize.width / pixelsPerMeter) * 0.5f * width,
                (tileSize.width / pixelsPerMeter) * 0.5f * height
        );

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        fixtureDef.restitution = 0.0f;
        fixtureDef.filter.categoryBits = kFilterCategoryLevel;
        fixtureDef.filter.maskBits = 0xffff;
        body->CreateFixture(&fixtureDef);
    }

    void GameScene::createPhysicalWorld() {
        m_world = new b2World(b2Vec2(1.0f, kGravity));
        m_world->SetAllowSleeping(true);
        m_world->SetContinuousPhysics(true);
        m_world->SetContactListener(this);
    }

    double GameScene::getCurrentTimeInSeconds() {
        static struct timeval currentTime;
        gettimeofday(&currentTime, nullptr);
        return (currentTime.tv_sec) + (currentTime.tv_usec / 1000000.0);
    }

    void GameScene::addObjects() {
        auto objectGroups = m_tileMap->getObjectGroups();
        for (auto& objectGroup : objectGroups) {
            auto objects = objectGroup->getObjects();

            for (auto& object : objects) {
                auto properties = object.asValueMap();
                auto type = properties.at("type");

                if (!type.isNull()) {
                    addChild(addObject(type.asString().c_str(), properties), 0);
                    m_objectCount++;
                }
            }
        }
    }

    BaseActor* GameScene::addObject(std::string className, ValueMap& properties) {

        BaseActor* o = nullptr;
        if(className == "Player") {
            o = EnemyPlayer::CreateEnemyOfType(EnemyPlayer::EnemyType::eCRABBY, m_world, Vec2(properties["x"].asFloat(), properties["y"].asFloat()));
            setViewPointCenter(o->getPosition());
        }
        else if(className == "Monster") {
            o = EnemyPlayer::CreateEnemyOfType(EnemyPlayer::EnemyType::ePINKSTAR, m_world, Vec2(properties["x"].asFloat(), properties["y"].asFloat()));
        }
        else if(className == "MagicChest") {
            o = EnemyPlayer::CreateEnemyOfType(EnemyPlayer::EnemyType::eFIERCETOOTH, m_world, Vec2(properties["x"].asFloat(), properties["y"].asFloat()));
        }

        return o;
    }

    void GameScene::update(float delta) {

        currentTime = getCurrentTimeInSeconds();

        if (!lastTickTime) {
            lastTickTime = currentTime;
        }

        double frameTime = currentTime - lastTickTime;

        accumulator += frameTime;

        m_world->Step(delta, 1, 1);

        while (accumulator > kSecondsPerUpdate) {
            accumulator -= kSecondsPerUpdate;
            for (b2Body *body = m_world->GetBodyList(); body != NULL; body = body->GetNext()) {
                if (body->GetUserData()) {
                    BaseActor *sprite = (BaseActor*) body->GetUserData();
                    sprite->setPosition(ccp(body->GetPosition().x, body->GetPosition().y));
                    sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(body->GetAngle()));
                }
            }
        }

        lastTickTime = currentTime;
    }
}