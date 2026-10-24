#include "gf/game/gf_game_player_picker.h"
#include "fw/fw_pad.h"
#include "gf/game/gf_game_player_formation.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_util.h"

namespace gf {

constexpr u32 PICK_MODIFIER_BUTTON = 0x10;
constexpr u32 PICK_TOGGLE_BUTTON = 0x2;
constexpr u32 SPEED_UP_BUTTONS = 0x3000;
constexpr u32 SPEED_DOWN_BUTTONS = 0xc000;
constexpr u32 SPEED_LEVEL_MAX = 3;

void GfGamePlayerPicker::build(const GfSetupParam &param) {
  GfGamePlayerPicker *picker = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfGamePlayerPicker();
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
  u32 hold = padData->hold;
  u32 trigger = padData->trigger;
  bool isToggle = (trigger & PICK_TOGGLE_BUTTON) != 0;
  bool isLocked = (hold & PICK_MODIFIER_BUTTON) == 0 && !mIsPick;
  if (isToggle && !isLocked && isEnableChange()) {
    mIsPick = !mIsPick;
    if (mIsPick) {
      onActive();
    } else {
      onDeactive();
    }

    return;
  }

  if (!mIsPick) {
    return;
  }

  if ((hold & PICK_MODIFIER_BUTTON) == 0) {
    mIsModifierReleased = true;
  }

  if ((trigger & SPEED_UP_BUTTONS) != 0) {
    if (mSpeedLevel != SPEED_LEVEL_MAX) {
      mSpeedLevel++;
    }
  } else if ((trigger & SPEED_DOWN_BUTTONS) != 0 && mSpeedLevel != 0) {
    mSpeedLevel--;
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

  return picker->mIsPick;
}

GfGamePlayerPicker::GfGamePlayerPicker() : mSpeedLevel(1), mIsPick(false), mIsModifierReleased(false), mUpDir(mm::Vec3::unitY), mFrontDir(mm::Vec3::unitZ), mRightDir(mm::Vec3::unitX) {}

GfGamePlayerPicker::~GfGamePlayerPicker() {}

bool GfGamePlayerPicker::isEnableChange() const {
  if (mIsPick) {
    return true;
  }

  GfObjProperty *property = GfObjUtil::getProperty(getPlayerHandle());
  return property != nullptr && !property->character->isBattle;
}

void GfGamePlayerPicker::onActive() {
  GfObj *obj = GfObjUtil::getObj(getPlayerHandle());
  if (obj != nullptr) {
    MsgPcResetState message;
    sendMessage(obj, message);
  }

  mIsModifierReleased = false;
}

void GfGamePlayerPicker::onDeactive() {
  GfObj *obj = GfObjUtil::getObj(getPlayerHandle());
  if (obj != nullptr) {
    MsgPcResetState message;
    sendMessage(obj, message);
  }
}

GF_OBJ_HANDLE *GfGamePlayerPicker::getPlayerHandle() const { return GfGamePlayerFormation::get()->players[0].handle; }

} // namespace gf
