#include "gf/game/gf_game_stuck_meter.h"

#include "framework/coli/coli_object.h"
#include "fw/fw_coli_check.h"
#include "fw/fw_transform.h"
#include "gf/game/gf_game_depop_meter_manager.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/scom/gf_scom_obj.h"
#include "mm_mtl/reference_object.h"

namespace gf {

void GfGameDepopMeter::dispose() {
  if (unknown10 != INVALID_HANDLE) {
    GfGameDepopMeterManager::removeDepopMeter(this);
  }
  unknown10 = INVALID_HANDLE;
  unknown40 = false;
  unknown18 = true;
}

void GfGameDepopMeter::update(f32 deltaTime) {
  if (unknown10 == INVALID_HANDLE || !unknown20) {
    return;
  }
  GfObjAcc acc(unknown10);
  if (!acc.isValid()) {
    return;
  }
  const mm::Vec3 &position = acc.getWorldTransform().unknown00;
  fw::ColiCheckConfig config;
  config.unknown14 = true;
  config.unknown10 = 2;
  config.unknown0c = 0.0f;
  config.unknown08 = 0.0f;
  config.unknown15 = false;
  config.unknown04 = 7;
  config.unknown00 = 9;
  fw::TColiCheckResult<256> result;
  result.clear();
  fw::ColiCheck::testLineChara(result, unknown30, position, config);
  unknown40 = result.isHit;
  if (unknown40 && unknown18) {
    SCOM_DESTROY_GAME_OBJ::create(unknown10, 1.0f, 0);
    dispose();
  }
  unknown30 = position;
}

GfGameDepopMeterManager::GfGameDepopMeterManager(u32 count) : unknown08(count), unknown28(unknown10.end()) {}

#line 1598
void GfGameDepopMeterManager::create(u32 count) {
  if (get() != nullptr) {
    delete get();
  }
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfGameDepopMeterManager(count);
}

void GfGameDepopMeterManager::dispose() {
  if (get() != nullptr) {
    delete get();
  }
}

void GfGameDepopMeterManager::update(f32 deltaTime) {
  GfGameDepopMeterManager *manager = get();
  if (manager != nullptr && !manager->unknown10.empty()) {
    u32 size = manager->unknown10.size();
    u32 count = manager->unknown08;
    if (size < count) {
      count = size;
    }
    for (u32 i = 0; i < count; i++) {
      if (manager->unknown10.end() == manager->unknown28) {
        manager->unknown28 = manager->unknown10.begin();
      }
      manager->unknown28->update(deltaTime);
      manager = get();
      ++manager->unknown28;
    }
  }
}

void GfGameDepopMeterManager::addDepopMeter(GfGameDepopMeter *meter) {
  if (!meter->intoNode()) {
    get()->unknown10.push_back(meter);
    if (get()->unknown10.end() == get()->unknown28) {
      get()->unknown28 = get()->unknown10.begin();
    }
  }
}

void GfGameDepopMeterManager::removeDepopMeter(GfGameDepopMeter *meter) {
  if (meter != nullptr) {
    if (get()->unknown28.operator->() == meter) {
      ++get()->unknown28;
    }
    get()->unknown10.erase(meter);
    if (get()->unknown10.end() == get()->unknown28) {
      get()->unknown28 = get()->unknown10.begin();
    }
  }
}

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

template mm::mtl::PtrSingleton<gf::GfGameDepopMeterManager>::~PtrSingleton();
