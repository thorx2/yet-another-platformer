//
// Created by gaudh on 2/8/2021.
//

#ifndef PROJ_ANDROID_ENEMYPLAYER_H
#define PROJ_ANDROID_ENEMYPLAYER_H

#include <string>
#include "BaseActor.h"

namespace PlatformerGame {
    class EnemyPlayer : public BaseActor {
    public:
        enum EnemyType {
            eCRABBY,
            ePINKSTAR,
            eFIERCETOOTH
        };
        enum EnemyStatus {
            ePATROL,
            eATTACKING,
        };

        static EnemyPlayer* CreateEnemyOfType(EnemyType eType, b2World* world, cocos2d::Vec2 pos);

    protected:
        void update(float dt) override;

    private:
        EnemyPlayer(std::string enemyName, b2World* world, cocos2d::Vec2 pos);
    };
}

#endif //PROJ_ANDROID_ENEMYPLAYER_H
