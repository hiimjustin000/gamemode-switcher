#ifndef GJBASEGAMELAYER_HPP
#define GJBASEGAMELAYER_HPP

#include <defs.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>

namespace switcher {

    struct SWITCHER_DLL HookGJBaseGameLayer : geode::Modify<HookGJBaseGameLayer, GJBaseGameLayer> {
        struct Fields {
            bool m_isPlayLayer = false;
        };

        bool init();
        bool canBeActivatedByPlayer(PlayerObject* p0, EffectGameObject* p1);
        bool isPortalObject(GameObjectType type);
    };
}
#endif