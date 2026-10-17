#include "event/script_chara_mount.h"

#include "event/chara_obj.h"
#include "event/object.h"
#include "event/object_chara.h"
#include "event/object_manager.h"
#include "event/param.h"
#include "event/param_variable.h"
#include "event/script_util.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

void ScriptCharaMount::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  ObjectChara *chara = static_cast<ObjectChara *>(object);
  u32 index = param.val(0).getS32();
  const char *bone = param.val(1).getStr();
  mm::Vec3 pos(param.val(2).getF32(), param.val(3).getF32(), param.val(4).getF32());
  mm::Vec3 rot(param.val(5).getF32(), param.val(6).getF32(), param.val(7).getF32());
  if (mm::mtl::Singleton<ObjectManager>::getPtr()->getCharaCount() > index) {
    ObjectChara *target = mm::mtl::Singleton<ObjectManager>::getPtr()->getChara(index);
    if (chara != target) {
      chara->getCharaObj()->mount(target->getCharaObj(), bone, pos, rot);
    }
  }
}

void ScriptCharaMount::undo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  static_cast<ObjectChara *>(object)->getCharaObj()->mount(nullptr, "", mm::Vec3::zero, mm::Vec3::zero);
}

} // namespace event
