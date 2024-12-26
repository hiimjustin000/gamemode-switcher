#ifndef SWITCHERPOPUP_HPP
#define SWITCHERPOPUP_HPP

#include <defs.hpp>

namespace switcher {

    class SWITCHER_DLL SwitcherPopup : public geode::Popup<> {
    protected:
        cocos2d::CCMenu* m_gamemodeMenu = nullptr;
        CCMenuItemSpriteExtra* m_okBtn = nullptr;

        std::array<CCMenuItemSpriteExtra*, 8> m_gamemodeBtns = {};
    public:
        static SwitcherPopup* create();
        bool setup();
        int getCurrentAction();

        CCMenuItemSpriteExtra* createGamemode(const char* spriteOn, const char* spriteOff, int action);
    };
}
#endif