//
// Created by gaudh on 2/4/2021.
//

#ifndef PROJ_ANDROID_GAMEMANAGER_H
#define PROJ_ANDROID_GAMEMANAGER_H


namespace PlatformerGame {

    enum UIButton {
        eLeftMove,
        eRightMove,
        eAttack,
        eJump,
        eInGameMenu
    };

    class GameManager {
    public:
        static GameManager* GetInstance();

        void OnInteractionReceived(UIButton buttonHit);

        void OnInteractionStopped(UIButton buttonHit);

    private:
        GameManager();
    };
}



#endif //PROJ_ANDROID_GAMEMANAGER_H
