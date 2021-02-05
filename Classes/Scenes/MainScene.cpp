//
// Created by gaudh on 2/5/2021.
//

#include "MainScene.h"

USING_NS_CC;

namespace PlatformerGame {

    cocos2d::Scene *MainScene::createScene() {
        return MainScene::create();
    }

    bool MainScene::init() {
        if (!Scene::init()) {
            return false;
        }

        auto spritecache = SpriteFrameCache::getInstance();

        auto visibleSize = Director::getInstance()->getVisibleSize();

        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        spritecache->addSpriteFramesWithFile("tpassets/enemy/enemy.plist", "tpassets/enemy/enemy.png");

        auto something = SpriteFrameCache::getInstance()->getSpriteFrameByName("TheCrustyCrew/Crabby/01-Idle/Idle 04.png");

        auto mySprite = Sprite::createWithSpriteFrame(something);

        mySprite->setPosition(
                Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        addChild(mySprite, 1);

        return true;
    }

}
