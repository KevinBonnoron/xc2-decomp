#include "event/script_chara_fade.h"

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

void ScriptCharaFade::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  ObjectChara *chara = static_cast<ObjectChara *>(object);
  bool isOut = param.val(0).getBool();
  f32 frame = param.val(1).getF32();
  isPrevFadeOut = chara->getCharaObj()->isFadeOut();
  chara->getCharaObj()->playFade(isOut, frame);
}

void ScriptCharaFade::undo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  static_cast<ObjectChara *>(object)->getCharaObj()->playFade(isPrevFadeOut, 0.0f);
}

void ScriptCharaFade::redo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  static_cast<ObjectChara *>(object)->getCharaObj()->playFade(param.val(0).getBool(), 0.0f);
}

} // namespace event
