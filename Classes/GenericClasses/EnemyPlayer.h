//
// Created by gaudh on 2/8/2021.
//

#ifndef PROJ_ANDROID_ENEMYPLAYER_H
#define PROJ_ANDROID_ENEMYPLAYER_H

#include <string>
#include "BaseActor.h"

namespace PlatformerGame {
    class EnemyPlayer : public BaseActor {
    private:
        EnemyPlayer(std::string enemyName, b2World* world, cocos2d::Vec2 pos);
    public:
        enum EnemyType {
            eCRABBY,
            ePINKSTAR,
            eFIERCETOOTH
        };
        static EnemyPlayer* CreateEnemyOfType(EnemyType eType, b2World* world, cocos2d::Vec2 pos);
    };
}

#endif //PROJ_ANDROID_ENEMYPLAYER_H
