#include "event/script_chara_motion_abc.h"

#include "event/chara_obj.h"
#include "event/object.h"
#include "event/object_chara.h"
#include "event/object_manager.h"
#include "event/param.h"
#include "event/param_variable.h"
#include "event/script_util.h"
#include "mm_mtl/singleton.h"

namespace event {

void ScriptCharaMotionABC::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  static_cast<ObjectChara *>(object)->getCharaObj()->playMotionABC(param.val(0).getStr(),
                                                                   param.val(1).getStr(),
                                                                   param.val(2).getStr(),
                                                                   param.val(3).getF32(),
                                                                   param.val(4).getF32(),
                                                                   param.val(5).getF32(),
                                                                   param.val(6).getF32(),
                                                                   param.val(7).getF32(),
                                                                   param.val(8).getF32());
}

void ScriptCharaMotionABC::undo(const Param &param) {}

} // namespace event
