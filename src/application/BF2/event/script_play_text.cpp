#include "event/script_play_text.h"

#include "event/object.h"
#include "event/object_chara.h"
#include "event/object_list.h"
#include "event/object_manager.h"
#include "event/param.h"
#include "event/param_variable.h"
#include "event/script_util.h"
#include "event/text_manager.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {
class CharaObj;

void ScriptPlayText::doit(const Param &param) {
  const char *label = param.val(0).getStr();
  int index = param.val(1).getS32();
  f32 life = param.val(2).getF32();
  f32 delay = param.val(3).getF32();
  f32 delayBack = param.val(4).getF32();
  int captionType = param.val(5).getS32();
  CharaObj *chara;
  if (index < 0) {
    Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
    if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
      chara = nullptr;
    } else {
      chara = static_cast<ObjectChara *>(object)->getCharaObj();
    }
  } else {
    chara = static_cast<ObjectChara *>(mm::mtl::Singleton<ObjectManager>::getPtr()->getCurrent()->getCharaObject(index))->getCharaObj();
  }
  mm::mtl::Singleton<TextManager>::getPtr()->play(label, chara, life, delay, delayBack, captionType);
}

void ScriptPlayText::undo(const Param &param) { mm::mtl::Singleton<TextManager>::getPtr()->stop(); }

} // namespace event
