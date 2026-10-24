#include "event/script_chara_walk_pos.h"

#include "event/object.h"
#include "event/object_chara.h"
#include "event/object_manager.h"
#include "event/param.h"
#include "event/param_variable.h"
#include "event/script_util.h"
#include "mm_mtl/singleton.h"

enum EVT_poscvtype : int;

namespace event {

void ScriptCharaWalkPos::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  PosAxis axis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
  ObjectChara *chara = static_cast<ObjectChara *>(object);
  unknown10 = chara->getPosAxis();
  chara->walkPosAxis(axis, static_cast<EVT_poscvtype>(param.val(4).getS32()), param.val(5).getBool());
}

void ScriptCharaWalkPos::undo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  PosAxis axis = unknown10;
  static_cast<ObjectChara *>(object)->setPosAxis(axis);
}

void ScriptCharaWalkPos::redo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  PosAxis axis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
  static_cast<ObjectChara *>(object)->setPosAxis(axis);
}

} // namespace event
