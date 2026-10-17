#include "event/script_effect_play.h"

#include "event/object.h"
#include "event/object_effect.h"
#include "event/object_manager.h"
#include "event/param.h"
#include "event/param_variable.h"
#include "event/script_util.h"
#include "mm_mtl/singleton.h"

namespace event {

void ScriptEffectPlay::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_EFFECT) {
    return;
  }
  static_cast<ObjectEffect *>(object)->play(
      param.val(0).getStr(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32(), param.val(4).getS32(), param.val(5).getS32());
}

void ScriptEffectPlay::undo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_EFFECT) {
    return;
  }
  static_cast<ObjectEffect *>(object)->stop();
}

void ScriptEffectPlay::redo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_EFFECT) {
    return;
  }
  static_cast<ObjectEffect *>(object)->play(
      param.val(0).getStr(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32(), param.val(4).getS32(), 0);
}

} // namespace event
