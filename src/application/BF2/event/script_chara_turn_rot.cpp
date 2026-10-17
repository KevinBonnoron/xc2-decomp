#include "event/script_chara_turn_rot.h"

#include "event/chara_obj.h"
#include "event/object.h"
#include "event/object_chara.h"
#include "event/object_manager.h"
#include "event/param.h"
#include "event/param_variable.h"
#include "event/sche_manager.h"
#include "event/scheduler.h"
#include "event/script_util.h"
#include "mm_mtl/singleton.h"

enum EVT_rotcvtype : int;

namespace event {

void ScriptCharaTurnRot::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  ObjectChara *chara = static_cast<ObjectChara *>(object);
  RotAxis axis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
  prevAxis = chara->getRotAxis();
  mm::mtl::Singleton<ScheManager>::getPtr()->setUse(Scheduler::USE_TURN, false, chara->getCharaObj()->getHandle());
  chara->turnRotAxis(axis, static_cast<EVT_rotcvtype>(param.val(4).getS32()), param.val(5).getF32());
}

void ScriptCharaTurnRot::undo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  RotAxis axis = prevAxis;
  static_cast<ObjectChara *>(object)->setRotAxis(axis);
}

void ScriptCharaTurnRot::redo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  RotAxis axis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
  static_cast<ObjectChara *>(object)->setRotAxis(axis);
}

} // namespace event
