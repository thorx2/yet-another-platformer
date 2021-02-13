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

        auto spriteCache = SpriteFrameCache::getInstance();

        auto visibleSize = Director::getInstance()->getVisibleSize();

        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        //TODO Make this assignment better
        leftButton = ui::Button::create("MobileButtons/Buttons/3.png", "", "", cocos2d::ui::Button::TextureResType::PLIST);
        leftButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType touchType){
            switch (touchType) {
                case ui::Widget::TouchEventType::BEGAN:
                    GameManager::GetInstance()->OnInteractionReceived(UIButtonType::eLeftMove);
                    leftButton->setOpacity(200);
                    break;
                case ui::Widget::TouchEventType::CANCELED:
                case ui::Widget::TouchEventType::ENDED:
                    GameManager::GetInstance()->OnInteractionStopped(UIButtonType::eLeftMove);
                    leftButton->setOpacity(255);
                    break;
                case ui::Widget::TouchEventType::MOVED:
                    break;
            }
        });
        rightButton = ui::Button::create("MobileButtons/Buttons/4.png", "", "", cocos2d::ui::Button::TextureResType::PLIST);
        rightButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType touchType){
            switch (touchType) {
                case ui::Widget::TouchEventType::BEGAN:
                    GameManager::GetInstance()->OnInteractionReceived(UIButtonType::eRightMove);
                    rightButton->setOpacity(200);
                    break;
                case ui::Widget::TouchEventType::CANCELED:
                case ui::Widget::TouchEventType::ENDED:
                    rightButton->setOpacity(255);
                    GameManager::GetInstance()->OnInteractionStopped(UIButtonType::eRightMove);
                    break;
                case ui::Widget::TouchEventType::MOVED:
                    break;
            }
        });
        attackButton = ui::Button::create("MobileButtons/Buttons/5.png", "", "", cocos2d::ui::Button::TextureResType::PLIST);
        attackButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType touchType){
            switch (touchType) {
                case ui::Widget::TouchEventType::BEGAN:
                    attackButton->setOpacity(200);
                    break;
                case ui::Widget::TouchEventType::CANCELED:
                case ui::Widget::TouchEventType::ENDED:
                    attackButton->setOpacity(255);
                    break;
                case ui::Widget::TouchEventType::MOVED:
                    break;
            }
        });
        closeButton = ui::Button::create("MobileButtons/Buttons/7.png", "", "", cocos2d::ui::Button::TextureResType::PLIST);
        closeButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType touchType){
            switch (touchType) {
                case ui::Widget::TouchEventType::BEGAN:
                    closeButton->setOpacity(200);
                    Director::getInstance()->end();
                    break;
                case ui::Widget::TouchEventType::CANCELED:
                case ui::Widget::TouchEventType::ENDED:
                    closeButton->setOpacity(255);
                    break;
                case ui::Widget::TouchEventType::MOVED:
                    break;
            }
        });
        jumpButton = ui::Button::create("MobileButtons/Buttons/6.png", "", "", cocos2d::ui::Button::TextureResType::PLIST);
        jumpButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType touchType){
            switch (touchType) {
                case ui::Widget::TouchEventType::BEGAN:
                    jumpButton->setOpacity(200);
                    GameManager::GetInstance()->OnInteractionReceived(UIButtonType::eJumpMove);
                    break;
                case ui::Widget::TouchEventType::CANCELED:
                case ui::Widget::TouchEventType::ENDED:
                    jumpButton->setOpacity(255);
                    break;
                case ui::Widget::TouchEventType::MOVED:
                    break;
            }
        });

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

        this->addChild(closeButton, 2);
        this->addChild(leftButton, 2);
        this->addChild(rightButton, 2);
        this->addChild(jumpButton, 2);
        this->addChild(attackButton, 2);

        return true;
    }

    cocos2d::Scene *OnScreenController::createScene() {
        auto scene = Scene::create();
        auto layer = OnScreenController::create();
        scene->addChild(layer);
        return scene;
    }
}