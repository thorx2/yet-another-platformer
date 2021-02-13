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

    void GameManager::OnInteractionReceived(UIButtonType buttonHit) {
        switch (buttonHit) {
            case eLeftMove:
                m_player->GetBodySprite()->setFlippedX(false);
                m_player->SetActorState(ActorState::eMoving);
                break;
            case eRightMove:
                m_player->GetBodySprite()->setFlippedX(true);
                m_player->SetActorState(ActorState::eMoving);
                break;
            case eAttackMove:
                break;
            case eJumpMove:
                m_player->SetActorState(ActorState::eJumpStart);
                break;
            case eInGameMenu:
                break;
        }
    }

    void GameManager::OnInteractionStopped(UIButtonType buttonHit) {
        switch (buttonHit) {
            case eLeftMove:
                m_player->SetActorState(ActorState::eIdle);
                break;
            case eRightMove:
                m_player->SetActorState(ActorState::eIdle);
                break;
            case eAttackMove:
                break;
            case eJumpMove:
                break;
            case eInGameMenu:
                break;
        }
    }

    void GameManager::SetPlayerActor(BaseActor *player) {
        m_player = player;
    }

    BaseActor* GameManager::GetPCActor() {
        return m_player;
    }
}