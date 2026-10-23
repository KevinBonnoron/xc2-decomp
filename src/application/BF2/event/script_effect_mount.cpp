#include "event/script_effect_mount.h"

#include "event/object.h"
#include "event/object_effect.h"
#include "event/object_manager.h"
#include "event/script_util.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"

namespace event {
enum ATTACH_TYPE : int;

const char *ScriptEffectMount::cmdName() const { return "effmount"; }

void ScriptEffectMount::redo(const Param &param) { doit(param); }

void ScriptEffectMount::undo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_EFFECT) {
    return;
  }
  static_cast<ObjectEffect *>(object)->setMount(nullptr, "", mm::Vec3::zero, false, static_cast<ATTACH_TYPE>(0));
}

} // namespace event
