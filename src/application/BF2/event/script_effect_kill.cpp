#include "event/script_effect_kill.h"

#include "event/effect_obj.h"
#include "event/object.h"
#include "event/object_effect.h"
#include "event/object_manager.h"
#include "event/script_util.h"
#include "mm_mtl/singleton.h"

namespace event {

void ScriptEffectKill::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_EFFECT) {
    return;
  }
  static_cast<ObjectEffect *>(object)->getEffectObj()->kill();
}

void ScriptEffectKill::redo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_EFFECT) {
    return;
  }
  static_cast<ObjectEffect *>(object)->getEffectObj()->kill();
}

} // namespace event
