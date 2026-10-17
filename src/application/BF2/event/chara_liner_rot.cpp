#include "event/chara_liner_rot.h"

#include "event/chara_dys_updater.h"
#include "event/chara_obj.h"
#include "event/cmd_variable.h"
#include "event/curve.h"
#include "event/frame_manager.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace event {

ICmd::RESULT CharaLinerRot::update(const Param &param) {
  if (dysUpdater == nullptr) {
    return RESULT_NEXT;
  }
  CharaObj *chara = static_cast<CharaObj *>(param.val(0).getUserdata());
  f32 delta = chara->getFrameInfo().streamDelta;
  if (param.getFrame() == 0) {
    mm::Vec3 from = chara->getRot();
    mm::Vec3 to(param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
    anm.clear();
    anm.append(0.0f, from, CV_TYPE_STEP);
    anm.append(param.val(4).getF32(), to, static_cast<CV_TYPE>(param.val(5).getS32()));
    dysUpdater->resetMovement(0);
  }
  anm.update(delta);
  chara->setRot(anm.getValue());
  if (anm.isEnd()) {
    anm.clear();
    return RESULT_END;
  }
  return RESULT_NEXT;
}

} // namespace event
