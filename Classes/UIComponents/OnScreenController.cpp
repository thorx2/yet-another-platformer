//
// Created by gaudh on 2/5/2021.
//

#include <cocos/2d/CCSpriteFrameCache.h>
#include <Manager/GameManager.h>
#include "OnScreenController.h"

USING_NS_CC;

/*
 * TODO: Try Buttons instead of Sprites
 * There has to be a better way to manage these objects.
 */

namespace PlatformerGame {

    bool OnScreenController::init() {

        if (!Layer::init()) {
            return false;
        }

        auto touchListener = EventListenerTouchAllAtOnce::create();

        touchListener->onTouchesBegan = [&](const std::vector<Touch*>& touches, Event* evt){
            onTouchesBegan(touches, evt);
        };

        touchListener->onTouchesEnded = [&](const std::vector<Touch*>& touches, Event* evt){
            onTouchesEnded(touches, evt);
        };

        touchListener->onTouchesMoved = [&](const std::vector<Touch*>& touches, Event* evt){
            log("onTouchesMoved");
        };


        auto spritecache = SpriteFrameCache::getInstance();

        auto visibleSize = Director::getInstance()->getVisibleSize();

        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        spritecache->addSpriteFramesWithFile("tpassets/uiandcontrolls/controlls.plist",
                                             "tpassets/uiandcontrolls/controlls.png");

        leftButton = Sprite::createWithSpriteFrameName("MobileButtons/Buttons/3.png");
        rightButton = Sprite::createWithSpriteFrameName("MobileButtons/Buttons/4.png");
        attackButton = Sprite::createWithSpriteFrameName("MobileButtons/Buttons/5.png");
        jumpButton = Sprite::createWithSpriteFrameName("MobileButtons/Buttons/6.png");
        closeButton = Sprite::createWithSpriteFrameName("MobileButtons/Buttons/7.png");

        float x = origin.x + visibleSize.width - closeButton->getContentSize().width;
        float y = origin.y + visibleSize.height - closeButton->getContentSize().height;
        closeButton->setPosition(Vec2(x, y));

        x = origin.x + leftButton->getContentSize().width + 5;
        y = origin.y + leftButton->getContentSize().height + 5;
        leftButton->setPosition(Vec2(x, y));

        x = origin.x + (rightButton->getContentSize().width * 3) + 5;
        y = origin.y + rightButton->getContentSize().height + 5;
        rightButton->setPosition(Vec2(x, y));

        x = origin.x + visibleSize.width - (attackButton->getContentSize().width * 3) - 5;
        y = origin.y + attackButton->getContentSize().height + 5;
        attackButton->setPosition(Vec2(x, y));

        x = origin.x + visibleSize.width - jumpButton->getContentSize().width - 5;
        y = origin.y + (jumpButton->getContentSize().height * 3)+ 5;
        jumpButton->setPosition(Vec2(x, y));

        this->addChild(closeButton);
        this->addChild(leftButton);
        this->addChild(rightButton);
        this->addChild(jumpButton);
        this->addChild(attackButton);

        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

        return true;
    }

    cocos2d::Scene *OnScreenController::createScene() {
        auto scene = Scene::create();
        auto layer = OnScreenController::create();
        scene->addChild(layer);
        return scene;
    }

    void OnScreenController::onTouchesBegan(const std::vector<Touch*>& touches, Event  *event) {

        for(auto touch : touches) {
            if (closeButton->getBoundingBox().containsPoint(touch->getLocation())) {
                closeButton->setOpacity(200);
                GameManager::GetInstance()->OnInteractionReceived(eInGameMenu);
            } else if (leftButton->getBoundingBox().containsPoint(touch->getLocation())) {
                leftButton->setOpacity(200);
                GameManager::GetInstance()->OnInteractionReceived(eLeftMove);
            } else if (rightButton->getBoundingBox().containsPoint(touch->getLocation())) {
                rightButton->setOpacity(200);
                GameManager::GetInstance()->OnInteractionReceived(eRightMove);
            } else if (attackButton->getBoundingBox().containsPoint(touch->getLocation())) {
                attackButton->setOpacity(200);
                GameManager::GetInstance()->OnInteractionReceived(eAttack);
            } else if (jumpButton->getBoundingBox().containsPoint(touch->getLocation())) {
                jumpButton->setOpacity(200);
                GameManager::GetInstance()->OnInteractionReceived(eJump);
            }
        }
    }

    void OnScreenController::onTouchesEnded(const std::vector<Touch*>& touches, Event  *event) {
        for(auto touch : touches) {
            if (closeButton->getBoundingBox().containsPoint(touch->getLocation())) {
                closeButton->setOpacity(255);
                Director::getInstance()->end();
            } else if (leftButton->getBoundingBox().containsPoint(touch->getLocation())) {
                leftButton->setOpacity(255);
            } else if (rightButton->getBoundingBox().containsPoint(touch->getLocation())) {
                rightButton->setOpacity(255);
            } else if (attackButton->getBoundingBox().containsPoint(touch->getLocation())) {
                attackButton->setOpacity(255);
            } else if (jumpButton->getBoundingBox().containsPoint(touch->getLocation())) {
                jumpButton->setOpacity(255);
            }
        }
    }

    void OnScreenController::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event) {

    }
}