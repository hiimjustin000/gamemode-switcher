#ifndef PLAYLAYER_HPP
#define PLAYLAYER_HPP

#include <defs.hpp>
#include <Geode/modify/PlayLayer.hpp>

namespace switcher {

    struct HookPlayLayer : geode::Modify<HookPlayLayer, PlayLayer> {
        int getCurrentPlayerState();

        static HookPlayLayer* get();
    };
}
#endif