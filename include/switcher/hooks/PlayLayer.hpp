#ifndef PLAYLAYER_HPP
#define PLAYLAYER_HPP

#include <defs.hpp>
#include <Geode/modify/PlayLayer.hpp>

namespace switcher {

    struct HookPlayLayer : geode::Modify<HookPlayLayer, PlayLayer> {
        int getCurrentPlayerState();
        int getCurrentBoostState();

        void performActionsOnPlayer(std::array<int, 5>& actions);
        inline void performActionOnPlayer(int action);

        static HookPlayLayer* get();
    };
}
#endif