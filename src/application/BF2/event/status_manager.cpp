#include "event/status_manager.h"

#include <stdarg.h>
#include <stdio.h>

#include "event/chara_obj.h"
#include "event/manager.h"
#include "event/mercenaries_manager.h"
#include "event/object.h"
#include "event/object_chara.h"
#include "event/object_manager.h"
#include "event/quest_manager.h"
#include "event/ui_manager.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/event/gf_game_event.h"
#include "gf/game/gf_game_cond.h"
#include "gf/request/gf_req_scom.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/singleton.h"

namespace event {

u32 StatusManager::getHomuriFlag() const { return gf::GfGameFlag::getLocal(1, gf::FLAG_UNKNOWN_35323); }

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

// Inferred role: result text of the log lines of judge; original name unknown.
static const char *unknown001(bool isOk) { return isOk ? "OK" : "NG"; }

// Erased arguments (ruling of 2026-11-13): the game never sets the this and tag registers (x0, x1) before its calls to log, which is
// defined in this unit and reads neither, so clang drops them. The tag the original passed cannot be checked; nullptr is passed.
// The game checks the singleton guard again for the second getState of the range tests (cases 5 and 31), as written here.
bool StatusManager::judge(EVT_judge type, int id, int value0, int value1, int value2, bool &result) {
  result = false;
  switch (type) {
  case 1:
    result = static_cast<u32>(id) <= gf::GfDataUtil::getScenarioFlag();
    log(nullptr, "%d <= scenario  (%s)", id, unknown001(result));
    return true;
  case 2:
    if (mm::mtl::PtrSingleton<Manager>::get()->isEndFadeOut()) {
      return true;
    }
    if (!mm::mtl::Singleton<QuestManager>::getPtr()->entry(id, &result)) {
      return false;
    }
    log(nullptr, "quest[%d].state = %d  (%s)", id, result, unknown001(result));
    return true;
  case 3:
    result = value0 <= mm::mtl::Singleton<QuestManager>::getPtr()->getState(id);
    log(nullptr, "%d <= quest[%d].state  (%s)", value0, id, unknown001(result));
    return true;
  case 5:
    result = value0 <= mm::mtl::Singleton<QuestManager>::getPtr()->getState(id) && mm::mtl::Singleton<QuestManager>::getPtr()->getState(id) <= value1;
    log(nullptr, "%d <= quest[%d].state <= %d  (%s)", value0, id, value1, unknown001(result));
    return true;
  case 8:
    result = (value1 != 0) == mm::mtl::Singleton<QuestManager>::getPtr()->getComp(id, value0);
    log(nullptr, "quest[%d].comp[%d] == %d  (%s)", id, value0, value1, unknown001(result));
    return true;
  case 11:
    result = value0 <= gf::GfGameFlag::getLocal(8, id + 0x848);
    log(nullptr, "%d <= town8[%d]  (%s)", value0, id, unknown001(result));
    return true;
  case 13:
    result = value0 <= gf::GfGameFlag::getLocal(4, id + 0x1fa);
    log(nullptr, "%d <= town4[%d]  (%s)", value0, id, unknown001(result));
    return true;
  case 15:
    result = gf::GfGameFlag::getLocal(1, id + 0xc327) == value0;
    log(nullptr, "%d == town1[%d]  (%s)", value0, id, unknown001(result));
    return true;
  case 17:
    result = value0 <= gf::GfGameFlag::getLocal(8, id + 0x8ad);
    log(nullptr, "%d <= sys8[%d]  (%s)", value0, id, unknown001(result));
    return true;
  case 19:
    result = value0 <= gf::GfGameFlag::getLocal(4, id + 0x20b);
    log(nullptr, "%d <= sys4[%d]  (%s)", value0, id, unknown001(result));
    return true;
  case 21:
    result = gf::GfGameFlag::getLocal(1, id + 0x89fa) == value0;
    log(nullptr, "%d == sys1[%d]  (%s)", value0, id, unknown001(result));
    return true;
  case 23:
    result = value0 <= gf::GfGameFlag::getLocal(8, id + 0x8af);
    log(nullptr, "%d <= hanyou[%d]  (%s)", value0, id, unknown001(result));
    return true;
  case 25:
    result = gf::GfGameFlag::getLocal(1, id + 0xd651) == 1;
    log(nullptr, "1 == meet[%d]  (%s)", id, unknown001(result));
    return true;
  case 26:
    result = gf::GfGameCond::isGameCond(id);
    log(nullptr, "1 == condition[%d]  (%s)", id, unknown001(result));
    return true;
  case 27:
    if (mm::mtl::PtrSingleton<Manager>::get()->isEndFadeOut()) {
      return true;
    }
    if (!mm::mtl::Singleton<UIManager>::getPtr()->execFieldSkill(id, result)) {
      return false;
    }
    log(nullptr, "skill[%d].play()  (%s)", id, unknown001(result));
    return true;
  case 28:
    if (mm::mtl::PtrSingleton<Manager>::get()->isEndFadeOut()) {
      return true;
    }
    if (!mm::mtl::Singleton<UIManager>::getPtr()->openShopUI(id, result)) {
      return false;
    }
    log(nullptr, "shop[%d].play()  (%s)", id, unknown001(result));
    return true;
  case 29:
    result = value0 <= mm::mtl::Singleton<MercenariesManager>::getPtr()->getState(id);
    log(nullptr, "%d <= merce[%d].state  (%s)", value0, id, unknown001(result));
    return true;
  case 31:
    result = value0 <= mm::mtl::Singleton<MercenariesManager>::getPtr()->getState(id) && mm::mtl::Singleton<MercenariesManager>::getPtr()->getState(id) <= value1;
    log(nullptr, "%d <= merce[%d].state <= %d  (%s)", value0, id, value1, unknown001(result));
    return true;
  default:
    return true;
  }
}

void StatusManager::log(const char *tag, const char *format, ...) {
  char buffer[512];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);
}

