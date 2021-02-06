//
// Created by gaudh on 2/4/2021.
//

#include "GameManager.h"

namespace PlatformerGame {

    static GameManager* instance = nullptr;

    GameManager::GameManager() {

    }

    GameManager *GameManager::GetInstance() {
        if (instance == nullptr) {
            instance = new GameManager();
        }

        return instance;
    }

    void GameManager::OnInteractionReceived(UIButton buttonHit) {

    }

    void GameManager::OnInteractionStopped(UIButton buttonHit) {

    }
}