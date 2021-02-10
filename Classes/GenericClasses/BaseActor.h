//
// Created by gaudh on 2/4/2021.
//

#ifndef PROJ_ANDROID_BASEACTOR_H
#define PROJ_ANDROID_BASEACTOR_H

#include <string>
#include <Box2D/Box2D.h>
#include <cocos/2d/CCSprite.h>
#include <cocos/2d/CCAnimation.h>

namespace PlatformerGame {
    enum ActorState {
        eDefaultState,
        eIdle,
        eMoving,
        eJumpStart,
        eJumpMid,
        eJumpEnd,
        eGetHit,
        eAttack,
        eDie,
        eMaxState
    };

    class BaseActor : public cocos2d::Node {
    public:
        void ChangeWepon(std::string stringWeponClass);

        void PlayAnimation(std::string animName);

        void SetActorState(ActorState state);

        virtual ~BaseActor();

        virtual void setPosition(const cocos2d::Vec2 &position);

    protected:
        BaseActor(std::string characterName, b2World* world, cocos2d::Vec2 pos);

    private:

        enum
        {
            kFilterCategoryLevel = 0x01,
            kFilterCategorySolidObject = 0x02,
            kFilterCategoryNonSolidObject = 0x04
        };

        b2Body* m_physicsBody;

        cocos2d::Sprite* m_body;

        cocos2d::Sprite* m_weponSprite;

        cocos2d::Sprite* m_effectSprite;

        ActorState m_actorState;

        ActorState m_previousState;

        std::vector<cocos2d::Animation*> m_stateAniamtionList;

        void update(float dt);

        void createFixture(b2Shape* shape);

        void addRectangularFixtureToBody(float width, float height);

        void addCircularFixtureToBody(float radius);

        void addBodyToWorld(b2World* world, cocos2d::Vec2 pos);
    };
}


#endif //PROJ_ANDROID_BASEACTOR_H
