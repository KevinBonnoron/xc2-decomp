#include "event/volume_manager.h"

#include "event/skip_manager.h"
#include "event/volume_player.h"
#include "fw/fw_debug.h"
#include "gf/game/event/gf_game_event.h"
#include "gf/sound/gf_sound.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/singleton.h"

namespace fw {
enum SoundCategory : int;
class SoundManager;
} // namespace fw

namespace event {

VolumeManager::VolumeManager() : unknown10(0), unknown14(0) {}

void VolumeManager::clear() {
  for (u32 i = 0; i < CATE_COUNT; i++) {
    unknown18[i] = 1.0f;
  }
  for (u32 i = 0; i < CATE_COUNT; i++) {
    resetCategoryVolume(static_cast<CATE>(i), 30.0f);
  }
  unknown50.clear();
  unknowna0.clear();
  mm::mtl::Singleton<VolumePlayer>::get().clear();
}

void VolumeManager::setResetCategoryVolume(const mm::mtl::FixedArray<f32, CATE_COUNT> *volumes) {
  if (volumes != nullptr) {
    for (u32 i = 0; i < CATE_COUNT; i++) {
      unknown18[i] = (*volumes)[i];
    }
  } else {
    for (u32 i = 0; i < CATE_COUNT; i++) {
      unknown18[i] = 1.0f;
    }
  }
}

void VolumeManager::resetCategoryVolume(CATE cate, f32 frame) {
  if (mm::mtl::PtrSingleton<fw::SoundManager>::get() == nullptr) {
    return;
  }
  f32 playFrame = mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() ? 0.0f : frame;
  switch (cate) {
  case CATE_UNKNOWN_0:
    if (!unknowna0.isStart()) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(gf::CATEGORY_BGM, unknown18[0], playFrame);
    }
    unknown50.mask(VolumeSeamless::MASK_TYPE_UNKNOWN_0, false);
    unknowna0.setResetVolume(VolumeSkip::TYPE_UNKNOWN_0, unknown18[0]);
    break;
  case CATE_UNKNOWN_1:
    if (!unknowna0.isStart()) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(gf::CATEGORY_VOICE, unknown18[1], playFrame);
    }
    unknown50.mask(VolumeSeamless::MASK_TYPE_UNKNOWN_1, false);
    unknowna0.setResetVolume(VolumeSkip::TYPE_UNKNOWN_1, unknown18[1]);
    break;
  case CATE_UNKNOWN_2:
    if (!unknowna0.isStart()) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(gf::CATEGORY_BATTLE, unknown18[2], playFrame);
    }
    unknown50.mask(VolumeSeamless::MASK_TYPE_UNKNOWN_3, false);
    unknowna0.setResetVolume(VolumeSkip::TYPE_UNKNOWN_2, unknown18[2]);
    break;
  case CATE_UNKNOWN_3:
    if (!unknowna0.isStart()) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(gf::CATEGORY_FIELD, unknown18[3], playFrame);
    }
    unknown50.mask(VolumeSeamless::MASK_TYPE_UNKNOWN_4, false);
    unknowna0.setResetVolume(VolumeSkip::TYPE_UNKNOWN_3, unknown18[3]);
    break;
  case CATE_UNKNOWN_4:
    if (!unknowna0.isStart()) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(gf::CATEGORY_GIMMICK, unknown18[4], playFrame);
    }
    unknown50.mask(VolumeSeamless::MASK_TYPE_UNKNOWN_5, false);
    unknowna0.setResetVolume(VolumeSkip::TYPE_UNKNOWN_4, unknown18[4]);
    break;
  case CATE_UNKNOWN_5:
    if (!unknowna0.isStart()) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(gf::CATEGORY_ENV, unknown18[5], playFrame);
    }
    unknown50.mask(VolumeSeamless::MASK_TYPE_UNKNOWN_6, false);
    unknowna0.setResetVolume(VolumeSkip::TYPE_UNKNOWN_5, unknown18[5]);
    break;
  case CATE_UNKNOWN_6:
    if (!unknowna0.isStart()) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(gf::CATEGORY_WEATHER, unknown18[6], playFrame);
    }
    unknown50.mask(VolumeSeamless::MASK_TYPE_UNKNOWN_7, false);
    unknowna0.setResetVolume(VolumeSkip::TYPE_UNKNOWN_6, unknown18[6]);
    break;
  case CATE_UNKNOWN_7:
    if (!unknowna0.isStart()) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(gf::CATEGORY_EVT_CS, unknown18[7], playFrame);
    }
    unknowna0.setResetVolume(VolumeSkip::TYPE_UNKNOWN_7, unknown18[7]);
    break;
  case CATE_UNKNOWN_8:
    if (!unknowna0.isStart()) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(gf::CATEGORY_EVT_VOICE, unknown18[8], playFrame);
    }
    unknown50.mask(VolumeSeamless::MASK_TYPE_UNKNOWN_9, false);
    unknowna0.setResetVolume(VolumeSkip::TYPE_UNKNOWN_8, unknown18[8]);
    break;
  case CATE_UNKNOWN_9:
    if (!unknowna0.isStart()) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(gf::CATEGORY_EVT_SE, unknown18[9], playFrame);
    }
    unknown50.mask(VolumeSeamless::MASK_TYPE_UNKNOWN_10, false);
    unknowna0.setResetVolume(VolumeSkip::TYPE_UNKNOWN_9, unknown18[9]);
    break;
  case CATE_UNKNOWN_10:
    if (!unknowna0.isStart()) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(gf::CATEGORY_CH_SE, unknown18[10], playFrame);
    }
    unknown50.mask(VolumeSeamless::MASK_TYPE_UNKNOWN_11, false);
    unknowna0.setResetVolume(VolumeSkip::TYPE_UNKNOWN_10, unknown18[10]);
    break;
  case CATE_UNKNOWN_11:
    if (!unknowna0.isStart()) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(gf::CATEGORY_CH_SE_NS, unknown18[11], playFrame);
    }
    unknown50.mask(VolumeSeamless::MASK_TYPE_UNKNOWN_12, false);
    unknowna0.setResetVolume(VolumeSkip::TYPE_UNKNOWN_11, unknown18[11]);
    break;
  case CATE_UNKNOWN_12:
    if (!unknowna0.isStart()) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(gf::CATEGORY_ENE_VO, unknown18[12], playFrame);
    }
    unknown50.mask(VolumeSeamless::MASK_TYPE_UNKNOWN_13, false);
    unknowna0.setResetVolume(VolumeSkip::TYPE_UNKNOWN_12, unknown18[12]);
    break;
  case CATE_UNKNOWN_13:
    if (!unknowna0.isStart()) {
      mm::mtl::Singleton<VolumePlayer>::get().reset(gf::CATEGORY_NAREVO, unknown18[13], playFrame);
    }
    unknown50.mask(VolumeSeamless::MASK_TYPE_UNKNOWN_14, false);
    unknowna0.setResetVolume(VolumeSkip::TYPE_UNKNOWN_13, unknown18[13]);
    break;
  }
}

