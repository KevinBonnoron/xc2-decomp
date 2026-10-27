#include "gf/game/gf_game_stuck_meter.h"

#include "framework/coli/coli_object.h"
#include "mm_mtl/reference_object.h"

namespace gf {

void GfGameStuckMeter::CreateInfo::dispose() { mm::mtl::safeRelease(unknown08); }

void GfGameStuckMeter::CreateInfo::setColiObj(fw::ColiMoveObject *object) {
  mm::mtl::safeRelease(unknown08);
  unknown08 = object;
  if (object != nullptr) {
    object->addRef();
  }
}

GfGameStuckMeter::GfGameStuckMeter(const CreateInfo *info)
    : unknown00(1.0f), unknown04(0.5f), unknown08(nullptr), unknown10(1.0f), unknown18(0.0f), unknown1c(0.0f), unknown20(1.0f), unknown30(mm::Vec3::zero), unknown40(mm::Vec3::zero), unknown50(0.0f),
      unknown54(0.0f) {
  if (info != nullptr) {
    create(*info);
  }
}

void GfGameStuckMeter::dispose() {
  if (unknown08 != nullptr) {
    unknown08->resetCharacter(unknown18, unknown1c);
    mm::mtl::safeRelease(unknown08);
  }
}

bool GfGameStuckMeter::isStuck() const { return unknown04 <= unknown54; }

} // namespace gf
