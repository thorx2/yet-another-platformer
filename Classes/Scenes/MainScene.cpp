//
// Created by gaudh on 2/5/2021.
//

#include <UIComponents/OnScreenController.h>
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

        auto visibleSize = Director::getInstance()->getVisibleSize();

        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        auto layer = OnScreenController::create();

        this->addChild(layer, 3);

        auto spritecache = SpriteFrameCache::getInstance();

        spritecache->addSpriteFramesWithFile("tpassets/envtpfiles/bgparallax.plist",
                                             "tpassets/envtpfiles/bgparallax.png");

        auto parallax = ParallaxNode::create();

        for (int i = 0; i < 10; i++) {
            int cloudType = (rand() % 3) + 1;

            char buff[100];

            snprintf(buff, sizeof(buff), "Background/Small Cloud %d.png", cloudType);

            std::string buffAsStdStr = buff;

            parallax->addChild(Sprite::createWithSpriteFrameName(buffAsStdStr),
                               2,
                               Vec2(1.8f,0.0f),
                               Vec2((visibleSize.width / 2 + (origin.x + 350)) + + (rand() % 900 + (-900)),
                                    (visibleSize.height / 2 + origin.y) + (rand() % 150 + (-150))));
        }

        auto go = MoveBy::create(8, Vec2(-10,0));
        auto seq = Sequence::create(go, nullptr);
        parallax->runAction( (RepeatForever::create(seq) ));

        parallax->setPosition(Vec2::ZERO);

        auto bgImage = Sprite::createWithSpriteFrameName("Background/BG Image.png");

        bgImage->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        bgImage->setScale(2.5);

        this->addChild(bgImage, 0);

        this->addChild(parallax, 1);

        return true;
    }
}