const char *StatusManager::math2str(u32 math) const {
  if (math == MATH_EQUAL) {
    return "=";
  }
  if (math == MATH_ADD) {
    return "+=";
  }
  return "";
}

void StatusManager::setGameFlag8(u32 flag, int value, u32 math) const {
  switch (math) {
  case MATH_EQUAL:
    gf::GfGameFlag::setLocal(8, flag, mm::clamp(value, 0, 255));
    break;
  case MATH_ADD:
    gf::GfGameFlag::setLocal(8, flag, mm::clamp(static_cast<int>(gf::GfGameFlag::getLocal(8, flag)) + value, 0, 255));
    break;
  }
}

void StatusManager::setGameFlag4(u32 flag, int value, u32 math) const {
  switch (math) {
  case MATH_EQUAL:
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
  case MATH_EQUAL:
    gf::GfGameFlag::setLocal(2, flag, mm::clamp(value, 0, 3));
    break;
  case MATH_ADD:
    gf::GfGameFlag::setLocal(2, flag, mm::clamp(static_cast<int>(gf::GfGameFlag::getLocal(2, flag)) + value, 0, 3));
    break;
  }
}

void StatusManager::setExtDisp(u32 chara, const char *name, bool isDisp) const {
  ObjectChara *object = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(gf::OBJECT_TYPE_PC, chara);
  if (object == nullptr) {
    object = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(gf::OBJECT_TYPE_BLADE, chara);
  }
  if (object == nullptr) {
    object = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(gf::OBJECT_TYPE_NPC, chara);
  }
  if (object == nullptr) {
    object = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(gf::OBJECT_TYPE_ENEMY, chara);
  }
  if (object != nullptr && object->getType() == OBJTYPE_UNKNOWN_2) {
    object->getCharaObj()->setExtDisp(name, isDisp);
  }
}

void StatusManager::setExtDispWeapon(u32 chara, const char *name, bool isDisp) const {
  ObjectChara *object = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(gf::OBJECT_TYPE_PC, chara);
  if (object == nullptr) {
    object = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(gf::OBJECT_TYPE_BLADE, chara);
  }
  if (object != nullptr && object->getType() == OBJTYPE_UNKNOWN_2) {
    object->getCharaObj()->setExtDispWeapon(name, isDisp);
  }
}

void StatusManager::setExtParam(u32 chara, const char *name, f32 value) const {
  ObjectChara *object = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(gf::OBJECT_TYPE_PC, chara);
  if (object == nullptr) {
    object = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(gf::OBJECT_TYPE_BLADE, chara);
  }
  if (object == nullptr) {
    object = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(gf::OBJECT_TYPE_NPC, chara);
  }
  if (object == nullptr) {
    object = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(gf::OBJECT_TYPE_ENEMY, chara);
  }
  if (object != nullptr && object->getType() == OBJTYPE_UNKNOWN_2) {
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
  case MSG_TYPE_UNKNOWN_4:
    init();
    break;
  case MSG_TYPE_UNKNOWN_12:
    clear();
    break;
  default:
    break;
  }
}

} // namespace event
