//
// Created by gaudh on 2/4/2021.
//

#include "BaseActor.h"

USING_NS_CC;

namespace PlatformerGame {

    const std::string IDLE_PREFIX = "01-Idle";
    const int IDLE_FRAMES = 8;

    const std::string RUN_PREFIX = "02-Run";
    const int RUN_FRAMES = 8;

    const std::string JUMP_PREFIX = "01-Idle";
    const int JUMP_FRAMES = 8;

    const std::string FALL_PREFIX = "01-Idle";
    const int FALL_FRAMES = 8;

    const std::string GROUND_PREFIX = "01-Idle";
    const int GROUND_FRAMES = 8;

    const std::string HIT_PREFIX = "01-Idle";
    const int HIT_FRAMES = 8;

    const std::string ATTACK_PREFIX = "01-Idle";
    const int ATTACK_FRAMES = 8;

    const std::string DIE_PREFIX = "01-Idle";
    const int DIE_FRAMES = 8;

    BaseActor::BaseActor(std::string characterName) {
        m_actorState = eIdle;
    }
}