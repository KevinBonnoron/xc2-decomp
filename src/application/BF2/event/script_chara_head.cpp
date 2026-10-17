#include "event/script_chara_head.h"

#include "event/chara_obj.h"
#include "event/object.h"
#include "event/object_chara.h"
#include "event/object_manager.h"
#include "event/param.h"
#include "event/param_variable.h"
#include "event/script_util.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

void ScriptCharaHead::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  ObjectChara *chara = static_cast<ObjectChara *>(object);
  int type = param.val(0).getS32();
  f32 life = param.val(1).getF32();
  bool isBlendIn = param.val(2).getBool();
  bool isBlendOut = param.val(3).getBool();
  mPrevId = chara->getCharaObj()->getHead();
  chara->getCharaObj()->playHead(type, life, isBlendIn, isBlendOut);
}

void ScriptCharaHead::undo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  ObjectChara *chara = static_cast<ObjectChara *>(object);
  if (mPrevId > 0) {
    chara->getCharaObj()->playHead(mPrevId, 30.0f, true, true);
  } else {
    chara->getCharaObj()->stopHead();
  }
}

void ScriptCharaHead::redo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  int type = param.val(0).getS32();
  f32 life = param.val(1).getF32();
  static_cast<ObjectChara *>(object)->getCharaObj()->playHead(type, life, true, true);
}

} // namespace event
