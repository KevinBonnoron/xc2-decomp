#include "gf/game/gf_game_player_picker.h"

#include "framework/reference_frame.h"
#include "fw/fw_coli_check.h"
#include "fw/fw_debug.h"
#include "fw/fw_pad.h"
#include "fw/fw_transform.h"
#include "gf/game/gf_game_player_formation.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_util.h"
#include "mm_mtl/intrusive_ptr.h"

namespace gf {

constexpr u32 PICK_UNKNOWN_2 = 0x2;         // Inferred role: pick toggle button; original name unknown.
constexpr u32 PICK_UNKNOWN_4 = 0x4;         // Inferred role: pick snap to ground button; original name unknown.
constexpr u32 PICK_UNKNOWN_16 = 0x10;       // Inferred role: pick modifier button; original name unknown.
constexpr u32 PICK_UNKNOWN_32 = 0x20;       // Inferred role: pick move up button; original name unknown.
constexpr u32 SPEED_UNKNOWN_12288 = 0x3000; // Inferred role: speed up buttons; original name unknown.
constexpr u32 SPEED_UNKNOWN_49152 = 0xc000; // Inferred role: speed down buttons; original name unknown.
constexpr u32 SPEED_UNKNOWN_3 = 3;          // Inferred role: speed level max; original name unknown.

// Inferred role: movement speeds per speed level; original name unknown.
static const f32 unknown001[] = {0.5f, 1.0f, 2.0f, 5.0f};

void GfGamePlayerPicker::build(const GfSetupParam &param) {
#line 44
  GfGamePlayerPicker *picker = new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfGamePlayerPicker();
  picker->setup(param);
}

void GfGamePlayerPicker::setup(const GfSetupParam &) {}

void GfGamePlayerPicker::destroy() {
  GfGamePlayerPicker *picker = get();
  picker->cleanup();
  delete picker;
}

void GfGamePlayerPicker::cleanup() {}

void GfGamePlayerPicker::update(const fw::UpdateInfo &info) {
  GfGamePlayerPicker *picker = get();
  if (picker != nullptr) {
    picker->updateImpl(info);
  }
}

void GfGamePlayerPicker::updateImpl(const fw::UpdateInfo &) {
  const fw::PadData *padData = fw::PadManager::getControlPadData(0);
  u32 hold = padData->unknown00;
  u32 trigger = padData->unknown04;
  bool isToggle = (trigger & PICK_UNKNOWN_2) != 0;
  bool isLocked = (hold & PICK_UNKNOWN_16) == 0 && !unknown24;
  if (isToggle && !isLocked && isEnableChange()) {
    unknown24 = !unknown24;
    if (unknown24) {
      onActive();
    } else {
      onDeactive();
    }

    return;
  }

  if (!unknown24) {
    return;
  }

  if ((hold & PICK_UNKNOWN_16) == 0) {
    unknown25 = true;
  }

  if ((trigger & SPEED_UNKNOWN_12288) != 0) {
    if (unknown20 != SPEED_UNKNOWN_3) {
      unknown20++;
    }
  } else if ((trigger & SPEED_UNKNOWN_49152) != 0 && unknown20 != 0) {
    unknown20--;
  }

  GfObj *obj = GfObjUtil::getObj(getPlayerHandle());
  if (obj == nullptr) {
    return;
  }

  GfComTransform *transform = obj->getComponent<GfComTransform>();
  if (transform != nullptr) {
    calcWorldDir(transform);
    movePlayer(transform);
    dispStatus(transform);
  }
}

bool GfGamePlayerPicker::isPick() {
  GfGamePlayerPicker *picker = get();
  if (picker == nullptr) {
    return false;
  }

  return picker->unknown24;
}

GfGamePlayerPicker::GfGamePlayerPicker() : unknown20(1), unknown24(false), unknown25(false), unknown30(mm::Vec3::unitY), unknown40(mm::Vec3::unitZ), unknown50(mm::Vec3::unitX) {}

GfGamePlayerPicker::~GfGamePlayerPicker() {}

bool GfGamePlayerPicker::isEnableChange() const {
  if (unknown24) {
    return true;
  }

  GfObjProperty *property = GfObjUtil::getProperty(getPlayerHandle());
  return property != nullptr && !property->unknown10->unknown30;
}

void GfGamePlayerPicker::onActive() {
  GfObj *obj = GfObjUtil::getObj(getPlayerHandle());
  if (obj != nullptr) {
    MsgPcResetState message;
    sendMessage(obj, message);
  }

  unknown25 = false;
}

void GfGamePlayerPicker::onDeactive() {
  GfObj *obj = GfObjUtil::getObj(getPlayerHandle());
  if (obj != nullptr) {
    MsgPcResetState message;
    sendMessage(obj, message);
  }
}

GF_OBJ_HANDLE *GfGamePlayerPicker::getPlayerHandle() const { return GfGamePlayerFormation::get()->unknown1a0[0].unknown08; }

void GfGamePlayerPicker::movePlayer(GfComTransform *transform) {
  const fw::PadData *padData = fw::PadManager::getControlPadData(0);
  f32 stickX = padData->unknown1c;
  f32 stickY = padData->unknown20;
  u32 hold = padData->unknown00;
  u32 trigger = padData->unknown04;
  fw::Transform &world = transform->unknown10->unknown003();
  if ((trigger & PICK_UNKNOWN_4) != 0) {
    fw::ColiCheckConfig config;
    config.unknown08 = 0.0f;
    config.unknown0c = 0.0f;
    config.unknown04 = 0xffffffff;
    config.unknown00 = 9;
    config.unknown14 = false;
    config.unknown15 = false;
    config.unknown10 = 1;
    fw::TColiCheckResult<256> result;
    mm::Vec3 end = world.unknown00 - unknown30 * 100.0f;
    fw::ColiCheck::testLine(result, world.unknown00, end, config);
    if (result.getCount() != 0) {
      const mm::Vec3 &hit = result.getPosition(0);
      world.unknown00 = mm::Vec3::unitY * 0.1f + hit;
    }
  } else {
    if ((hold & PICK_UNKNOWN_32) != 0) {
      mm::Vec3 delta = unknown30;
      delta *= unknown001[unknown20];
      world.unknown00 += delta;
    } else if ((hold & PICK_UNKNOWN_16) != 0 && unknown25) {
      mm::Vec3 delta = unknown30;
      delta *= unknown001[unknown20];
      world.unknown00 -= delta;
    }
    mm::Vec3 right = unknown50 * stickX;
    right *= unknown001[unknown20];
    world.unknown00 += right;
    mm::Vec3 front = unknown40 * stickY;
    front *= unknown001[unknown20];
    world.unknown00 += front;
  }
  if (transform->unknown10->unknowna8 != nullptr) {
    transform->unknown10->syncLocalTransform();
  }
  if (transform->unknown18.get() != nullptr) {
    transform->unknown18->syncWorldTransform();
  }
}

void GfGamePlayerPicker::dispStatus(GfComTransform *transform) {
  fw::debug::drawFont(50, 600, "playerをpick中");
  fw::debug::drawFont(50, 620, "移動速度:%.2f", unknown001[unknown20]);
  fw::debug::drawAxis(transform->unknown001()->getSyncedWorldMatrix(), 1.0f);
}

} // namespace gf
