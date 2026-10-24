#include "event/script_chara_liner_pos.h"

#include "event/curve.h"
#include "event/object.h"
#include "event/object_chara.h"
#include "event/object_manager.h"
#include "event/param.h"
#include "event/param_variable.h"
#include "event/script_util.h"
#include "mm_mtl/singleton.h"

namespace event {

void ScriptCharaLinerPos::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  PosAxis axis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
  ObjectChara *chara = static_cast<ObjectChara *>(object);
  unknown10 = chara->getPosAxis();
  chara->linerPosAxis(axis, param.val(4).getBool(), param.val(5).getF32(), static_cast<CV_TYPE>(param.val(6).getS32()));
}

void ScriptCharaLinerPos::undo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  static_cast<ObjectChara *>(object)->setPosAxis(unknown10);
}

void ScriptCharaLinerPos::redo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  PosAxis axis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
  static_cast<ObjectChara *>(object)->setPosAxis(axis);
}

} // namespace event
