#include "event/script_chara_talk.h"

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

void ScriptCharaTalk::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  f32 frame = param.val(0).getF32();
  bool isBlend = param.val(1).getBool();
  bool isAuto = param.val(2).getBool();
  f32 openMin = param.val(3).getF32();
  f32 openMax = param.val(4).getF32();
  f32 closeMin = param.val(5).getF32();
  f32 closeMax = param.val(6).getF32();
  static_cast<ObjectChara *>(object)->getCharaObj()->playTalk(true, frame, isBlend, isAuto, openMin, openMax, closeMin, closeMax);
}

} // namespace event
