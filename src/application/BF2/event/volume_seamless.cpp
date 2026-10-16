#include "event/volume_seamless.h"

#include "event/volume_player.h"
#include "fw/fw_debug.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/singleton.h"

namespace event {

const f32 VolumeSeamless::DEF_VOL = 0.0f;

VolumeSeamless::VolumeSeamless() : flags(), mTarget(0) {
  mMask = 0;
  for (u32 i = 0; i < RESET_VOLUME_COUNT; i++) {
    mResetVolumes[i] = 1.0f;
  }
  mVolume = DEF_VOL;
}

void VolumeSeamless::clear() {
  flags.clear();
  mVolume = DEF_VOL;
  frame = 0.0f;
  for (u32 i = 0; i < RESET_VOLUME_COUNT; i++) {
    mResetVolumes[i] = 1.0f;
  }
  mMask = 0;
}

void VolumeSeamless::update() {
  if (!flags.test(FLAG_START) && !flags.test(FLAG_END)) {
    return;
  }
  if (frame >= 0.0f) {
    frame -= 1.0f;
  }
  if (flags.test(FLAG_END) && frame < 0.0f) {
    flags.set(FLAG_END, false);
  }
}

void VolumeSeamless::draw() {
  static bool s_isBlink;

  if (!flags.test(FLAG_START) && !flags.test(FLAG_END)) {
    return;
  }
  s32 width = ml::DevGraph::getRootWidth();
  s32 x = width - 505;
  s32 height = ml::DevGraph::getRootHeight();
  s32 y = height - 175;
  fw::debug::drawCompareZ(false);
  fw::debug::drawSquare2D(mm::Rect<s32>(x, y, 540, 45), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<s32>(x, y, 540, 45), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(width - 500, height - 170, mm::Col4::white, "CATE SEAM");
  x = width - 495;
  y = height - 153;
  mm::Col4 onColor(1.0f, 1.0f, 1.0f, 1.0f);
  mm::Col4 offColor(0.5f, 0.5f, 0.5f, 1.0f);
  if (s_isBlink) {
    if (flags.test(FLAG_START)) {
      onColor = mm::Col4(1.0f, 0.5f, 0.5f, 1.0f);
    }
    if (flags.test(FLAG_END)) {
      onColor = mm::Col4(0.5f, 0.5f, 1.0f, 1.0f);
    }
  }
  if (isActive(TGT_TYPE_BGM) && flags.test(FLAG_END)) {
    fw::debug::drawFont(x, y, onColor, "BGM");
  } else {
    fw::debug::drawFont(x, y, offColor, "BGM");
  }
  x = width - 465;
  if (isActive(TGT_TYPE_VOI)) {
    fw::debug::drawFont(x, y, onColor, "VOI");
  } else {
    fw::debug::drawFont(x, y, offColor, "VOI");
  }
  x = width - 435;
  if (isActive(TGT_TYPE_BTL)) {
    fw::debug::drawFont(x, y, onColor, "BTL");
  } else {
    fw::debug::drawFont(x, y, offColor, "BTL");
  }
  x = width - 405;
  if (isActive(TGT_TYPE_FLD)) {
    fw::debug::drawFont(x, y, onColor, "FLD");
  } else {
    fw::debug::drawFont(x, y, offColor, "FLD");
  }
  x = width - 375;
  if (isActive(TGT_TYPE_GMK)) {
    fw::debug::drawFont(x, y, onColor, "GMK");
  } else {
    fw::debug::drawFont(x, y, offColor, "GMK");
  }
  x = width - 345;
  if (isActive(TGT_TYPE_ENV)) {
    fw::debug::drawFont(x, y, onColor, "ENV");
  } else {
    fw::debug::drawFont(x, y, offColor, "ENV");
  }
  x = width - 315;
  if (isActive(TGT_TYPE_WEA)) {
    fw::debug::drawFont(x, y, onColor, "WEA");
  } else {
    fw::debug::drawFont(x, y, offColor, "WEA");
  }
  x = width - 285;
  if (isActive(TGT_TYPE_EVTVOI) && flags.test(FLAG_END)) {
    fw::debug::drawFont(x, y, onColor, "EVTVOI");
  } else {
    fw::debug::drawFont(x, y, offColor, "EVTVOI");
  }
  x = width - 240;
  if (isActive(TGT_TYPE_EVTSE) && flags.test(FLAG_END)) {
    fw::debug::drawFont(x, y, onColor, "EVTSE");
  } else {
    fw::debug::drawFont(x, y, offColor, "EVTSE");
  }
  x = width - 195;
  if (isActive(TGT_TYPE_CHRSE)) {
    fw::debug::drawFont(x, y, onColor, "CHRSE");
  } else {
    fw::debug::drawFont(x, y, offColor, "CHRSE");
  }
  x = width - 150;
  if (isActive(TGT_TYPE_NOSLOW)) {
    fw::debug::drawFont(x, y, onColor, "(NOSLOW)");
  } else {
    fw::debug::drawFont(x, y, offColor, "(NOSLOW)");
  }
  x = width - 80;
  if (isActive(TGT_TYPE_ENEVOI)) {
    fw::debug::drawFont(x, y, onColor, "ENEVOI");
  } else {
    fw::debug::drawFont(x, y, offColor, "ENEVOI");
  }
  x = width - 30;
  if (isActive(TGT_TYPE_NAREVOI)) {
    fw::debug::drawFont(x, y, onColor, "NAREVOI");
  } else {
    fw::debug::drawFont(x, y, offColor, "NAREVOI");
  }
  s_isBlink ^= true;
}

void VolumeSeamless::set(bool isEnable, f32 volume, u32 target, const mm::mtl::FixedArray<f32, RESET_VOLUME_COUNT> *resetVolumes) {
  flags.set(FLAG_ENABLE, isEnable);
  mTarget = target;
  mVolume = volume;
  if (resetVolumes != nullptr) {
    for (u32 i = 0; i < RESET_VOLUME_COUNT; i++) {
      mResetVolumes[i] = (*resetVolumes)[i];
    }
  } else {
    for (u32 i = 0; i < RESET_VOLUME_COUNT; i++) {
      mResetVolumes[i] = 1.0f;
    }
  }
}

void VolumeSeamless::start(f32 frame) {
  if (flags.test(FLAG_ENABLE)) {
    if (isActive(TGT_TYPE_VOI)) {
      mm::mtl::Singleton<VolumePlayer>::get().change(2, mVolume, frame);
    }
    if (isActive(TGT_TYPE_BTL)) {
      mm::mtl::Singleton<VolumePlayer>::get().change(4, mVolume, frame);
    }
    if (isActive(TGT_TYPE_FLD)) {
      mm::mtl::Singleton<VolumePlayer>::get().change(5, mVolume, frame);
    }
    if (isActive(TGT_TYPE_GMK)) {
      mm::mtl::Singleton<VolumePlayer>::get().change(6, mVolume, frame);
    }
    if (isActive(TGT_TYPE_ENV)) {
      mm::mtl::Singleton<VolumePlayer>::get().change(7, mVolume, frame);
    }
    if (isActive(TGT_TYPE_WEA)) {
      mm::mtl::Singleton<VolumePlayer>::get().change(8, mVolume, frame);
    }
    if (isActive(TGT_TYPE_CHRSE)) {
      mm::mtl::Singleton<VolumePlayer>::get().change(13, mVolume, frame);
    }
    if (isActive(TGT_TYPE_NOSLOW)) {
      mm::mtl::Singleton<VolumePlayer>::get().change(14, mVolume, frame);
    }
    if (isActive(TGT_TYPE_ENEVOI)) {
      mm::mtl::Singleton<VolumePlayer>::get().change(15, mVolume, frame);
    }
    if (isActive(TGT_TYPE_NAREVOI)) {
      mm::mtl::Singleton<VolumePlayer>::get().change(16, mVolume, frame);
    }
    flags.set(FLAG_START);
    flags.set(FLAG_END, false);
    this->frame = frame;
  }
}

void VolumeSeamless::end(f32 frame) {
  if (flags.test(FLAG_ENABLE)) {
    if (isActive(TGT_TYPE_BGM)) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(1, mResetVolumes[0], frame);
    }
    if (isActive(TGT_TYPE_VOI)) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(2, mResetVolumes[1], frame);
    }
    if (isActive(TGT_TYPE_BTL)) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(4, mResetVolumes[2], frame);
    }
    if (isActive(TGT_TYPE_FLD)) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(5, mResetVolumes[3], frame);
    }
    if (isActive(TGT_TYPE_GMK)) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(6, mResetVolumes[4], frame);
    }
    if (isActive(TGT_TYPE_ENV)) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(7, mResetVolumes[5], frame);
    }
    if (isActive(TGT_TYPE_WEA)) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(8, mResetVolumes[6], frame);
    }
    if (isActive(TGT_TYPE_EVTVOI)) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(11, mResetVolumes[7], frame);
    }
    if (isActive(TGT_TYPE_EVTSE)) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(12, mResetVolumes[8], frame);
    }
    if (isActive(TGT_TYPE_CHRSE)) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(13, mResetVolumes[9], frame);
    }
    if (isActive(TGT_TYPE_NOSLOW)) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(14, mResetVolumes[10], frame);
    }
    if (isActive(TGT_TYPE_ENEVOI)) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(15, mResetVolumes[11], frame);
    }
    if (isActive(TGT_TYPE_NAREVOI)) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(16, mResetVolumes[12], frame);
    }
    flags.set(FLAG_START, false);
    flags.set(FLAG_END);
    this->frame = frame;
  }
}

void VolumeSeamless::setTarget(TGT_TYPE target) { mTarget = target; }

void VolumeSeamless::mask(MASK_TYPE type, bool isMask) {
  if (isMask) {
    mMask |= type;
  } else {
    mMask &= ~type;
  }
}

} // namespace event
