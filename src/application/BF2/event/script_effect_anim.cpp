#include "event/script_effect_anim.h"

#include "event/effect_obj.h"
#include "event/object.h"
#include "event/object_effect.h"
#include "event/object_manager.h"
#include "event/param.h"
#include "event/param_variable.h"
#include "event/script_util.h"
#include "mm_mtl/singleton.h"

namespace event {

void ScriptEffectAnim::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_EFFECT) {
    return;
  }
  static_cast<ObjectEffect *>(object)->getEffectObj()->playAnim(param.val(0).getStr(), param.val(1).getF32());
}

} // namespace event
