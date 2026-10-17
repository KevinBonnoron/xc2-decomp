#include "event/chara_hide_wpn.h"

#include "event/chara_obj.h"
#include "event/cmd_variable.h"
#include "event/frame_manager.h"
#include "event/object_chara.h"
#include "event/object_manager.h"
#include "mm_mtl/singleton.h"

namespace event {

ICmd::RESULT CharaHideWpn::update(const Param &param) {
  if (!flags.test(FLAG_VALID)) {
    return RESULT_END;
  }
  CharaObj *chara = static_cast<CharaObj *>(param.val(0).getUserdata());
  f32 delta = chara->getFrameInfo().streamDelta;
  if (param.getFrame() <= 0) {
    ObjectChara *npc = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(CHARA_TYPE_NPC, npcId);
    if (npc != nullptr) {
      npc->getCharaObj()->setHideWeapon(WPNHIDEID_HIDE_WPN, true, flags.test(FLAG_LEFT));
    }
    time = param.val(1).getF32();
    flags.set(FLAG_HIDE);
    flags.set(FLAG_ENDLESS, time <= 0.0f);
  }
  if (flags.test(FLAG_ENDLESS)) {
    return RESULT_NEXT;
  }
  time -= delta;
  if (!(time < 0.0f)) {
    return RESULT_NEXT;
  }
  ObjectChara *npc = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(CHARA_TYPE_NPC, npcId);
  if (npc != nullptr) {
    npc->getCharaObj()->setHideWeapon(WPNHIDEID_HIDE_WPN, false, flags.test(FLAG_LEFT));
  }
  flags.set(FLAG_HIDE, false);
  return RESULT_END;
}

void CharaHideWpn::term() {
  if (flags.test(FLAG_HIDE)) {
    ObjectChara *npc = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(CHARA_TYPE_NPC, npcId);
    if (npc != nullptr) {
      npc->getCharaObj()->setHideWeapon(WPNHIDEID_HIDE_WPN, false, flags.test(FLAG_LEFT));
    }
    flags.set(FLAG_HIDE, false);
  }
}

} // namespace event