void VolumeManager::init() {
  for (u32 i = 0; i < CATE_COUNT; i++) {
    unknown18[i] = 1.0f;
  }
  unknown50.clear();
  unknowna0.clear();
  mm::mtl::Singleton<VolumePlayer>::get().clear();
}

void VolumeManager::update() {
  unknown50.update();
  mm::mtl::Singleton<VolumePlayer>::get().update();
}

void VolumeManager::render() {
  u32 dispFlags = this->unknown14;
  if ((dispFlags & DISP_FLAG_UNKNOWN_0) == 0) {
    return;
  }
  s32 width = (dispFlags & DISP_FLAG_UNKNOWN_1) != 0 ? 820 : 380;
  s32 x = ml::DevGraph::getRootWidth() - width;
  s32 left = x - 10;
  s32 height = ml::DevGraph::getRootHeight();
  s32 top = height - 125;
  fw::debug::drawCompareZ(false);
  fw::debug::drawSquare2D(mm::Rect<s32>(left, top, width, 60), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<s32>(left, top, width, 60), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(x - 5, height - 120, mm::Col4::white, "CATE");
  s32 posX = x + 25;
  s32 barY = height - 85;
  fw::debug::drawSquare2D(mm::Rect<s32>(posX + 10, barY, 6, static_cast<s32>(gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(1)) * -30.0f)), mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
  fw::debug::drawFont(posX + 20, height - 115, "BGM");
  fw::debug::drawFont(posX + 20, height - 100, "EVTBGM");
  fw::debug::drawFont(posX, barY, "%.2f", gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(1)));
  posX += 60;
  if ((dispFlags & DISP_FLAG_UNKNOWN_1) != 0) {
    fw::debug::drawSquare2D(mm::Rect<s32>(posX + 10, barY, 6, static_cast<s32>(gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(2)) * -30.0f)), mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
    fw::debug::drawFont(posX + 20, height - 105, "VOI");
    fw::debug::drawFont(posX, barY, "%.2f", gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(2)));
    posX += 40;
    fw::debug::drawSquare2D(mm::Rect<s32>(posX + 10, barY, 6, static_cast<s32>(gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(3)) * -30.0f)), mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
    fw::debug::drawFont(posX + 20, height - 105, "SYS");
    fw::debug::drawFont(posX, barY, "%.2f", gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(3)));
    posX += 40;
    fw::debug::drawSquare2D(mm::Rect<s32>(posX + 10, barY, 6, static_cast<s32>(gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(4)) * -30.0f)), mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
    fw::debug::drawFont(posX + 20, height - 105, "BTL");
    fw::debug::drawFont(posX, barY, "%.2f", gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(4)));
    posX += 40;
  }
  fw::debug::drawSquare2D(mm::Rect<s32>(posX + 10, barY, 6, static_cast<s32>(gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(5)) * -30.0f)), mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
  fw::debug::drawFont(posX + 20, height - 105, "FLD");
  fw::debug::drawFont(posX, barY, "%.2f", gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(5)));
  posX += 40;
  fw::debug::drawSquare2D(mm::Rect<s32>(posX + 10, barY, 6, static_cast<s32>(gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(6)) * -30.0f)), mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
  fw::debug::drawFont(posX + 20, height - 105, "GMK");
  fw::debug::drawFont(posX, barY, "%.2f", gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(6)));
  posX += 40;
  fw::debug::drawSquare2D(mm::Rect<s32>(posX + 10, barY, 6, static_cast<s32>(gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(7)) * -30.0f)), mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
  fw::debug::drawFont(posX + 20, height - 105, "ENV");
  fw::debug::drawFont(posX, barY, "%.2f", gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(7)));
  posX += 40;
  fw::debug::drawSquare2D(mm::Rect<s32>(posX + 10, barY, 6, static_cast<s32>(gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(8)) * -30.0f)), mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
  fw::debug::drawFont(posX + 20, height - 105, "WEA");
  fw::debug::drawFont(posX, barY, "%.2f", gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(8)));
  posX += 40;
  fw::debug::drawSquare2D(mm::Rect<s32>(posX + 10, barY, 6, static_cast<s32>(gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(9)) * -30.0f)), mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
  fw::debug::drawFont(posX + 20, height - 105, "EVTCS");
  fw::debug::drawFont(posX, barY, "%.2f", gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(9)));
  posX += 60;
  if ((dispFlags & DISP_FLAG_UNKNOWN_1) != 0) {
    fw::debug::drawSquare2D(mm::Rect<s32>(posX + 10, barY, 6, static_cast<s32>(gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(11)) * -30.0f)), mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
    fw::debug::drawFont(posX + 20, height - 105, "EVTVO");
    fw::debug::drawFont(posX, barY, "%.2f", gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(11)));
    posX += 60;
  }
  fw::debug::drawSquare2D(mm::Rect<s32>(posX + 10, barY, 6, static_cast<s32>(gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(12)) * -30.0f)), mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
  fw::debug::drawFont(posX + 20, height - 105, "EVTSE");
  fw::debug::drawFont(posX, barY, "%.2f", gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(12)));
  if ((dispFlags & DISP_FLAG_UNKNOWN_1) != 0) {
    posX += 60;
    fw::debug::drawSquare2D(mm::Rect<s32>(posX + 10, barY, 6, static_cast<s32>(gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(13)) * -30.0f)), mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
    fw::debug::drawFont(posX + 20, height - 105, "CHRSE");
    fw::debug::drawFont(posX, barY, "%.2f", gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(13)));
    posX += 60;
    fw::debug::drawSquare2D(mm::Rect<s32>(posX + 10, barY, 6, static_cast<s32>(gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(14)) * -30.0f)), mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
    fw::debug::drawFont(posX + 20, height - 105, "(NOSLOW)");
    fw::debug::drawFont(posX, barY, "%.2f", gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(14)));
    posX += 80;
    fw::debug::drawSquare2D(mm::Rect<s32>(posX + 10, barY, 6, static_cast<s32>(gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(15)) * -30.0f)), mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
    fw::debug::drawFont(posX + 20, height - 105, "ENEVO");
    fw::debug::drawFont(posX, barY, "%.2f", gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(15)));
    posX += 60;
    fw::debug::drawSquare2D(mm::Rect<s32>(posX + 10, barY, 6, static_cast<s32>(gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(16)) * -30.0f)), mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
    fw::debug::drawFont(posX + 20, height - 105, "NAREVO");
    fw::debug::drawFont(posX, barY, "%.2f", gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(16)));
  }
  unknown50.draw();
}

