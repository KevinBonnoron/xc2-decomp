#include "event/script_effect_color.h"

#include "event/curve.h"
#include "event/object.h"
#include "event/object_effect.h"
#include "event/object_manager.h"
#include "event/param.h"
#include "event/param_variable.h"
#include "event/script_util.h"
#include "mm_mtl/singleton.h"

namespace event {

void ScriptEffectColor::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_EFFECT) {
    return;
  }
  ObjectEffect *effect = static_cast<ObjectEffect *>(object);
  mm::Col4 color(param.val(0).getF32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
  prevColor = effect->getColor();
  effect->linerColor(color, param.val(4).getF32(), static_cast<CV_TYPE>(param.val(5).getS32()));
}

void ScriptEffectColor::undo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_EFFECT) {
    return;
  }
  static_cast<ObjectEffect *>(object)->setColor(prevColor);
}

void ScriptEffectColor::redo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_EFFECT) {
    return;
  }
  mm::Col4 color(param.val(0).getF32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
  static_cast<ObjectEffect *>(object)->linerColor(color, param.val(4).getF32(), static_cast<CV_TYPE>(param.val(5).getS32()));
}

} // namespace event
