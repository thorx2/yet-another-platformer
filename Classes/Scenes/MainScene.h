//
// Created by gaudh on 2/5/2021.
//

#ifndef PROJ_ANDROID_MAINSCENE_H
#define PROJ_ANDROID_MAINSCENE_H

#include "cocos2d.h"

namespace PlatformerGame {
    class MainScene : public cocos2d::Scene {
    public:
        static cocos2d::Scene *createScene();

        virtual bool init();

        CREATE_FUNC(MainScene);
    private:
        cocos2d::ParallaxNode* m_parallaxNode = nullptr;

        void newGameStartFunction(Ref *pSender);
        void quitGameButton(Ref *pSender);

        void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    };
}


#endif //PROJ_ANDROID_MAINSCENE_H
