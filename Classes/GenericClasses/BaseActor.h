//
// Created by gaudh on 2/4/2021.
//

#ifndef PROJ_ANDROID_BASEACTOR_H
#define PROJ_ANDROID_BASEACTOR_H

#include <string>
#include <cocos/2d/CCSprite.h>

namespace PlatformerGame {
    enum ActorState {
        eIdle,
        eMoving,
        eJumpStart,
        eJumpMid,
        eJumpEnd,
        eGetHit,
        eAttack,
        eDie
    };

    class BaseActor : cocos2d::Sprite {
    public:

        BaseActor(std::string characterName);

        void ChangeWepon(std::string stringWeponClass);

        void PlayAnimation(std::string animName);

        void SetActorState(ActorState state);

    private:

        cocos2d::Sprite m_weponSprite;

        cocos2d::Sprite m_effectSprite;

        ActorState m_actorState;

        void updateActor();
    };
}


#endif //PROJ_ANDROID_BASEACTOR_H
