//
// Created by gaudh on 2/8/2021.
//

#include "EnemyPlayer.h"
namespace PlatformerGame {

    EnemyPlayer *EnemyPlayer::CreateEnemyOfType(EnemyPlayer::EnemyType eType, b2World* world, cocos2d::Vec2 pos) {
        switch (eType) {
            case eCRABBY:
                return new EnemyPlayer("Crabby", world, pos);
                break;
            case eFIERCETOOTH:
                return new EnemyPlayer("PinkStar", world, pos);
                break;
            case ePINKSTAR:
                return new EnemyPlayer("FierceTooth", world, pos);
                break;
            default:
                return nullptr;
                break;
        }
    }

    EnemyPlayer::EnemyPlayer(std::string enemyName, b2World* world, cocos2d::Vec2 pos) : BaseActor(enemyName, world, pos) {

    }

    void EnemyPlayer::update(float dt) {
        BaseActor::update(dt);
    }
}