void VolumeManager::changeCategoryVolume(CATE cate, f32 volume, f32 frame) {
  if (mm::mtl::PtrSingleton<fw::SoundManager>::get() == nullptr) {
    return;
  }
  f32 playFrame = mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() ? 0.0f : frame;
  switch (cate) {
  case CATE_UNKNOWN_0:
    if (!unknowna0.isStart()) {
      mm::mtl::Singleton<VolumePlayer>::get().change(gf::CATEGORY_BGM, volume, playFrame);
    }
    unknown50.mask(VolumeSeamless::MASK_TYPE_UNKNOWN_0, true);
    unknowna0.setResetVolume(VolumeSkip::TYPE_UNKNOWN_0, volume);
    break;
  case CATE_UNKNOWN_3:
    if (!unknowna0.isStart()) {
      mm::mtl::Singleton<VolumePlayer>::get().change(gf::CATEGORY_FIELD, volume, playFrame);
    }
    unknown50.mask(VolumeSeamless::MASK_TYPE_UNKNOWN_4, true);
    unknowna0.setResetVolume(VolumeSkip::TYPE_UNKNOWN_3, volume);
    break;
  case CATE_UNKNOWN_4:
    if (!unknowna0.isStart()) {
      mm::mtl::Singleton<VolumePlayer>::get().change(gf::CATEGORY_GIMMICK, volume, playFrame);
    }
    unknown50.mask(VolumeSeamless::MASK_TYPE_UNKNOWN_5, true);
    unknowna0.setResetVolume(VolumeSkip::TYPE_UNKNOWN_4, volume);
    break;
  case CATE_UNKNOWN_5:
    if (!unknowna0.isStart()) {
      mm::mtl::Singleton<VolumePlayer>::get().change(gf::CATEGORY_ENV, volume, playFrame);
    }
    unknown50.mask(VolumeSeamless::MASK_TYPE_UNKNOWN_6, true);
    unknowna0.setResetVolume(VolumeSkip::TYPE_UNKNOWN_5, volume);
    break;
  case CATE_UNKNOWN_6:
    if (!unknowna0.isStart()) {
      mm::mtl::Singleton<VolumePlayer>::get().change(gf::CATEGORY_WEATHER, volume, playFrame);
    }
    unknown50.mask(VolumeSeamless::MASK_TYPE_UNKNOWN_7, true);
    unknowna0.setResetVolume(VolumeSkip::TYPE_UNKNOWN_6, volume);
    break;
  case CATE_UNKNOWN_7:
    if (!unknowna0.isStart()) {
      mm::mtl::Singleton<VolumePlayer>::get().change(gf::CATEGORY_EVT_CS, volume, playFrame);
    }
    unknowna0.setResetVolume(VolumeSkip::TYPE_UNKNOWN_7, volume);
    break;
  case CATE_UNKNOWN_8:
    if (!unknowna0.isStart()) {
      mm::mtl::Singleton<VolumePlayer>::get().change(gf::CATEGORY_EVT_VOICE, volume, playFrame);
    }
    unknown50.mask(VolumeSeamless::MASK_TYPE_UNKNOWN_9, true);
    unknowna0.setResetVolume(VolumeSkip::TYPE_UNKNOWN_8, volume);
    break;
  case CATE_UNKNOWN_9:
    if (!unknowna0.isStart()) {
      mm::mtl::Singleton<VolumePlayer>::get().change(gf::CATEGORY_EVT_SE, volume, playFrame);
    }
    unknown50.mask(VolumeSeamless::MASK_TYPE_UNKNOWN_10, true);
    unknowna0.setResetVolume(VolumeSkip::TYPE_UNKNOWN_9, volume);
    break;
  }
}

