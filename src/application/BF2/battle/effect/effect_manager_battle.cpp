#include "battle/effect/effect_manager_battle.h"

namespace btl {

void EffectManager::Initialize() {}

void EffectManager::PreUpdate(const fw::UpdateInfo &updateInfo) { get()->PreUpdateProc(updateInfo); }

void EffectManager::PreUpdateProc(const fw::UpdateInfo &) {}

void EffectManager::Update(const fw::UpdateInfo &updateInfo) { get()->UpdateProc(updateInfo); }

} // namespace btl
