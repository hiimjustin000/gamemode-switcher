#include <hooks/PlayLayer.hpp>

using namespace geode::prelude;

namespace switcher {

    int HookPlayLayer::getCurrentPlayerState() {
        if(m_player1->isInBasicMode()) return 0;
        else if(m_player1->m_isShip) return 1;
        else if(m_player1->m_isBall) return 2;
        else if(m_player1->m_isBird) return 3;
        else if(m_player1->m_isDart) return 4;
        else if(m_player1->m_isRobot) return 5;
        else if(m_player1->m_isSpider) return 6;
        else if(m_player1->m_isSwing) return 7;

        return -1;
    }

    HookPlayLayer* HookPlayLayer::get() {
        return static_cast<HookPlayLayer*>(GameManager::get()->m_playLayer);
    }
}