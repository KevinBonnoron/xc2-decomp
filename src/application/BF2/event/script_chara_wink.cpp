#include "event/script_chara_wink.h"

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

void ScriptCharaWink::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  int type = param.val(0).getS32();
  f32 frame = param.val(1).getF32();
  bool isLoop = param.val(2).getBool();
  f32 lensX = param.val(3).getF32();
  f32 lensY = param.val(4).getF32();
  int lensType = param.val(5).getS32();
  bool isDirect = param.val(6).getBool();
  bool isAuto = param.val(7).getBool();
  static_cast<ObjectChara *>(object)->getCharaObj()->playWink(type, frame, isLoop, lensX, lensY, lensType, isDirect, isAuto);
}

} // namespace event
