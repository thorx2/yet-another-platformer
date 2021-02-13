//
// Created by gaudh on 2/5/2021.
//

#include <cocos/2d/CCNode.h>
#include <GenericClasses/EnemyPlayer.h>
#include <B2DebugDraw/B2DebugDrawLayer.h>
#include <Manager/GameManager.h>
#include <AudioEngine.h>
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

        auto spriteCache = SpriteFrameCache::getInstance();

        spriteCache->addSpriteFramesWithFile("tpassets/enemy/enemy.plist",
                                             "tpassets/enemy/enemy.png");
        spriteCache->addSpriteFramesWithFile("tpassets/uiandcontrolls/controlls.plist",
                                             "tpassets/uiandcontrolls/controlls.png");

        loadGameLevel("levels/LevelOne.tmx");

        auto worldLayer = m_tileMap->getLayer("World");

        m_onScreenController = OnScreenController::create();

        this->addChild(m_onScreenController, 3);

        this->addChild(m_tileMap, 0);

        scheduleUpdate();

        auto debugLayer = B2DebugDrawLayer::create(m_world, 32);
        debugLayer->setGlobalZOrder(99);
        this->addChild(debugLayer);

        cocos2d::experimental::AudioEngine::play2d("Music/InGameBGM.mp3", true, 0.7f);

        return true;
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

        if (m_onScreenController != nullptr) {
            m_onScreenController->setPosition(viewPoint);
        }

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

        for (int y = 0; y < layerSize.height; y++) {
            for (int x = 0; x < layerSize.width; x++) {

                auto tileSprite = layer->getTileAt(Point(x, y));

                if (tileSprite) {
                    this->createRectangularFixture(layer, x, y, 1, 1);
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
    void GameScene::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
    {
        //
        // IMPORTANT:
        // This is only for debug purposes
        // It is recommend to disable it
        //
        Scene::draw(renderer, transform, flags);

        GL::enableVertexAttribs( cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION );
        Director* director = Director::getInstance();
        CCASSERT(nullptr != director, "Director is null when setting matrix stack");
        director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

        _modelViewMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

        _customCommand.init(_globalZOrder);
        _customCommand.func = CC_CALLBACK_0(GameScene::onDraw, this);
        renderer->addCommand(&_customCommand);

        director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    }

    void GameScene::onDraw()
    {
        Director* director = Director::getInstance();
        CCASSERT(nullptr != director, "Director is null when setting matrix stack");

        auto oldMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
        director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewMV);
        m_world->DrawDebugData();
        director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, oldMV);
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
                    BaseActor* actor = addObject(type.asString().c_str(), properties);
                    if (actor != nullptr) {
                        addChild(actor, 0);
                        actor->setPosition(ccp(properties.at("x").asFloat(), properties.at("y").asFloat()));
                        m_objectCount++;
                    }
                }
            }
        }
    }

    BaseActor* GameScene::addObject(std::string className, ValueMap& properties) {
        BaseActor* o = nullptr;
        if(className == "Player") {
            o = EnemyPlayer::CreateEnemyOfType(EnemyPlayer::EnemyType::eCRABBY, m_world, Vec2(properties["x"].asFloat(), properties["y"].asFloat()));
            GameManager::GetInstance()->SetPlayerActor(o);
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

        m_world->Step(delta, 8, 1);

        if (GameManager::GetInstance()->GetPCActor() != nullptr) {
            setViewPointCenter(GameManager::GetInstance()->GetPCActor()->getPosition());
        }

        lastTickTime = currentTime;
    }
}