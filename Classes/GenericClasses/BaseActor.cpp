//
// Created by gaudh on 2/4/2021.
//

#include<string>
#include <cocos/2d/CCSpriteFrameCache.h>
#include <cocos/2d/CCActionInterval.h>
#include "BaseActor.h"

USING_NS_CC;

namespace PlatformerGame {

    BaseActor::BaseActor(std::string characterName, b2World* world, cocos2d::Vec2 pos) {

        auto spriteCache = SpriteFrameCache::getInstance();

        for(auto animData : DefaultPlayerAnimationData) {
            Animation* anim = new Animation();
            Vector<SpriteFrame*> frames;

            for (int i = 1; i <= animData.second.begin()->second; i++) {

                std::string animFamily = animData.second.begin()->first;

                animFamily = animFamily.substr(animFamily.find("-") + 1, animFamily.length());

                std::string frameName = "TheCrustyCrew/";
                frameName.append(characterName); // TheCrustyCrew/Crabby
                frameName.append("/"); // TheCrustyCrew/Crabby/
                frameName.append(animData.second.begin()->first); // TheCrustyCrew/Crabby/<Data?>
                frameName.append("/"); // TheCrustyCrew/Crabby/<Data?>/
                frameName.append(animFamily);
                frameName.append(" 0");
                frameName.append(std::to_string(i));
                frameName.append(".png");

                frames.pushBack(spriteCache->getSpriteFrameByName(frameName));

                if (m_body == nullptr) {
                    m_body = extension::PhysicsSprite::createWithSpriteFrameName(frameName.c_str());
                }
            }

            std::reverse(frames.begin(), frames.end());

            anim->initWithSpriteFrames(frames, 0.1f);

            if (animData.second.begin()->first.find("Idle") != std::string::npos ||
                animData.second.begin()->first.find("Run") != std::string::npos) {
                anim->setLoops(-1);
            }

            m_stateAniamtionList.insert({static_cast<ActorState>(animData.first), anim});
        }

        m_actorState = eIdle;

        m_previousState = eIdle;

        m_body->setPTMRatio(32);

        addBodyToWorld(world, pos);

        m_body->runAction(Animate::create(m_stateAniamtionList[eIdle]));

        addRectangularFixtureToBody();

        m_body->setB2Body(m_physicsBody);

        setPosition(pos);

        scheduleUpdate();

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

                m_previousState = m_actorState;

                m_body->stopAllActions();

                switch (m_actorState) {
                    case eIdle:
                    case eGetHit:
                    case eMoving:
                        m_body->runAction(Animate::create(m_stateAniamtionList[m_actorState]));
                        break;
                    case eJumpStart:
                        m_physicsBody->ApplyLinearImpulseToCenter(b2Vec2(0, 100), true);
                        m_actorState = eJumpMid;
                        break;
                    case eJumpMid:
                        break;
                    case eJumpEnd:
                        break;
                    case eAttack:
                        m_body->runAction(Animate::create(m_stateAniamtionList[m_actorState]));
                        break;
                    case eDie:
                        break;
                }
            }
        }
        m_body->update(dt);
    }

    BaseActor::~BaseActor() {

    }

    void BaseActor::addBodyToWorld(b2World* world, Vec2 pos) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.fixedRotation = true;
        bodyDef.position.Set(pos.x / 32,pos.y / 32);
        m_physicsBody = world->CreateBody(&bodyDef);
    }

    void BaseActor::addRectangularFixtureToBody() {
        b2PolygonShape shape;
        shape.SetAsBox(0.5f,0.5f);
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.7f;
        m_physicsBody->CreateFixture(&fixtureDef);
    }


    void BaseActor::setPosition(const Vec2 &position) {
        Node::setPosition(position);
        m_body->setPosition(getPosition().x, getPosition().y);
    }

    cocos2d::Sprite *BaseActor::GetBodySprite() {
        return m_body;
    }
}