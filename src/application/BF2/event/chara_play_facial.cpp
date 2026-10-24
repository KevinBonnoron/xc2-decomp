#include "event/chara_play_facial.h"

#include "event/chara_obj.h"
#include "event/cmd_variable.h"
#include "event/frame_manager.h"
#include "gf/object/gf_obj_util.h"

namespace event {

void CharaPlayFacial::init() { unknown08 = 0; }

ICmd::RESULT CharaPlayFacial::update(const Param &param) {
  if (gf::GfObjUtil::getObj(unknown10) == nullptr) {
    return RESULT_END;
  }
  f32 delta = static_cast<CharaObj *>(param.val(0).getUserdata())->getFrameInfo().unknown04;
  if (param.getFrame() <= 0) {
    play(param.val(1).getS32(),
         param.val(2).getF32(),
         param.val(3).getS32(),
         param.val(4).getF32(),
         param.val(5).getS32(),
         param.val(6).getF32(),
         param.val(7).getS32(),
         param.val(8).getF32(),
         param.val(9).getF32(),
         param.val(10).getF32());
  }
  if ((unknown08 & FLAG_LOOP) == 0) {
    unknown24 -= delta;
    if (unknown24 < 0.0f) {
      idle();
      return RESULT_END;
    }
  }
  return RESULT_NEXT;
}

void CharaPlayFacial::term() { idle(); }

} // namespace event
