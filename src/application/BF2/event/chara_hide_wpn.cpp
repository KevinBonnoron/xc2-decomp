#include "event/chara_hide_wpn.h"

#include "event/chara_obj.h"
#include "event/cmd_variable.h"
#include "event/frame_manager.h"
#include "event/object_chara.h"
#include "event/object_manager.h"
#include "mm_mtl/singleton.h"

namespace event {

ICmd::RESULT CharaHideWpn::update(const Param &param) {
  if (!unknown08.test(FLAG_UNKNOWN_0)) {
    return RESULT_UNKNOWN_1;
  }
  CharaObj *chara = static_cast<CharaObj *>(param.val(0).getUserdata());
  f32 delta = chara->getFrameInfo().unknown0c;
  if (param.getFrame() <= 0) {
    ObjectChara *npc = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(CHARA_TYPE_UNKNOWN_3, unknown0c);
    if (npc != nullptr) {
      npc->getCharaObj()->setHideWeapon(WPNHIDEID_UNKNOWN_2, true, unknown08.test(FLAG_UNKNOWN_1));
    }
    unknown10 = param.val(1).getF32();
    unknown08.set(FLAG_UNKNOWN_2);
    unknown08.set(FLAG_UNKNOWN_3, unknown10 <= 0.0f);
  }
  if (unknown08.test(FLAG_UNKNOWN_3)) {
    return RESULT_UNKNOWN_2;
  }
  unknown10 -= delta;
  if (!(unknown10 < 0.0f)) {
    return RESULT_UNKNOWN_2;
  }
  ObjectChara *npc = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(CHARA_TYPE_UNKNOWN_3, unknown0c);
  if (npc != nullptr) {
    npc->getCharaObj()->setHideWeapon(WPNHIDEID_UNKNOWN_2, false, unknown08.test(FLAG_UNKNOWN_1));
  }
  unknown08.set(FLAG_UNKNOWN_2, false);
  return RESULT_UNKNOWN_1;
}

void CharaHideWpn::term() {
  if (unknown08.test(FLAG_UNKNOWN_2)) {
    ObjectChara *npc = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(CHARA_TYPE_UNKNOWN_3, unknown0c);
    if (npc != nullptr) {
      npc->getCharaObj()->setHideWeapon(WPNHIDEID_UNKNOWN_2, false, unknown08.test(FLAG_UNKNOWN_1));
    }
    unknown08.set(FLAG_UNKNOWN_2, false);
  }
}

} // namespace event
