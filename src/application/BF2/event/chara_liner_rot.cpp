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
  if (unknown08 == nullptr) {
    return RESULT_NEXT;
  }
  CharaObj *chara = static_cast<CharaObj *>(param.val(0).getUserdata());
  f32 delta = chara->getFrameInfo().unknown0c;
  if (param.getFrame() == 0) {
    mm::Vec3 from = chara->getRot();
    mm::Vec3 to(param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
    unknown10.clear();
    unknown10.append(0.0f, from, CV_TYPE_STEP);
    unknown10.append(param.val(4).getF32(), to, static_cast<CV_TYPE>(param.val(5).getS32()));
    unknown08->resetMovement(0);
  }
  unknown10.update(delta);
  chara->setRot(unknown10.getValue());
  if (unknown10.isEnd()) {
    unknown10.clear();
    return RESULT_END;
  }
  return RESULT_NEXT;
}

} // namespace event
