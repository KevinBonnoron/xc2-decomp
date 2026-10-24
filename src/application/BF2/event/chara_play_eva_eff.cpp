#include "event/chara_play_eva_eff.h"

#include <stddef.h>

#include "event/chara_manager.h"
#include "event/chara_obj.h"
#include "event/cmd_variable.h"
#include "event/extend.h"
#include "event/frame_manager.h"
#include "event/motstm_manager.h"
#include "event/res_manager.h"
#include "gf/event/gf_evt_model.h"
#include "gf/object/gf_obj_util.h"
#include "mm_mtl/singleton.h"

namespace event {

ICmd::RESULT CharaPlayEvaEff::update(const Param &param) {
  if (unknown10 != nullptr && gf::GfObjUtil::getObj(unknown10->unknown20) != nullptr) {
    f32 delta = static_cast<CharaObj *>(param.val(0).getUserdata())->getFrameInfo().unknown0c;
    if (param.getFrame() <= 0) {
      const char *name = mm::mtl::Singleton<Extend>::getPtr()->replaceString(param.val(1).getStr(), "event", "effect");
      void *data;
      size_t size;
      if (!mm::mtl::Singleton<CharaManager>::getPtr()->isStreamMode()) {
        data = mm::mtl::Singleton<ResManager>::getPtr()->adr(mm::mtl::Singleton<Extend>::getPtr()->effeva(name), &size);
      } else {
        data = mm::mtl::Singleton<MotstmManager>::getPtr()->adr(mm::mtl::Singleton<Extend>::getPtr()->effeva(name), &size);
      }
      if (data == nullptr) {
        return RESULT_END;
      }
      unknown30.play(unknown10, unknown18, data);
      f32 life = param.val(2).getF32();
      this->unknown28 = life;
      this->unknown20 = data;
      if (life <= 0.0f) {
        unknown08 |= FLAG_PLAY | FLAG_LOOP;
      } else {
        unknown08 = (unknown08 & ~FLAG_LOOP) | FLAG_PLAY;
      }
    }
    unknown30.update(delta * param.val(3).getF32());
    if ((unknown08 & FLAG_LOOP) != 0) {
      return RESULT_NEXT;
    }
    unknown28 -= delta;
    if (!(unknown28 < 0.0f)) {
      return RESULT_NEXT;
    }
    unknown30.stop();
  }
  if (mm::mtl::Singleton<CharaManager>::getPtr()->isStreamMode() && unknown20 != nullptr) {
    mm::mtl::Singleton<MotstmManager>::getPtr()->free(unknown20);
  }
  unknown20 = nullptr;
  unknown08 &= ~FLAG_PLAY;
  return RESULT_END;
}

void CharaPlayEvaEff::term() {
  if ((unknown08 & FLAG_PLAY) != 0) {
    if (mm::mtl::Singleton<CharaManager>::getPtr()->isStreamMode() && unknown20 != nullptr) {
      mm::mtl::Singleton<MotstmManager>::getPtr()->free(unknown20);
    }
    unknown20 = nullptr;
    unknown08 &= ~FLAG_PLAY;
  }
}

} // namespace event
