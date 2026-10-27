#include "gf/field/gf_field_dmg.h"

#include "framework/coli/coli_object.h"

namespace gf {

void GfFieldDmgManager::destroy() {
  if (get() != nullptr) {
    delete get();
  }
}

GfFieldDmg::GfFieldDmg(const CreateInfo *info) : unknown08(true), unknown09(false), unknown10(nullptr), unknown18(0xffffffff), unknown1c(0.0f), unknown20(false) {
  if (info != nullptr) {
    create(*info);
  }
}

void GfFieldDmg::create(const CreateInfo &info) {
  dispose();
  unknown08 = info.unknown00;
  unknown09 = true;
}

void GfFieldDmg::dispose() {
  unknown20 = false;
  unknown18 = fw::COLI_INVALID_DAMAGE_ID;
  unknown1c = 0.0f;
  unknown10 = nullptr;
  unknown08 = true;
  unknown09 = false;
}

s32 GfFieldDmg::calculateDamage(u32 maxHp, u8 rate, f32 reduction) {
  u32 damage = static_cast<u32>(static_cast<f32>(rate * maxHp) * 0.01f);
  return damage - static_cast<u32>(static_cast<f32>(damage) * reduction);
}

} // namespace gf
