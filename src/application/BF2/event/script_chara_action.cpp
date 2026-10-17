#include "event/script_chara_action.h"

#include "event/chara_obj.h"
#include "event/object.h"
#include "event/object_chara.h"
#include "event/object_manager.h"
#include "event/param.h"
#include "event/param_variable.h"
#include "event/sche_manager.h"
#include "event/scheduler.h"
#include "event/script_util.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

void ScriptCharaAction::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  ObjectChara *chara = static_cast<ObjectChara *>(object);
  int type = param.val(0).getS32();
  f32 frame = param.val(1).getF32();
  bool isLoop = param.val(2).getBool();
  bool isBlend = param.val(3).getBool();
  mPrevId = chara->getCharaObj()->getAction();
  mm::mtl::Singleton<ScheManager>::getPtr()->setUse(Scheduler::USE_TURN, false, chara->getCharaObj()->getHandle());
  chara->getCharaObj()->playAction(type, frame, isLoop, isBlend);
}

void ScriptCharaAction::undo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  ObjectChara *chara = static_cast<ObjectChara *>(object);
  if (mPrevId > 0) {
    chara->getCharaObj()->playAction(mPrevId, 30.0f, true, true);
  } else {
    chara->getCharaObj()->stopAction();
  }
}

void ScriptCharaAction::redo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  int type = param.val(0).getS32();
  f32 frame = param.val(1).getF32();
  static_cast<ObjectChara *>(object)->getCharaObj()->playAction(type, frame, true, true);
}

} // namespace event
