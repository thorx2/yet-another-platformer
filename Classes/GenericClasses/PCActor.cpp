//
// Created by gaudh on 2/13/2021.
//

#include "PCActor.h"

namespace PlatformerGame {
    PCActor::PCActor(std::string enemyName, b2World *world, cocos2d::Vec2 pos)
            : BaseActor(enemyName, world, pos) {
    }

    PCActor *PCActor::CreatePOActor(b2World *world, cocos2d::Vec2 pos) {
        return new PCActor("Crabby", world, pos);
    }
}
