#include <hooks/PlayLayer.hpp>

using namespace geode::prelude;

namespace switcher {

    int HookPlayLayer::getCurrentPlayerState() {
        if(m_player1->isInNormalMode()) return 0;
        else if(m_player1->m_isShip) return 1;
        else if(m_player1->m_isBall) return 2;
        else if(m_player1->m_isBird) return 3;
        else if(m_player1->m_isDart) return 4;
        else if(m_player1->m_isRobot) return 5;
        else if(m_player1->m_isSpider) return 6;
        else if(m_player1->m_isSwing) return 7;

        return -1;
    }

    int HookPlayLayer::getCurrentBoostState() {
        float speed = m_player1->m_playerSpeed;

        if(speed == 0.7f) return 0;
        if(speed == 0.9f) return 1;
        if(speed == 1.1f) return 2;
        if(speed == 1.3f) return 3;
        if(speed == 1.6f) return 4;

        return -1;
    }

    HookPlayLayer* HookPlayLayer::get() {
        return static_cast<HookPlayLayer*>(GameManager::get()->m_playLayer);
    }

    void HookPlayLayer::performActionsOnPlayer(std::array<int, 7>& actions) {
        for(int action : actions) {
            if(action == -1) continue;
            performActionOnPlayer(action);
        }
    }

    void HookPlayLayer::performActionOnPlayer(int action) {
        switch(action) {
            case -1: break;
            
            // 0-7 gamemode actions
            case 0: {
                m_player1->toggleFlyMode(false, false);
                m_player1->toggleRollMode(false, false);
                m_player1->toggleBirdMode(false, false);
                m_player1->toggleDartMode(false, false);
                m_player1->toggleRobotMode(false, false);
                m_player1->toggleSpiderMode(false, false);
                m_player1->toggleSwingMode(false, false);
                break;
            }
            case 1: {
                m_player1->toggleFlyMode(true, true);
                break;
            }

            case 2: {
                m_player1->toggleRollMode(true, true);
                break;
            }
            case 3: {
                m_player1->toggleBirdMode(true, true);
                break;
            }
            case 4: {
                m_player1->toggleDartMode(true, true);
                break;
            }
            case 5: {
                m_player1->toggleRobotMode(true, true);
                break;
            }
            case 6: {
                m_player1->toggleSpiderMode(true, true);
                break;
            }
            case 7: {
                m_player1->toggleSwingMode(true, true);
                break;
            }

            //8-12 speed actions
            case 8: {
                m_player1->m_playerSpeed = 0.7f;
                break;
            }
            case 9: {
                m_player1->m_playerSpeed = 0.9f;
                break;
            }
            case 10: {
                m_player1->m_playerSpeed = 1.1f;
                break;
            }
            case 11: {
                m_player1->m_playerSpeed = 1.3f;
                break;
            }
            case 12: {
                m_player1->m_playerSpeed = 1.6f;
                break;
            }

            //13-17 misc
            case 13: {
                m_player1->m_isPlatformer = !m_player1->m_isPlatformer;
#ifdef GEODE_IS_ANDROID
                m_uiLayer->togglePlatformerMode(m_player1->m_isPlatformer);
#endif
                break;
            }
            case 14: {
                m_player1->togglePlayerScale(m_player1->m_vehicleSize != 0.6f, true);
                break;
            }
            case 15: {
                m_player1->flipGravity(!m_player1->m_isUpsideDown, true);
                break;
            }
            case 16: {
                m_player1->doReversePlayer(!m_player1->m_isGoingLeft);
                break;
            }
            case 17: {
                m_fields->m_portalsEnabled = !m_fields->m_portalsEnabled;
                break;
            }
        }

        if(action <= 7) {
            auto obj = TeleportPortalObject::create("edit_eGameRotBtn_001.png", true);
            obj->m_cameraIsFreeMode = true;
            this->playerWillSwitchMode(m_player1, obj);
        }
    }
}