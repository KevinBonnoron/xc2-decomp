#include "event/script_chara_motion.h"

#include "event/chara_obj.h"
#include "event/object.h"
#include "event/object_chara.h"
#include "event/object_manager.h"
#include "event/param.h"
#include "event/param_variable.h"
#include "event/script_util.h"
#include "mm_mtl/singleton.h"

namespace event {

void ScriptCharaMotion::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  static_cast<ObjectChara *>(object)->getCharaObj()->playMotion(param.val(0).getStr(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
}

void ScriptCharaMotion::undo(const Param &param) {}

} // namespace event
