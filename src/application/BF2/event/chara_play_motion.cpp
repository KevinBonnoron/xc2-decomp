#include "event/chara_play_motion.h"

#include "event/chara_dys_updater.h"
#include "event/chara_ik_updater.h"
#include "event/chara_manager.h"
#include "event/chara_obj.h"
#include "event/cmd_variable.h"
#include "event/extend.h"
#include "event/frame_manager.h"
#include "event/manager.h"
#include "event/motstm_manager.h"
#include "event/res_manager.h"
#include "fw/fw_debug.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/animation/gf_com_evt_anim.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"
#include "ml/scn.h"
#include "ml/scn_cam_util.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"

namespace event {

CharaPlayMotion::CharaPlayMotion() {
  unknown08 = 0;
  unknown10 = reinterpret_cast<gf::GF_OBJ_HANDLE *>(-1);
  m_charaIKUpdater = 0;
  m_charaDysUpdater = 0;
  unknown28 = 0;
  unknown30 = 0;
  unknown3c = 0.0f;
  unknown40 = 0.0f;
}

ICmd::RESULT CharaPlayMotion::update(const Param &param) {
  gf::GfObj *obj = gf::GfObjUtil::getObj(unknown10);
  if (obj == nullptr) {
    if (CharaManager::getPtr()->isStreamMode() && unknown28 != nullptr) {
      MotstmManager::getPtr()->free(unknown28);
    }
    unknown08 &= ~(2 | 4);
    unknown28 = nullptr;
    unknown30 = 0;
    return RESULT_UNKNOWN_1;
  }
  const FrameInfo &info = static_cast<CharaObj *>(param.val(0).getUserdata())->getFrameInfo();
  f32 delta = info.unknown04;
  if (param.getFrame() <= 0) {
    const char *name = param.val(1).getStr();
    if (!CharaManager::getPtr()->isStreamMode()) {
      unknown28 = mm::mtl::Singleton<ResManager>::getPtr()->adr(mm::mtl::Singleton<Extend>::getPtr()->anm(name), &unknown30);
    } else {
      unknown28 = MotstmManager::getPtr()->adr(mm::mtl::Singleton<Extend>::getPtr()->anm(name), &unknown30);
    }
    if (unknown28 == nullptr) {
      return RESULT_UNKNOWN_1;
    }
    unknown3c = param.val(3).getF32();
    unknown40 = 0.0f;
    play(obj, unknown28, unknown30, param.val(4).getF32());
    m_charaIKUpdater->setFootIK(false, CharaIKUpdater::FOOT_TYPE_UNKNOWN_2);
    unknown48 = name;
    f32 life = param.val(2).getF32();
    unknown38 = life;
    unknown08 |= 2;
    setFlag(8, life <= 0.0f);
  }
  if ((unknown08 & 4) != 0) {
    gf::GfComEvtAnim *anim = obj->getComponent<gf::GfComEvtAnim>();
    if (anim != nullptr) {
      anim->setSpeed(unknown40, gf::ANIM_LAYER_UNKNOWN_0);
    }
  }
  unknown40 = unknown3c * info.unknown0c;
  if ((unknown08 & 8) == 0) {
    unknown38 -= delta;
    if (unknown38 < 0.0f) {
      stop(obj);
      m_charaIKUpdater->setFootIK(true, CharaIKUpdater::FOOT_TYPE_UNKNOWN_2);
      if (CharaManager::getPtr()->isStreamMode() && unknown28 != nullptr) {
        MotstmManager::getPtr()->free(unknown28);
      }
      unknown48 = "";
      unknown28 = nullptr;
      unknown30 = 0;
      unknown08 &= ~2;
      return RESULT_UNKNOWN_1;
    }
  }
  return RESULT_UNKNOWN_2;
}

void CharaPlayMotion::play(gf::GfObj *obj, void *motion, u64 size, f32 time) {
  if ((unknown08 & 1) == 0) {
    return;
  }
  gf::GfComEvtAnim *anim = obj->getComponent<gf::GfComEvtAnim>();
  if (anim != nullptr) {
    anim->play(motion, size, time / 30.0f);
  }
  m_charaDysUpdater->resetDynamics(0);
  unknown08 |= 4;
}

void CharaPlayMotion::render(const mm::Vec3 &position, f32 eyeOffset) {
  if (unknown28 == nullptr || gf::GfObjUtil::getObj(unknown10) == nullptr) {
    return;
  }
  mm::Vec3 top;
  top.x = position.x;
  top.y = position.y + eyeOffset + 0.2f;
  top.z = position.z;
  mm::Vec3 screen;
  if (!ml::ScnCamUtil::getScreenPos(screen, Manager::get()->getScn()->getCam(-1), top)) {
    return;
  }
  s32 x = screen.x;
  s32 y = screen.y;
  fw::debug::drawSquare2D(mm::Rect<s32>(x - 80, y - 60, 220, 40), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<s32>(x - 80, y - 60, 220, 40), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  s32 textX = x - 75;
  s32 textY = y - 55;
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(textX, textY, "[MOTION]");
  if (!(unknown08 & 8)) {
    fw::debug::drawFont(x + 35, textY, "life(%.1f)", unknown38);
  } else {
    fw::debug::drawFont(x + 35, textY, "life(∞)");
  }
  fw::debug::drawFont(x - 70, y - 40, mm::mtl::Singleton<Extend>::getPtr()->filename(unknown48));
}

void CharaPlayMotion::term() {
  if ((unknown08 & 2) == 0) {
    return;
  }
  gf::GfObj *obj = gf::GfObjUtil::getObj(unknown10);
  if (obj != nullptr) {
    stop(obj);
  }
  m_charaIKUpdater->setFootIK(true, CharaIKUpdater::FOOT_TYPE_UNKNOWN_2);
  if (CharaManager::getPtr()->isStreamMode() && unknown28 != nullptr) {
    MotstmManager::getPtr()->free(unknown28);
  }
  unknown28 = nullptr;
  unknown08 &= ~2;
}

void CharaPlayMotion::stop(gf::GfObj *obj) {
  if ((unknown08 & 4) == 0) {
    return;
  }
  gf::GfComEvtAnim *anim = obj->getComponent<gf::GfComEvtAnim>();
  if (anim != nullptr) {
    anim->stop();
    anim->setSpeed(1.0f, gf::ANIM_LAYER_UNKNOWN_0);
  }
  m_charaDysUpdater->resetDynamics(0);
  unknown08 &= ~4;
}

} // namespace event
