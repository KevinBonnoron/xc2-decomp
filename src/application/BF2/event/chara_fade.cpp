#include "event/chara_fade.h"

#include "event/alpha_manager.h"
#include "event/alpha_obj.h"
#include "event/chara_obj.h"
#include "event/cmd_variable.h"
#include "event/curve.h"
#include "event/frame_manager.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

ICmd::RESULT CharaFade::update(const Param &param) {
  CharaObj *chara = static_cast<CharaObj *>(param.val(0).getUserdata());
  f32 delta = chara->getFrameInfo().unknown0c;
  if (param.getFrame() == 0) {
    f32 from = 1.0f;
    if (unknown08 != gf::unknown020) {
      from = gf::GfObjAcc(unknown08).getAlphaEvent();
    }
    f32 to = param.val(1).getBool() ? 0.0f : 1.0f;
    f32 frame = param.val(2).getF32();
    m_anmF32.clear();
    m_anmF32.append(0.0f, from, CV_TYPE_UNKNOWN_0);
    m_anmF32.append(frame, to, CV_TYPE_UNKNOWN_1);
  }
  m_anmF32.update(delta);
  if (unknown08 != gf::unknown020) {
    mm::mtl::Singleton<AlphaManager>::getPtr()->setAlpha(unknown08, ALPHA_ATTR_UNKNOWN_1, m_anmF32.getValue(), 1.0f);
  }
  if (m_anmF32.isEnd()) {
    m_anmF32.clear();
    if (unknown08 != gf::unknown020) {
      mm::mtl::Singleton<AlphaManager>::getPtr()->setAlpha(unknown08, ALPHA_ATTR_UNKNOWN_1, param.val(1).getBool() ? 0.0f : 1.0f, 1.0f);
    }
    return RESULT_UNKNOWN_1;
  }
  return RESULT_UNKNOWN_2;
}

} // namespace event
