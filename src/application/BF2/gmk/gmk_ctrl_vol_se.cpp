#include "gmk/gmk_ctrl_vol_se.h"

#include <math.h>

#include "framework/sound/sound_manager.h"
#include "fw/fw_transform.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_math.h"

namespace gmk {

GmkCtrlVolSe::GmkCtrlVolSe() : unknown60(0), unknown64(0.0f), unknown68(false) {}

void GmkCtrlVolSe::create(const CreateInfo &info) {
  dispose();
  unknown20 = info;
  unknown70 = info.unknown20;
  createInst();
}

void GmkCtrlVolSe::dispose() {
  disposeInst(true);
  unknown20 = CreateInfo();
}

void GmkCtrlVolSe::disposeInst(bool isFadeOut) {
  if (unknown60 == 0) {
    return;
  }
  if (intoNode() && GmkCtrlVolSeManager::get() != nullptr) {
    GmkCtrlVolSeManager::get()->unknown08.erase(this);
  }
  if (!isFadeOut || fw::SoundManager::get()->isLoop(unknown60)) {
    fw::SoundManager::get()->stopSe(unknown60, isFadeOut ? 1.0f : 0.0f);
  }
  unknown60 = 0;
}

void GmkCtrlVolSe::validateMute() const {
  if (unknown60 == 0) {
    return;
  }
  fw::SoundManager::get()->setVolume(unknown60, unknown68 ? 0.0f : static_cast<f32>(unknown20.unknown18) * 0.01f, 0.0f);
}

void GmkCtrlVolSe::update(f32 deltaTime) {
  if (unknown20.unknown00 == nullptr || unknown20.unknown08 == 0 || unknown60 == 0 || unknown68) {
    return;
  }
  if (gf::GfGameManager::getControlMover() == gf::INVALID_HANDLE) {
    return;
  }
  if (unknown20.unknown30 != gf::INVALID_HANDLE) {
    gf::GfObjAcc acc(unknown20.unknown30);
    if (acc.isValidTransform()) {
      unknown70 = mm::Vec3(acc.getWorldTransformNoSync().unknown00);
    }
  }
  const mm::Vec3 &position = gf::GfObjUtil::getObj(gf::GfGameManager::getControlMover())->getComponent<gf::GfComTransform>()->getPosition();
  f32 x = unknown70.x - position.x;
  f32 y = unknown70.y - position.y;
  f32 z = unknown70.z - position.z;
  unknown64 = sqrtf(x * x + y * y + z * z);
  f32 volume = 1.0f;
  if (unknown20.unknown10 > 0.0f) {
    if (unknown20.unknown10 <= unknown64) {
      volume = static_cast<f32>(unknown20.unknown18) * 0.01f;
    } else if (unknown64 <= unknown20.unknown14) {
      volume = static_cast<f32>(unknown20.unknown19) * 0.01f;
    } else {
      f32 rate = 0.0f;
      if (unknown20.unknown14 < unknown20.unknown10) {
        rate = (unknown20.unknown10 - unknown64) / (unknown20.unknown10 - unknown20.unknown14);
      }
      f32 range = static_cast<f32>(unknown20.unknown19 - unknown20.unknown18) * 0.01f;
      mm::clampRef(range, 0.0f, 1.0f);
      volume = static_cast<f32>(unknown20.unknown18) * 0.01f + rate * range;
    }
    if (gf::GfGameManager::isRoom()) {
      volume *= static_cast<f32>(unknown20.unknown1a) * 0.01f;
    }
  }
  fw::SoundManager::get()->setVolume(unknown60, volume, 0.0f);
}

bool GmkCtrlVolSe::isPlayEnd() const { return !fw::SoundManager::get()->isPlaying(unknown60); }

} // namespace gmk
