#include <ui/SwitcherPopup.hpp>
#include <hooks/PlayLayer.hpp>

using namespace geode::prelude;

namespace switcher {

    SwitcherPopup* SwitcherPopup::create() {
        SwitcherPopup* ret = new SwitcherPopup();
        if(ret->initAnchored(360, 200, "GJ_square02.png")) {
            ret->autorelease();
            return ret;
        }
        delete ret;
        return nullptr;
    }

    bool SwitcherPopup::setup() {
        setTitle("Edit Player", "bigFont.fnt");

        auto closeSpr = ButtonSprite::create("OK");
        setCloseButtonSpr(closeSpr);
        closeSpr->setScale(0.9f);
        m_closeBtn->setPosition(ccp(m_mainLayer->getContentWidth() / 2, 25));

        m_gamemodeMenu = CCMenu::create();
        m_gamemodeMenu->setLayout(RowLayout::create()->setGap(15));
        m_mainLayer->addChildAtPosition(m_gamemodeMenu, Anchor::Center, ccp(0, 30));

        m_gamemodeBtns[0] = createGamemode("gj_iconBtn_on_001.png", "gj_iconBtn_off_001.png", 0);
        m_gamemodeBtns[1] = createGamemode("gj_shipBtn_on_001.png", "gj_shipBtn_off_001.png", 1);
        m_gamemodeBtns[2] = createGamemode("gj_ballBtn_on_001.png", "gj_ballBtn_off_001.png", 2);
        m_gamemodeBtns[3] = createGamemode("gj_birdBtn_on_001.png", "gj_birdBtn_off_001.png", 3);
        m_gamemodeBtns[4] = createGamemode("gj_dartBtn_on_001.png", "gj_dartBtn_off_001.png", 4);
        m_gamemodeBtns[5] = createGamemode("gj_robotBtn_on_001.png", "gj_robotBtn_off_001.png", 5);
        m_gamemodeBtns[6] = createGamemode("gj_spiderBtn_on_001.png", "gj_spiderBtn_off_001.png", 6);
        m_gamemodeBtns[7] = createGamemode("gj_swingBtn_on_001.png", "gj_swingBtn_off_001.png", 7);

        int playerState = HookPlayLayer::get()->getCurrentPlayerState();
        for(CCMenuItemSpriteExtra* btn : m_gamemodeBtns) {
            if(!btn) break;
            m_gamemodeMenu->addChild(btn);
            btn->setEnabled(btn->getTag() == playerState);
        }
        m_gamemodeMenu->updateLayout();

        return true;
    }

    CCMenuItemSpriteExtra* SwitcherPopup::createGamemode(const char* spriteOn, const char* spriteOff, int action) {
        auto ret = CCMenuItemExt::createSpriteExtraWithFrameName(spriteOff, 0.8f, [=](CCObject*){});
        ret->setTag(action);
        auto disabledImage = CCSprite::createWithSpriteFrameName(spriteOn);
        disabledImage->setScale(0.8f);
        ret->setDisabledImage(disabledImage);
        return ret;
    }
}