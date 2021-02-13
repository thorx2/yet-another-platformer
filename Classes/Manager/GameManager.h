//
// Created by gaudh on 2/4/2021.
//

#ifndef PROJ_ANDROID_GAMEMANAGER_H
#define PROJ_ANDROID_GAMEMANAGER_H


#include <GenericClasses/BaseActor.h>

namespace PlatformerGame {

    enum UIButtonType {
        eLeftMove,
        eRightMove,
        eAttackMove,
        eJumpMove,
        eInGameMenu
    };

    class GameManager {
    public:
        static GameManager* GetInstance();

        void OnInteractionReceived(UIButtonType buttonHit);

        void OnInteractionStopped(UIButtonType buttonHit);

        void SetPlayerActor(BaseActor* player);

        BaseActor* GetPCActor();

    private:
        GameManager();

        BaseActor* m_player;
    };
}



#endif //PROJ_ANDROID_GAMEMANAGER_H
