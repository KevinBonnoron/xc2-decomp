#include "event/ui_manager.h"

namespace event {

void UIManager::render() {}

bool UIManager::isOpenSkipUI() const { return (flags & FLAG_SKIP) != 0; }

bool UIManager::isOpenCommonUI() const { return (flags & (FLAG_COMMON | FLAG_COMMON_FADE)) != 0; }

bool UIManager::isFieldSkill() const { return (flags & FLAG_FIELD_SKILL) != 0; }

bool UIManager::isOpenShopUI() const { return (flags & FLAG_SHOP) != 0; }

u32 UIManager::getPayoffUI() const { return mPayoffResult; }

bool UIManager::isOpenPayoffUI() const { return (flags & FLAG_PAYOFF) != 0; }

bool UIManager::isOpenRewardUI() const { return (flags & FLAG_REWARD) != 0; }

bool UIManager::isOpenChapTelopUI() const { return (flags & FLAG_CHAP_TELOP) != 0; }

bool UIManager::isAvanTitleUI() const { return (flags & FLAG_AVAN_TITLE) != 0; }

bool UIManager::isZoneTelopUI() const { return (flags & FLAG_ZONE_TELOP) != 0; }

bool UIManager::isOpenHomuraHikariUI() const { return (flags & FLAG_HOMURA_HIKARI) != 0; }

void UIManager::finishNewGameWait() { flags |= FLAG_NEW_GAME_WAIT_END; }

bool UIManager::isNewGameWait() const { return (flags & FLAG_NEW_GAME_WAIT) != 0; }

bool UIManager::isOpenMinigame() const { return (flags & FLAG_MINIGAME) != 0; }

} // namespace event
