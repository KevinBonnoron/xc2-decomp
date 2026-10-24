#include "event/chara_hide_wpn.h"

#include "event/chara_obj.h"
#include "event/cmd_variable.h"
#include "event/frame_manager.h"
#include "event/object_chara.h"
#include "event/object_manager.h"
#include "mm_mtl/singleton.h"

namespace event {

ICmd::RESULT CharaHideWpn::update(const Param &param) {
  if (!unknown08.test(FLAG_VALID)) {
    return RESULT_END;
  }
  CharaObj *chara = static_cast<CharaObj *>(param.val(0).getUserdata());
  f32 delta = chara->getFrameInfo().unknown0c;
  if (param.getFrame() <= 0) {
    ObjectChara *npc = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(CHARA_TYPE_NPC, unknown0c);
    if (npc != nullptr) {
      npc->getCharaObj()->setHideWeapon(WPNHIDEID_HIDE_WPN, true, unknown08.test(FLAG_LEFT));
    }
    unknown10 = param.val(1).getF32();
    unknown08.set(FLAG_HIDE);
    unknown08.set(FLAG_ENDLESS, unknown10 <= 0.0f);
  }
  if (unknown08.test(FLAG_ENDLESS)) {
    return RESULT_NEXT;
  }
  unknown10 -= delta;
  if (!(unknown10 < 0.0f)) {
    return RESULT_NEXT;
  }
  ObjectChara *npc = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(CHARA_TYPE_NPC, unknown0c);
  if (npc != nullptr) {
    npc->getCharaObj()->setHideWeapon(WPNHIDEID_HIDE_WPN, false, unknown08.test(FLAG_LEFT));
  }
  unknown08.set(FLAG_HIDE, false);
  return RESULT_END;
}

void CharaHideWpn::term() {
  if (unknown08.test(FLAG_HIDE)) {
    ObjectChara *npc = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(CHARA_TYPE_NPC, unknown0c);
    if (npc != nullptr) {
      npc->getCharaObj()->setHideWeapon(WPNHIDEID_HIDE_WPN, false, unknown08.test(FLAG_LEFT));
    }
    unknown08.set(FLAG_HIDE, false);
  }
}

} // namespace event
