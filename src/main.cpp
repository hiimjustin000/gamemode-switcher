#include <defs.hpp>
#include <ui/SwitcherPopup.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

namespace switcher {

    struct SWITCHER_DLL HookPauseLayer : public Modify<HookPauseLayer, PauseLayer> {
        void customSetup() {
            PauseLayer::customSetup();

            auto rightMenu = static_cast<CCMenu*>(this->getChildByID("right-button-menu"));
            if(!rightMenu) {
                log::error("right-button-menu not found, returning");
                return;
            }

            auto button = CCMenuItemExt::createSpriteExtraWithFrameName("GJ_editModeBtn_001.png", 0.675f, [=](CCObject*) {
                auto thing = switcher::SwitcherPopup::create();
                thing->show();
            });
            button->setID("gamemode-editor-button"_spr);
            rightMenu->addChild(button);
            rightMenu->updateLayout();
        }
    };
}