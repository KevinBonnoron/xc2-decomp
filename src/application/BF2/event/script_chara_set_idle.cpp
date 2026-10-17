#include "event/script_chara_set_idle.h"

#include "event/chara_obj.h"
#include "event/object.h"
#include "event/object_chara.h"
#include "event/object_manager.h"
#include "event/param.h"
#include "event/param_variable.h"
#include "event/script_util.h"
#include "mm_mtl/singleton.h"

namespace event {

void ScriptCharaSetIdle::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  ObjectChara *chara = static_cast<ObjectChara *>(object);
  mPrevId = chara->getCharaObj()->getIdle();
  chara->getCharaObj()->setIdle(param.val(0).getS32());
}

void ScriptCharaSetIdle::undo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  static_cast<ObjectChara *>(object)->getCharaObj()->setIdle(mPrevId);
}

} // namespace event
