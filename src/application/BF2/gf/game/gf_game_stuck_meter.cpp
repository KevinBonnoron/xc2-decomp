#include "gf/game/gf_game_stuck_meter.h"

#include "framework/coli/coli_object.h"
#include "fw/fw_coli_check.h"
#include "fw/fw_transform.h"
#include "gf/game/gf_game_depop_meter_manager.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/scom/gf_scom_obj.h"
#include "mm_math/mm_mat44.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/unique_ptr.h"

namespace gf {

GfGameDepopMeter::GfGameDepopMeter(const CreateInfo *info) : unknown10(unknown020), unknown18(true), unknown20(true), unknown30(mm::Vec3::zero), unknown40(false) {
  if (info != nullptr) {
    create(*info);
  }
}

void GfGameDepopMeter::dispose() {
  if (unknown10 != unknown020) {
    GfGameDepopMeterManager::removeDepopMeter(this);
  }
  unknown10 = unknown020;
  unknown40 = false;
  unknown18 = true;
}

void GfGameDepopMeter::update(f32 deltaTime) {
  if (unknown10 == unknown020 || !unknown20) {
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
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfGameDepopMeterManager(count);
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

void GfGameStuckMeter::CreateInfo::operator=(const CreateInfo &other) {
  mm::mtl::safeRelease(unknown08);
  unknown00 = other.unknown00;
  unknown04 = other.unknown04;
  unknown08 = other.unknown08;
  if (unknown08 != nullptr) {
    unknown08->addRef();
  }
  unknown10 = other.unknown10;
}

GfGameStuckMeter::GfGameStuckMeter(const CreateInfo *info)
    : unknown00(), unknown18(0.0f), unknown1c(0.0f), unknown20(1.0f), unknown30(mm::Vec3::zero), unknown40(mm::Vec3::zero), unknown50(0.0f), unknown54(0.0f) {
  if (info != nullptr) {
    create(*info);
  }
}

void GfGameStuckMeter::create(const CreateInfo &info) {
  dispose();
  unknown00 = info;
  const fw::unknown031 *shape = unknown00.unknown08->unknowne8.get();
  if (shape != nullptr && shape->unknown00 == fw::unknown031::TYPE_UNKNOWN_3) {
    unknown18 = static_cast<const fw::unknown134 *>(shape)->unknown04;
    unknown1c = static_cast<const fw::unknown134 *>(shape)->unknown08;
  } else {
    unknown20 = unknown00.unknown08->unknowne0;
  }
  const mm::Mat44 &matrix = unknown00.unknown08->getMatrix();
  unknown30 = mm::Vec3(matrix.rows[3][0], matrix.rows[3][1], matrix.rows[3][2]);
  unknown40 = unknown30;
  unknown50 = 0.0f;
  unknown54 = 0.0f;
}

void GfGameStuckMeter::dispose() {
  if (unknown00.unknown08 != nullptr) {
    unknown00.unknown08->resetCharacter(unknown18, unknown1c);
    mm::mtl::safeRelease(unknown00.unknown08);
  }
}

void GfGameStuckMeter::update(f32 deltaTime) {
  if (deltaTime <= 0.0f || unknown00.unknown08 == nullptr) {
    return;
  }
  bool isRestore;
  if (checkStuck(deltaTime)) {
    isRestore = false;
    unknown50 = 0.0f;
    unknown54 += deltaTime;
  } else {
    unknown50 += deltaTime;
    if (unknown50 > 3.0f) {
      isRestore = true;
      unknown54 = 0.0f;
    } else {
      isRestore = false;
    }
  }
  fw::ColiObject *coli = unknown00.unknown08;
  if (coli->unknown30 == fw::COLI_TYPE_UNKNOWN_1) {
    const fw::unknown031 *base = coli->unknowne8.get();
    const fw::unknown134 *shape = base != nullptr && base->unknown00 == fw::unknown031::TYPE_UNKNOWN_3 ? static_cast<const fw::unknown134 *>(base) : nullptr;
    if (isStuck()) {
      if (shape != nullptr) {
        f32 radius = shape->unknown04 * 0.99f <= 0.05f ? 0.05f : shape->unknown04 * 0.99f;
        f32 height = shape->unknown08 * 0.99f <= 0.05f ? 0.05f : shape->unknown08 * 0.99f;
        coli->resetCharacter(radius, height);
      } else {
        coli->unknowne0 = coli->unknowne0 * 0.99f <= 0.05f ? 0.05f : coli->unknowne0 * 0.99f;
      }
    } else if (isRestore) {
      if (shape != nullptr) {
        f32 radius = unknown18 < shape->unknown04 * 1.1f ? unknown18 : shape->unknown04 * 1.1f;
        f32 height = unknown1c < shape->unknown08 * 1.1f ? unknown1c : shape->unknown08 * 1.1f;
        coli->resetCharacter(radius, height);
      } else {
        f32 scale = coli->unknowne0 * 1.1f;
        coli->unknowne0 = unknown20 < scale ? unknown20 : scale;
      }
    }
  }
}

bool GfGameStuckMeter::isStuck() const { return unknown00.unknown04 <= unknown54; }

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfGameDepopMeterManager>::~PtrSingleton();
