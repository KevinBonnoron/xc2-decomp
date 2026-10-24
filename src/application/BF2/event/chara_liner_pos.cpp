#include "event/chara_liner_pos.h"

#include "event/chara_dys_updater.h"
#include "event/chara_ik_updater.h"
#include "event/chara_obj.h"
#include "event/chara_util.h"
#include "event/cmd_variable.h"
#include "event/curve.h"
#include "event/frame_manager.h"
#include "mm_math/mm_vec3.h"

namespace event {

ICmd::RESULT CharaLinerPos::update(const Param &param) {
  if (unknown08 == nullptr || unknown10 == nullptr) {
    return RESULT_NEXT;
  }
  CharaObj *chara = static_cast<CharaObj *>(param.val(0).getUserdata());
  f32 delta = chara->getFrameInfo().unknown0c;
  if (param.getFrame() == 0) {
    mm::Vec3 pos(param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
    unknown20.clear();
    unknown20.append(0.0f, chara->getPos(), CV_TYPE_STEP);
    unknown20.append(param.val(4).getF32(), pos, static_cast<CV_TYPE>(param.val(5).getS32()));
    if (unknown18 == 0) {
      CharaUtil::setGravity(chara->getHandle(), false);
    }
    unknown08->setFootIK(false, CharaIKUpdater::FOOT_TYPE_0);
    unknown10->resetMovement(0);
  }
  unknown20.update(delta);
  chara->setPos(unknown20.getValue());
  if (unknown20.isEnd()) {
    unknown20.clear();
    return RESULT_END;
  }
  return RESULT_NEXT;
}

} // namespace event
