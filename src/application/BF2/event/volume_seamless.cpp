#include "event/volume_seamless.h"

#include "event/volume_player.h"
#include "fw/fw_debug.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/singleton.h"

namespace event {

const f32 VolumeSeamless::DEF_VOL = 0.0f;

VolumeSeamless::VolumeSeamless() : unknown08(), m_target(0) {
  unknown10 = 0;
  for (u32 i = 0; i < RESET_VOLUME_COUNT; i++) {
    unknown14[i] = 1.0f;
  }
  unknown48 = DEF_VOL;
}

void VolumeSeamless::clear() {
  unknown08.clear();
  unknown48 = DEF_VOL;
  unknown4c = 0.0f;
  for (u32 i = 0; i < RESET_VOLUME_COUNT; i++) {
    unknown14[i] = 1.0f;
  }
  unknown10 = 0;
}

void VolumeSeamless::update() {
  if (!unknown08.test(FLAG_START) && !unknown08.test(FLAG_END)) {
    return;
  }
  if (unknown4c >= 0.0f) {
    unknown4c -= 1.0f;
  }
  if (unknown08.test(FLAG_END) && unknown4c < 0.0f) {
    unknown08.set(FLAG_END, false);
  }
}

void VolumeSeamless::draw() {
  static bool s_isBlink;

  if (!unknown08.test(FLAG_START) && !unknown08.test(FLAG_END)) {
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
    if (unknown08.test(FLAG_START)) {
      onColor = mm::Col4(1.0f, 0.5f, 0.5f, 1.0f);
    }
    if (unknown08.test(FLAG_END)) {
      onColor = mm::Col4(0.5f, 0.5f, 1.0f, 1.0f);
    }
  }
  if (isActive(TGT_TYPE_BGM) && unknown08.test(FLAG_END)) {
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
  if (isActive(TGT_TYPE_EVTVOI) && unknown08.test(FLAG_END)) {
    fw::debug::drawFont(x, y, onColor, "EVTVOI");
  } else {
    fw::debug::drawFont(x, y, offColor, "EVTVOI");
  }
  x = width - 240;
  if (isActive(TGT_TYPE_EVTSE) && unknown08.test(FLAG_END)) {
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
  unknown08.set(FLAG_ENABLE, isEnable);
  m_target = target;
  unknown48 = volume;
  if (resetVolumes != nullptr) {
    for (u32 i = 0; i < RESET_VOLUME_COUNT; i++) {
      unknown14[i] = (*resetVolumes)[i];
    }
  } else {
    for (u32 i = 0; i < RESET_VOLUME_COUNT; i++) {
      unknown14[i] = 1.0f;
    }
  }
}

void VolumeSeamless::start(f32 frame) {
  if (unknown08.test(FLAG_ENABLE)) {
    if (isActive(TGT_TYPE_VOI)) {
      mm::mtl::Singleton<VolumePlayer>::get().change(2, unknown48, frame);
    }
    if (isActive(TGT_TYPE_BTL)) {
      mm::mtl::Singleton<VolumePlayer>::get().change(4, unknown48, frame);
    }
    if (isActive(TGT_TYPE_FLD)) {
      mm::mtl::Singleton<VolumePlayer>::get().change(5, unknown48, frame);
    }
    if (isActive(TGT_TYPE_GMK)) {
      mm::mtl::Singleton<VolumePlayer>::get().change(6, unknown48, frame);
    }
    if (isActive(TGT_TYPE_ENV)) {
      mm::mtl::Singleton<VolumePlayer>::get().change(7, unknown48, frame);
    }
    if (isActive(TGT_TYPE_WEA)) {
      mm::mtl::Singleton<VolumePlayer>::get().change(8, unknown48, frame);
    }
    if (isActive(TGT_TYPE_CHRSE)) {
      mm::mtl::Singleton<VolumePlayer>::get().change(13, unknown48, frame);
    }
    if (isActive(TGT_TYPE_NOSLOW)) {
      mm::mtl::Singleton<VolumePlayer>::get().change(14, unknown48, frame);
    }
    if (isActive(TGT_TYPE_ENEVOI)) {
      mm::mtl::Singleton<VolumePlayer>::get().change(15, unknown48, frame);
    }
    if (isActive(TGT_TYPE_NAREVOI)) {
      mm::mtl::Singleton<VolumePlayer>::get().change(16, unknown48, frame);
    }
    unknown08.set(FLAG_START);
    unknown08.set(FLAG_END, false);
    this->unknown4c = frame;
  }
}

void VolumeSeamless::end(f32 frame) {
  if (unknown08.test(FLAG_ENABLE)) {
    if (isActive(TGT_TYPE_BGM)) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(1, unknown14[0], frame);
    }
    if (isActive(TGT_TYPE_VOI)) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(2, unknown14[1], frame);
    }
    if (isActive(TGT_TYPE_BTL)) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(4, unknown14[2], frame);
    }
    if (isActive(TGT_TYPE_FLD)) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(5, unknown14[3], frame);
    }
    if (isActive(TGT_TYPE_GMK)) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(6, unknown14[4], frame);
    }
    if (isActive(TGT_TYPE_ENV)) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(7, unknown14[5], frame);
    }
    if (isActive(TGT_TYPE_WEA)) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(8, unknown14[6], frame);
    }
    if (isActive(TGT_TYPE_EVTVOI)) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(11, unknown14[7], frame);
    }
    if (isActive(TGT_TYPE_EVTSE)) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(12, unknown14[8], frame);
    }
    if (isActive(TGT_TYPE_CHRSE)) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(13, unknown14[9], frame);
    }
    if (isActive(TGT_TYPE_NOSLOW)) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(14, unknown14[10], frame);
    }
    if (isActive(TGT_TYPE_ENEVOI)) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(15, unknown14[11], frame);
    }
    if (isActive(TGT_TYPE_NAREVOI)) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(16, unknown14[12], frame);
    }
    unknown08.set(FLAG_START, false);
    unknown08.set(FLAG_END);
    this->unknown4c = frame;
  }
}

void VolumeSeamless::setTarget(TGT_TYPE target) { m_target = target; }

void VolumeSeamless::mask(MASK_TYPE type, bool isMask) {
  if (isMask) {
    unknown10 |= type;
  } else {
    unknown10 &= ~type;
  }
}

} // namespace event
