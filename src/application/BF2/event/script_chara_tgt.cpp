#include "event/script_chara_tgt.h"

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

enum EVT_aimtype : int;
enum EVT_tarcvtype : int;

namespace event {

void ScriptCharaTgt::doit(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  ObjectChara *chara = static_cast<ObjectChara *>(object);
  TarAxis axis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
  f32 frame = param.val(4).getF32();
  isPrevTar = chara->isTar();
  prevAxis = chara->getTarAxis();
  mm::mtl::Singleton<ScheManager>::getPtr()->setUse(Scheduler::USE_LOOK, false, chara->getCharaObj()->getHandle());
  chara->setTar(axis, frame, static_cast<EVT_tarcvtype>(param.val(5).getS32()), static_cast<EVT_aimtype>(param.val(6).getS32()), param.val(7).getF32(), param.val(8).getF32());
}

void ScriptCharaTgt::undo(const Param &param) { mm::mtl::Singleton<ObjectManager>::getPtr(); }

void ScriptCharaTgt::redo(const Param &param) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->getActive();
  if (ScriptUtil::getObjType(object) != OBJTYPE_CHARA) {
    return;
  }
  TarAxis axis(param.val(0).getS32(), param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
  static_cast<ObjectChara *>(object)->setTar(axis, param.val(4).getF32(), static_cast<EVT_tarcvtype>(0), static_cast<EVT_aimtype>(0), -1.0f, -1.0f);
}

} // namespace event
