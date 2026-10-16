#include "event/status_manager.h"

#include <stdarg.h>
#include <stdio.h>

#include "event/manager.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_game_flag.h"
#include "gf/game/event/gf_game_event.h"
#include "gf/request/gf_req_scom.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/singleton.h"

namespace event {

StatusManager::StatusManager() : flags(0) {}

void StatusManager::init() {
  mChanges.clear();
  flags = 0;
  gf::GfGameEvent::setCancelFlag(false);
}

void StatusManager::clear() {
  mChanges.clear();
  flags = 0;
}

void StatusManager::log(const char *tag, const char *format, ...) {
  char buffer[512];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);
}

const char *StatusManager::math2str(u32 math) const {
  if (math == MATH_SET) {
    return "=";
  }
  if (math == MATH_ADD) {
    return "+=";
  }
  return "";
}

void StatusManager::setGameFlag8(u32 flag, int value, u32 math) const {
  switch (math) {
  case MATH_SET:
    gf::GfGameFlag::setLocal(8, flag, mm::clamp(value, 0, 255));
    break;
  case MATH_ADD:
    gf::GfGameFlag::setLocal(8, flag, mm::clamp(static_cast<int>(gf::GfGameFlag::getLocal(8, flag)) + value, 0, 255));
    break;
  }
}

void StatusManager::setGameFlag4(u32 flag, int value, u32 math) const {
  switch (math) {
  case MATH_SET:
    gf::GfGameFlag::setLocal(4, flag, mm::clamp(value, 0, 15));
    break;
  case MATH_ADD:
    gf::GfGameFlag::setLocal(4, flag, mm::clamp(static_cast<int>(gf::GfGameFlag::getLocal(4, flag)) + value, 0, 15));
    break;
  }
}

void StatusManager::setGameFlag1(u32 flag, int value) const { gf::GfGameFlag::setLocal(1, flag, mm::clamp(value, 0, 1)); }

void StatusManager::setGameFlag2(u32 flag, int value, u32 math) const {
  switch (math) {
  case MATH_SET:
    gf::GfGameFlag::setLocal(2, flag, mm::clamp(value, 0, 3));
    break;
  case MATH_ADD:
    gf::GfGameFlag::setLocal(2, flag, mm::clamp(static_cast<int>(gf::GfGameFlag::getLocal(2, flag)) + value, 0, 3));
    break;
  }
}

void StatusManager::addMoney(int money) const { gf::SCOM_ADD_MONEY::create(money); }

void StatusManager::addTrustPoint(u32 blade, int point) const { gf::SCOM_ADD_TRUST::create(blade, point); }

u32 StatusManager::getDriverByBladeId(u32 blade) const { return gf::GfDataBlade::getCreator(blade); }

void StatusManager::setHomuriFlag(int flag) {
  if (!mm::mtl::PtrSingleton<Manager>::get()->isEndFadeOut()) {
    gf::GfDataBlade::setHomuriNameHikari(flag != 0);
  }
}

void StatusManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT:
    init();
    break;
  case MSG_TYPE_CLEAR:
    clear();
    break;
  default:
    break;
  }
}

} // namespace event
