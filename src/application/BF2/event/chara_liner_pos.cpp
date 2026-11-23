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
  if (m_charaIKUpdater == nullptr || m_charaDysUpdater == nullptr) {
    return RESULT_UNKNOWN_2;
  }
  CharaObj *chara = static_cast<CharaObj *>(param.val(0).getUserdata());
  f32 delta = chara->getFrameInfo().unknown0c;
  if (param.getFrame() == 0) {
    mm::Vec3 pos(param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
    m_anmVec.clear();
    m_anmVec.append(0.0f, chara->getPos(), CV_TYPE_UNKNOWN_0);
    m_anmVec.append(param.val(4).getF32(), pos, static_cast<CV_TYPE>(param.val(5).getS32()));
    if (unknown18 == 0) {
      CharaUtil::setGravity(chara->getHandle(), false);
    }
    m_charaIKUpdater->setFootIK(false, CharaIKUpdater::FOOT_TYPE_UNKNOWN_0);
    m_charaDysUpdater->resetMovement(0);
  }
  m_anmVec.update(delta);
  chara->setPos(m_anmVec.getValue());
  if (m_anmVec.isEnd()) {
    m_anmVec.clear();
    return RESULT_UNKNOWN_1;
  }
  return RESULT_UNKNOWN_2;
}

} // namespace event
