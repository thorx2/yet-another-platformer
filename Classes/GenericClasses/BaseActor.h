//
// Created by gaudh on 2/4/2021.
//

#ifndef PROJ_ANDROID_BASEACTOR_H
#define PROJ_ANDROID_BASEACTOR_H

#include <string>
#include <map>
#include <Box2D/Box2D.h>
#include <cocos/2d/CCSprite.h>
#include <cocos/2d/CCAnimation.h>
#include "extensions/cocos-ext.h"

namespace PlatformerGame {
    enum ActorState {
        eDefaultState,
        eIdle,
        eMoving,
        eJumpStart,
        eJumpMid,
        eJumpEnd,
        ePreAttack,
        eAttack,
        eGetHit,
        eDie,
        eMaxState
    };

    class BaseActor : public cocos2d::extension::PhysicsSprite {
    public:
        void ChangeWepon(std::string stringWeponClass);

        void PlayAnimation(std::string animName);

        void SetActorState(ActorState state);

        virtual ~BaseActor();

    protected:
        BaseActor(std::string characterName, b2World* world, cocos2d::Vec2 pos);

        virtual void update(float dt);

    private:
        bool m_tempFrameAssigned = false;

        const std::map<int, std::map<std::string, int>> DefaultPlayerAnimationData = {
                {eIdle, {{"01-Idle", 9}}},
                {eMoving, {{"02-Run", 6}}},
                {eJumpStart, {{"03-Jump", 3}}},
                {eJumpMid, {{"04-Fall", 1}}},
                {eJumpEnd, {{"05-Ground", 2}}},
                {ePreAttack, {{"06-Anticipation", 3}}},
                {eAttack, {{"07-Attack", 4}}},
                {eGetHit, {{"08-Hit", 4}}},
        };

        const float kPixelsPerMeter = 32.0f;
        const float kGravity = -kPixelsPerMeter / 0.7f;

        enum
        {
            kFilterCategoryLevel = 0x01,
            kFilterCategorySolidObject = 0x02,
            kFilterCategoryNonSolidObject = 0x04
        };

        b2Body* m_physicsBody;

        cocos2d::Sprite* m_weponSprite;

        cocos2d::Sprite* m_effectSprite;

        ActorState m_actorState;

        ActorState m_previousState;

        std::map<ActorState, cocos2d::Animation*> m_stateAniamtionList;

        void addRectangularFixtureToBody();

        void addBodyToWorld(b2World* world, cocos2d::Vec2 pos);
    };
}


#endif //PROJ_ANDROID_BASEACTOR_H
