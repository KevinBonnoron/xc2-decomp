#include "event/status_manager.h"

#include <stdarg.h>
#include <stdio.h>

#include "event/chara_obj.h"
#include "event/manager.h"
#include "event/object.h"
#include "event/object_chara.h"
#include "event/object_manager.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/event/gf_game_event.h"
#include "gf/request/gf_req_scom.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/singleton.h"

namespace event {

u32 StatusManager::getHomuriFlag() const { return gf::GfGameFlag::getLocal(1, gf::FLAG_BLADE_HOMURI_NAME_HIKARI); }

StatusManager::StatusManager() : unknown18(0) {}

void StatusManager::init() {
  unknown20.clear();
  unknown18 = 0;
  gf::GfGameEvent::setCancelFlag(false);
}

void StatusManager::clear() {
  unknown20.clear();
  unknown18 = 0;
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

void StatusManager::setExtDisp(u32 chara, const char *name, bool isDisp) const {
  ObjectChara *object = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(gf::OBJECT_TYPE_DRIVER, chara);
  if (object == nullptr) {
    object = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(gf::OBJECT_TYPE_BLADE, chara);
  }
  if (object == nullptr) {
    object = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(gf::OBJECT_TYPE_NPC, chara);
  }
  if (object == nullptr) {
    object = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(gf::OBJECT_TYPE_ENEMY, chara);
  }
  if (object != nullptr && object->getType() == OBJTYPE_CHARA) {
    object->getCharaObj()->setExtDisp(name, isDisp);
  }
}

void StatusManager::setExtDispWeapon(u32 chara, const char *name, bool isDisp) const {
  ObjectChara *object = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(gf::OBJECT_TYPE_DRIVER, chara);
  if (object == nullptr) {
    object = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(gf::OBJECT_TYPE_BLADE, chara);
  }
  if (object != nullptr && object->getType() == OBJTYPE_CHARA) {
    object->getCharaObj()->setExtDispWeapon(name, isDisp);
  }
}

void StatusManager::setExtParam(u32 chara, const char *name, f32 value) const {
  ObjectChara *object = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(gf::OBJECT_TYPE_DRIVER, chara);
  if (object == nullptr) {
    object = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(gf::OBJECT_TYPE_BLADE, chara);
  }
  if (object == nullptr) {
    object = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(gf::OBJECT_TYPE_NPC, chara);
  }
  if (object == nullptr) {
    object = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(gf::OBJECT_TYPE_ENEMY, chara);
  }
  if (object != nullptr && object->getType() == OBJTYPE_CHARA) {
    object->getCharaObj()->setExtParam(name, value);
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
