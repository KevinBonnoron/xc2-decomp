#include "event/script_effect_turn.h"

#include "event/curve.h"
#include "event/object.h"
#include "event/object_effect.h"
#include "event/object_manager.h"
#include "event/param.h"
#include "event/param_variable.h"
#include "event/script_util.h"
#include "mm_mtl/singleton.h"

namespace event {

void ScriptEffectTurn::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_EFFECT) {
    return;
  }
  ObjectEffect *effect = static_cast<ObjectEffect *>(object);
  RotAxis axis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
  prevAxis = effect->getRotAxis();
  effect->linerRotAxis(axis, param.val(4).getF32(), static_cast<CV_TYPE>(param.val(5).getS32()));
}

void ScriptEffectTurn::undo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_EFFECT) {
    return;
  }
  static_cast<ObjectEffect *>(object)->setRotAxis(prevAxis);
}

void ScriptEffectTurn::redo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_EFFECT) {
    return;
  }
  static_cast<ObjectEffect *>(object)->setRotAxis(RotAxis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32()));
}

} // namespace event
