#include "event/script_chara_facial.h"

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

void ScriptCharaFacial::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  ObjectChara *chara = static_cast<ObjectChara *>(object);
  int type = param.val(0).getS32();
  f32 life = param.val(1).getF32();
  int browType = param.val(2).getS32();
  f32 browWeight = param.val(3).getF32();
  int eyeType = param.val(4).getS32();
  f32 eyeWeight = param.val(5).getF32();
  int lipType = param.val(6).getS32();
  f32 lipWeight = param.val(7).getF32();
  f32 blendIn = param.val(8).getF32();
  f32 blendOut = param.val(9).getF32();
  unknown08 = chara->getCharaObj()->getFacial();
  chara->getCharaObj()->playFacial(type, life, browType, browWeight, eyeType, eyeWeight, lipType, lipWeight, blendIn, blendOut);
}

void ScriptCharaFacial::undo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  static_cast<ObjectChara *>(object)->getCharaObj()->playFacial(unknown08, 30.0f, -1, -1.0f, -1, -1.0f, -1, -1.0f, -1.0f, -1.0f);
}

} // namespace event
