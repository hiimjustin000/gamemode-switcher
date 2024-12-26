#include <ui/SwitcherPopup.hpp>
#include <hooks/PlayLayer.hpp>

using namespace geode::prelude;

namespace switcher {

    SwitcherPopup* SwitcherPopup::create() {
        SwitcherPopup* ret = new SwitcherPopup();
        if(ret->initAnchored(400, 240, "geode.loader/GE_square02.png")) {
            ret->autorelease();
            return ret;
        }
        delete ret;
        return nullptr;
    }

    bool SwitcherPopup::setup() {
        setTitle("Edit Player", "bigFont.fnt");
        addCorners(Corner::Blue, Corner::Blue);

        auto closeSpr = ButtonSprite::create("OK");
        setCloseButtonSpr(closeSpr);
        closeSpr->setScale(0.9f);
        m_closeBtn->m_pfnSelector = menu_selector(SwitcherPopup::onClose);
        m_closeBtn->setPosition(ccp(m_mainLayer->getContentWidth() / 2, 25));

        m_gamemodeMenu = CCMenu::create();
        m_gamemodeMenu->setLayout(RowLayout::create()->setGap(15));
        m_mainLayer->addChildAtPosition(m_gamemodeMenu, Anchor::Center, ccp(0, 60));

        m_speedMenu = CCMenu::create();
        m_speedMenu->setLayout(RowLayout::create()->setGap(15));
        m_mainLayer->addChildAtPosition(m_speedMenu, Anchor::Center, ccp(0, 5));

        m_miscMenu = CCMenu::create();
        m_miscMenu->setLayout(RowLayout::create()->setGap(15));
        m_mainLayer->addChildAtPosition(m_miscMenu, Anchor::Center, ccp(0, -50));

        m_localGamemodeState = HookPlayLayer::get()->getCurrentPlayerState();
        m_localSpeedState = HookPlayLayer::get()->getCurrentBoostState();

        m_gamemodeBtns[0] = createGamemode("gj_iconBtn_on_001.png", "gj_iconBtn_off_001.png", 0);
        m_gamemodeBtns[1] = createGamemode("gj_shipBtn_on_001.png", "gj_shipBtn_off_001.png", 1);
        m_gamemodeBtns[2] = createGamemode("gj_ballBtn_on_001.png", "gj_ballBtn_off_001.png", 2);
        m_gamemodeBtns[3] = createGamemode("gj_birdBtn_on_001.png", "gj_birdBtn_off_001.png", 3);
        m_gamemodeBtns[4] = createGamemode("gj_dartBtn_on_001.png", "gj_dartBtn_off_001.png", 4);
        m_gamemodeBtns[5] = createGamemode("gj_robotBtn_on_001.png", "gj_robotBtn_off_001.png", 5);
        m_gamemodeBtns[6] = createGamemode("gj_spiderBtn_on_001.png", "gj_spiderBtn_off_001.png", 6);
        m_gamemodeBtns[7] = createGamemode("gj_swingBtn_on_001.png", "gj_swingBtn_off_001.png", 7);

        m_speedBtns[0] = createSpeed("boost_01_001.png", 8);
        m_speedBtns[1] = createSpeed("boost_02_001.png", 9);
        m_speedBtns[2] = createSpeed("boost_03_001.png", 10);
        m_speedBtns[3] = createSpeed("boost_04_001.png", 11);
        m_speedBtns[4] = createSpeed("boost_05_001.png", 12);

        m_miscBtns[0] = createMisc("platOn.png"_spr, "platOff.png"_spr, 13);
        m_miscBtns[1] = createMisc("sizeOn.png"_spr, "sizeOff.png"_spr, 14);
        m_miscBtns[2] = createMisc("gravOn.png"_spr, "gravOff.png"_spr, 15);

        for(CCMenuItemSpriteExtra* btn : m_gamemodeBtns) {
            if(!btn) continue;
            m_gamemodeMenu->addChild(btn);
        }
        m_gamemodeMenu->updateLayout();

        for(CCMenuItemSpriteExtra* btn : m_speedBtns) {
            if(!btn) continue;
            m_speedMenu->addChild(btn);
        }
        m_speedMenu->updateLayout();

        for(CCMenuItemToggler* btn : m_miscBtns) {
            if(!btn) break;
            m_miscMenu->addChild(btn);
        }
        m_miscMenu->updateLayout();

        return true;
    }

    void SwitcherPopup::onClose(CCObject* sender) {
        HookPlayLayer::get()->performActionsOnPlayer(m_actions);
        Popup::onClose(sender);
    }

    CCMenuItemSpriteExtra* SwitcherPopup::createGamemode(const char* spriteOn, const char* spriteOff, int action) {
        auto ret = CCMenuItemExt::createSpriteExtraWithFrameName(spriteOff, 0.9f, [this](CCObject* sender){
            m_actions[0] = sender->getTag();
            m_localGamemodeState = m_actions[0];
            updateGamemodeButtons();
        });

        ret->setTag(action);

        auto disabledImage = CCSprite::createWithSpriteFrameName(spriteOn);
        disabledImage->setScale(0.9f);
        
        ret->setDisabledImage(disabledImage);
        ret->setEnabled(action != m_localGamemodeState);
        return ret;
    }

    CCMenuItemSpriteExtra* SwitcherPopup::createSpeed(const char* sprite, int action) {
        auto normalImage = CCSprite::createWithSpriteFrameName(sprite);
        normalImage->setScale(0.85f);
        normalImage->setOpacity(150);

        auto ret = CCMenuItemExt::createSpriteExtra(normalImage, [this](CCObject* sender){
            m_actions[1] = sender->getTag();
            m_localSpeedState = m_actions[1];
            updateSpeedButtons();
        });

        ret->setTag(action);
        auto disabledImage = CCSprite::createWithSpriteFrameName(sprite);
        disabledImage->setScale(0.85f);

        ret->setDisabledImage(disabledImage);
        ret->setEnabled(action != m_localSpeedState + 8);
        return ret;
    }

    CCMenuItemToggler* SwitcherPopup::createMisc(const char* spriteOn, const char* spriteOff, int action) {
        auto ret = CCMenuItemExt::createTogglerWithFrameName(spriteOn, spriteOff, 0.9f, [this](CCObject* sender){
            if(m_actions[sender->getTag() - 11] == sender->getTag()) m_actions[sender->getTag() - 11] = -1;
            else m_actions[sender->getTag() - 11] = sender->getTag();
            //updateMiscButtons();
        });

        ret->setTag(action);

        auto disabledImage = CCSprite::createWithSpriteFrameName(spriteOn);
        disabledImage->setScale(0.9f);

        ret->toggle(disabledImage);
        switch(action) {
            case 13: ret->toggle(HookPlayLayer::get()->m_player1->m_isPlatformer); break;
            case 14: ret->toggle(HookPlayLayer::get()->m_player1->m_vehicleSize == 0.6f); break;
            case 15: ret->toggle(HookPlayLayer::get()->m_player1->m_isUpsideDown); break;
            default: ret->toggle(false); break;
        }
        return ret;
    }

    void SwitcherPopup::updateGamemodeButtons() {
        for(CCMenuItemSpriteExtra* btn : m_gamemodeBtns) {
            btn->setEnabled(btn->getTag() != m_localGamemodeState);
        }
    }

    void SwitcherPopup::updateSpeedButtons() {
        for(CCMenuItemSpriteExtra* btn : m_speedBtns) {
            btn->setEnabled(btn->getTag() != m_localSpeedState);
        }
    }
}