void VolumeManager::setSeamlessVolume(bool isEnable, f32 volume, u32 target, const mm::mtl::FixedArray<f32, VolumeSeamless::RESET_VOLUME_UNKNOWN_13> *resetVolumes) {
  unknown50.set(isEnable, volume, target, resetVolumes);
}

void VolumeManager::startSeamlessVolume(f32 frame) {
  if (!unknowna0.isStart()) {
    unknown50.start(frame);
  }
}

void VolumeManager::endSeamlessVolume(f32 frame) {
  if (!unknowna0.isStart()) {
    unknown50.end(frame);
  }
}

void VolumeManager::maskSeamlessVolume(VolumeSeamless::MASK_TYPE type, bool isMask) { unknown50.mask(type, isMask); }

void VolumeManager::setSkipVolume(bool isEnable, f32 volume, f32 inFrame, f32 outFrame, const mm::mtl::FixedArray<f32, CATE_COUNT> *resetVolumes) {
  unknowna0.set(isEnable, volume, inFrame, outFrame, resetVolumes);
}

void VolumeManager::startSkipVolume() { unknowna0.start(); }

void VolumeManager::endSkipVolume() { unknowna0.end(); }

void VolumeManager::setDisp(bool isDisp) { setDispFlag(DISP_FLAG_UNKNOWN_0, isDisp); }

bool VolumeManager::isDisp() const { return (unknown14 & DISP_FLAG_UNKNOWN_0) != 0; }

void VolumeManager::setDispDetail(bool isDisp) { setDispFlag(DISP_FLAG_UNKNOWN_1, isDisp); }

bool VolumeManager::isDispDetail() const { return (unknown14 & DISP_FLAG_UNKNOWN_1) != 0; }

void VolumeManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_UNKNOWN_1:
    init();
    break;
  case MSG_TYPE_UNKNOWN_2:
    clear();
    break;
  case MSG_TYPE_UNKNOWN_14:
    update();
    break;
  case MSG_TYPE_UNKNOWN_17:
    render();
    break;
  default:
    break;
  }
}

} // namespace event
