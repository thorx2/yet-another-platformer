//
// Created by gaudh on 2/4/2021.
//

#ifndef PROJ_ANDROID_GAMEMANAGER_H
#define PROJ_ANDROID_GAMEMANAGER_H


namespace PlatformerGame {

    class GameManager {
    public:
        static GameManager* GetInstance();

    private:
        GameManager();
    };
}



#endif //PROJ_ANDROID_GAMEMANAGER_H
