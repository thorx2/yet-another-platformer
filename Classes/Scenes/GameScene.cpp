//
// Created by gaudh on 2/5/2021.
//

#include "GameScene.h"

USING_NS_CC;

namespace PlatformerGame {

    cocos2d::Scene *GameScene::createScene() {
        return GameScene::create();
    }

    bool GameScene::init() {
        if (!Scene::init()) {
            return false;
        }

        this->addChild(tileMap, 0);

        return true;
    }

    void GameScene::setViewPointCenter(CCPoint position) {

        CCSize winSize = CCDirector::sharedDirector()->getWinSize();

        int x = MAX(position.x, winSize.width/2);
        int y = MAX(position.y, winSize.height/2);
        x = MIN(x, (tileMap->getMapSize().width * this->tileMap->getTileSize().width) - winSize.width / 2);
        y = MIN(y, (tileMap->getMapSize().height * tileMap->getTileSize().height) - winSize.height/2);
        CCPoint actualPosition = ccp(x, y);

        CCPoint centerOfView = ccp(winSize.width/2, winSize.height/2);
        CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
        this->setPosition(viewPoint);
    }
}