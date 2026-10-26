#include "event/script_effect_mount.h"

#include "event/chara_obj.h"
#include "event/object.h"
#include "event/object_chara.h"
#include "event/object_effect.h"
#include "event/object_manager.h"
#include "event/param.h"
#include "event/param_variable.h"
#include "event/script_util.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"

namespace event {
enum ATTACH_TYPE : int;

const char *ScriptEffectMount::cmdName() const { return "effmount"; }

void ScriptEffectMount::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_EFFECT) {
    return;
  }
  ObjectChara *chara = static_cast<ObjectChara *>(param.val(0).getUserdata());
  ATTACH_TYPE type = static_cast<ATTACH_TYPE>(param.val(1).getS32());
  const char *bone = param.val(2).getStr();
  mm::Vec3 offset(param.val(3).getF32(), param.val(4).getF32(), param.val(5).getF32());
  bool isRotate = param.val(6).getBool();
  static_cast<ObjectEffect *>(object)->setMount(chara->getCharaObj()->getAttachActor(), bone, offset, isRotate, type);
}

void ScriptEffectMount::redo(const Param &param) { doit(param); }

void ScriptEffectMount::undo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_EFFECT) {
    return;
  }
  static_cast<ObjectEffect *>(object)->setMount(nullptr, "", mm::Vec3::zero, false, static_cast<ATTACH_TYPE>(0));
}

} // namespace event
