#ifndef PLAYLAYER_HPP
#define PLAYLAYER_HPP

#include <defs.hpp>
#include <Geode/modify/PlayLayer.hpp>

namespace switcher {

    struct SWITCHER_DLL HookPlayLayer : geode::Modify<HookPlayLayer, PlayLayer> {
        struct Fields {
            bool m_portalsEnabled = true;
        };

        int getCurrentPlayerState();
        int getCurrentBoostState();

        void performActionsOnPlayer(std::array<int, 7>& actions);
        inline void performActionOnPlayer(int action);

        static HookPlayLayer* get();
    };
}
#endif