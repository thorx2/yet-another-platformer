//
// Created by gaudh on 2/4/2021.
//

#include<string>
#include <cocos/2d/CCSpriteFrameCache.h>
#include <cocos/2d/CCActionInterval.h>
#include "BaseActor.h"

USING_NS_CC;

namespace PlatformerGame {

    const float kPixelsPerMeter = 32.0f;
    const float kGravity = -kPixelsPerMeter / 0.7f;

    const std::string IDLE_PREFIX = "01-Idle";
    const int IDLE_FRAMES = 8;

    const std::string RUN_PREFIX = "02-Run";
    const int RUN_FRAMES = 8;

    const std::string JUMP_PREFIX = "03-Jump";
    const int JUMP_FRAMES = 8;

    const std::string FALL_PREFIX = "04-Fall";
    const int FALL_FRAMES = 8;

    const std::string GROUND_PREFIX = "05-Ground";
    const int GROUND_FRAMES = 8;

    const std::string HIT_PREFIX = "08-Hit";
    const int HIT_FRAMES = 8;

    const std::string ATTACK_PREFIX = "07-Attack";
    const int ATTACK_FRAMES = 8;

    const std::string DIE_PREFIX = "01-Idle";
    const int DIE_FRAMES = 8;

    BaseActor::BaseActor(std::string characterName, b2World* world, cocos2d::Vec2 pos) {
        auto spritecache = SpriteFrameCache::getInstance();

        spritecache->addSpriteFramesWithFile("tpassets/enemy/enemy.plist",
                                             "tpassets/enemy/enemy.png");

        std::string defaultImage = "TheCrustyCrew/" + characterName + "/" + IDLE_PREFIX + "/" + "Idle 01.png";

        auto defaultFrame = spritecache->getSpriteFrameByName(defaultImage);

        m_body = Sprite::createWithSpriteFrame(defaultFrame);

        m_actorState = eIdle;

        m_previousState = eIdle;

        schedule(CC_SCHEDULE_SELECTOR(BaseActor::update), 0.03f);

        for (int i = 0; i < 5; i++) {
            Animation* anim = new Animation;
            Vector<SpriteFrame*> frames;

            for (int j = 1; j <= IDLE_FRAMES; j++) {
                std::string frameName = "TheCrustyCrew/";
                frameName.append(characterName);
                frameName.append("/");
                frameName.append(IDLE_PREFIX);
                frameName.append("/");
                frameName.append("Idle 0");
                frameName.append(std::to_string(j));
                frameName.append(".png");

                frames.pushBack(spritecache->getSpriteFrameByName(frameName));
            }
            std::reverse(frames.begin(), frames.end());

            anim->initWithSpriteFrames(frames, 0.1f);

            anim->setLoops(-1);

            m_stateAniamtionList.push_back(anim);
        }

        std::reverse(m_stateAniamtionList.begin(), m_stateAniamtionList.end());

        addBodyToWorld(world, pos);

        addRectangularFixtureToBody(1,1);

        m_body->runAction(Animate::create(m_stateAniamtionList.front()));

        setPosition(pos);

        addChild(m_body);
    }

    void BaseActor::ChangeWepon(std::string stringWeponClass) {

    }

    void BaseActor::PlayAnimation(std::string animName) {

    }

    void BaseActor::SetActorState(ActorState state) {
        m_actorState = state;
    }

    void BaseActor::update(float dt) {
        for (int i = eDefaultState; i < eMaxState; i++) {
            if (i == m_actorState && m_actorState != m_previousState) {

            }
        }

        m_body->update(dt);
    }

    BaseActor::~BaseActor() {

    }

    void BaseActor::addBodyToWorld(b2World* world, Vec2 pos) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(pos.x,pos.y);
        bodyDef.userData = m_body;
        bodyDef.fixedRotation = true;
        m_physicsBody = world->CreateBody(&bodyDef);
    }

    void BaseActor::addCircularFixtureToBody(float radius) {
        b2CircleShape shape;
        shape.m_radius = radius * this->getScale();
        this->createFixture(&shape);
    }

    void BaseActor::addRectangularFixtureToBody(float width, float height) {
        b2PolygonShape shape;
        shape.SetAsBox(
                width * this->getScale(),
                height * this->getScale()
        );
        this->createFixture(&shape);
    }

    void BaseActor::createFixture(b2Shape* shape) {
        b2FixtureDef fixtureDef;
        fixtureDef.shape = shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.7f;
        fixtureDef.restitution = 0.1f;
        fixtureDef.filter.categoryBits = kFilterCategorySolidObject;
        fixtureDef.filter.maskBits = 0xffff;
        this->m_physicsBody->CreateFixture(&fixtureDef);
    }

    void BaseActor::setPosition(const Vec2 &position) {
        Node::setPosition(position);
        m_body->setPosition(0, 0);
    }
}