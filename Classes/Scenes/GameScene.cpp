//
// Created by gaudh on 2/5/2021.
//

#include "GameScene.h"

namespace PlatformerGame {

    cocos2d::Scene *GameScene::createScene() {
        return GameScene::create();
    }

    bool GameScene::init() {
        if (!Scene::init()) {
            return false;
        }

        return true;
    }
}