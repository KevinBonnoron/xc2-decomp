#include "event/volume_manager.h"

#include "event/volume_player.h"
#include "fw/fw_debug.h"
#include "gf/game/event/gf_game_event.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/singleton.h"

namespace fw {
enum SoundCategory : int;
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
  if ((dispFlags & DISP_FLAG_DISP) == 0) {
    return;
  }
  s32 width = (dispFlags & DISP_FLAG_DETAIL) != 0 ? 820 : 380;
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
  if ((dispFlags & DISP_FLAG_DETAIL) != 0) {
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
  if ((dispFlags & DISP_FLAG_DETAIL) != 0) {
    fw::debug::drawSquare2D(mm::Rect<s32>(posX + 10, barY, 6, static_cast<s32>(gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(11)) * -30.0f)), mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
    fw::debug::drawFont(posX + 20, height - 105, "EVTVO");
    fw::debug::drawFont(posX, barY, "%.2f", gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(11)));
    posX += 60;
  }
  fw::debug::drawSquare2D(mm::Rect<s32>(posX + 10, barY, 6, static_cast<s32>(gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(12)) * -30.0f)), mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
  fw::debug::drawFont(posX + 20, height - 105, "EVTSE");
  fw::debug::drawFont(posX, barY, "%.2f", gf::GfGameEvent::getCategoryVolume(static_cast<fw::SoundCategory>(12)));
  if ((dispFlags & DISP_FLAG_DETAIL) != 0) {
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

void VolumeManager::setSeamlessVolume(bool isEnable, f32 volume, u32 target, const mm::mtl::FixedArray<f32, VolumeSeamless::RESET_VOLUME_COUNT> *resetVolumes) {
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

void VolumeManager::setDisp(bool isDisp) { setDispFlag(DISP_FLAG_DISP, isDisp); }

bool VolumeManager::isDisp() const { return (unknown14 & DISP_FLAG_DISP) != 0; }

void VolumeManager::setDispDetail(bool isDisp) { setDispFlag(DISP_FLAG_DETAIL, isDisp); }

bool VolumeManager::isDispDetail() const { return (unknown14 & DISP_FLAG_DETAIL) != 0; }

void VolumeManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT_BEGIN:
    init();
    break;
  case MSG_TYPE_UPDATE_SEQUENCE:
    clear();
    break;
  case MSG_TYPE_UPDATE:
    update();
    break;
  case MSG_TYPE_RENDER_POST:
    render();
    break;
  default:
    break;
  }
}

} // namespace event
