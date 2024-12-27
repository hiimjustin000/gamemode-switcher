#ifndef SWITCHERPOPUP_HPP
#define SWITCHERPOPUP_HPP

#include <defs.hpp>
#include <ui/PopupWithCorners.hpp>

namespace switcher {

    class SWITCHER_DLL SwitcherPopup : public PopupWithCorners<> {
    protected:
        std::array<CCMenuItemSpriteExtra*, 8> m_gamemodeBtns = {};
        cocos2d::CCMenu* m_gamemodeMenu = nullptr;

        std::array<CCMenuItemSpriteExtra*, 5> m_speedBtns = {};
        cocos2d::CCMenu* m_speedMenu = nullptr;

        std::array<CCMenuItemToggler*, 5> m_miscBtns = {};
        cocos2d::CCMenu* m_miscMenu = nullptr;

        std::array<int, 7> m_actions = {-1, -1, -1, -1, -1, -1, -1};
        int m_localGamemodeState = 0;
        int m_localSpeedState = 0;
    public:
        static SwitcherPopup* create();
        bool setup() override;
        int getCurrentAction();
        void onClose(cocos2d::CCObject*) override;

        void updateGamemodeButtons();
        void updateSpeedButtons();

        CCMenuItemSpriteExtra* createGamemode(const char* spriteOn, const char* spriteOff, int action);
        CCMenuItemSpriteExtra* createSpeed(const char* sprite, int action);
        CCMenuItemToggler* createMisc(const char* spriteOn, const char* spriteOff, int action);
    };
}
#endif