//
// Created by gaudh on 2/5/2021.
//

#include <UIComponents/OnScreenController.h>
#include "audio/include/AudioEngine.h"
#include "MainScene.h"
#include "GameScene.h"

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

        auto spritecache = SpriteFrameCache::getInstance();

        spritecache->addSpriteFramesWithFile("tpassets/envtpfiles/bgparallax.plist",
                                             "tpassets/envtpfiles/bgparallax.png");

        m_parallaxNode = ParallaxNode::create();

        for (int i = 0; i < 6; i++) {
            int cloudType = (rand() % 3) + 1;

            char buff[100];

            snprintf(buff, sizeof(buff), "Background/Small Cloud %d.png", cloudType);

            std::string buffAsStdStr = buff;

            int posOffsetX = random(origin.x, visibleSize.width);

            int posOffsetY = random(origin.y, visibleSize.height / 2) + visibleSize.height / 2;

            m_parallaxNode->addChild(Sprite::createWithSpriteFrameName(buffAsStdStr),
                               2,
                               Vec2(random(0.01f, 0.3f),random(0.01f, 0.3f)),
                               Vec2(posOffsetX,posOffsetY));
        }

        m_parallaxNode->setPosition(Vec2::ZERO);

        auto bgImage = Sprite::createWithSpriteFrameName("Background/BG Image.png");

        bgImage->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        bgImage->setScale(3);

        bgImage->setColor(Color3B(200,200,200));

        this->addChild(bgImage, 0);

        this->addChild(m_parallaxNode, 1);

        auto titleOne = Label::createWithTTF("Yet Another", "fonts/Hanalei-Regular.ttf", 36);
        auto titleTwo = Label::createWithTTF("PLATFORMER", "fonts/Hanalei-Regular.ttf", 42);
        titleOne->enableOutline(Color4B::BLACK, 1);
        titleTwo->enableOutline(Color4B::BLACK, 1);
        if (titleOne != nullptr) {

            titleOne->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                    origin.y + visibleSize.height -
                                            titleOne->getContentSize().height - 5));

            titleTwo->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                       origin.y + visibleSize.height -
                                       titleOne->getContentSize().height - titleTwo->getContentSize().height - 5));

            this->addChild(titleOne, 2);

            this->addChild(titleTwo, 2);
        }

        auto newGameButton = MenuItemFont::create("New Game", CC_CALLBACK_1(MainScene::newGameStartFunction, this));
        newGameButton->setFontNameObj("fonts/StalinistOne-Regular.ttf");
        newGameButton->setFontSizeObj(16);

        auto exitGame = MenuItemFont::create("Quit", CC_CALLBACK_1(MainScene::quitGameButton, this));
        exitGame->setFontNameObj("fonts/StalinistOne-Regular.ttf");
        exitGame->setFontSizeObj(16);

        auto menu = Menu::create(newGameButton, exitGame, nullptr);

        menu->alignItemsVerticallyWithPadding(15);

        menu->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

        addChild(menu, 5);

        auto listener = EventListenerTouchAllAtOnce::create();
        listener->onTouchesMoved = CC_CALLBACK_2(MainScene::onTouchesMoved, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
//        cocos2d::experimental::AudioEngine::play2d("Music/MainMenuBGM.mp3", true, 0.7f);

        return true;
    }

    void MainScene::onTouchesMoved(const std::vector<Touch*>& touches, Event  *event) {
        auto diff = touches[0]->getDelta() / 100;
        auto currentPos = m_parallaxNode->getPosition();
        m_parallaxNode->setPosition(currentPos + diff);
    }

    void MainScene::newGameStartFunction(Ref *pSender) {
        cocos2d::experimental::AudioEngine::stopAll();
        Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::create()));
    }

    void MainScene::quitGameButton(Ref *pSender) {
        Director::getInstance()->end();
    }
}
