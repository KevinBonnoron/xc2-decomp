#include "event/script_effect_scale.h"

#include "event/object.h"
#include "event/object_effect.h"
#include "event/object_manager.h"
#include "event/param.h"
#include "event/param_variable.h"
#include "event/script_util.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

void ScriptEffectScale::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_EFFECT) {
    return;
  }
  ObjectEffect *effect = static_cast<ObjectEffect *>(object);
  prevScale = effect->getScale();
  f32 scale = param.val(0).getF32();
  effect->setScale(mm::Vec3(scale, scale, scale));
}

void ScriptEffectScale::undo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_EFFECT) {
    return;
  }
  static_cast<ObjectEffect *>(object)->setScale(prevScale);
}

void ScriptEffectScale::redo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_EFFECT) {
    return;
  }
  f32 scale = param.val(0).getF32();
  static_cast<ObjectEffect *>(object)->setScale(mm::Vec3(scale, scale, scale));
}

} // namespace event
