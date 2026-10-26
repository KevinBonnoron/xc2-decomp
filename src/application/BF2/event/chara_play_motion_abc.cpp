#include "event/chara_play_motion_abc.h"

#include "event/chara_dys_updater.h"
#include "event/chara_ik_updater.h"
#include "event/extend.h"
#include "event/manager.h"
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

CharaPlayMotionABC::CharaPlayMotionABC() {
  unknown08 = 0;
  unknown10 = reinterpret_cast<gf::GF_OBJ_HANDLE *>(-1);
  unknown18 = 0;
  unknown20 = 0;
  unknown28 = 0;
  unknown58 = 0.0f;
  unknown5c = 0.0f;
  unknown60 = 0;
  unknown68 = 0.0f;
  unknown6c = 0.0f;
  unknown70 = 0.0f;
  unknown74 = 0.0f;
  unknown78 = 0.0f;
  unknown7c = 0.0f;
}

bool CharaPlayMotionABC::has(unsigned int index) const { return unknown34[index] > -1; }

void CharaPlayMotionABC::stopMotion(gf::GfObj *obj) {
  gf::GfComEvtAnim *anim = obj->getComponent<gf::GfComEvtAnim>();
  if (anim != nullptr) {
    anim->stopMulti();
    anim->setSpeed(1.0f, gf::ANIM_LAYER_BASE);
  }
  unknown20->resetDynamics(0);
}

void CharaPlayMotionABC::render(const mm::Vec3 &position, f32 eyeOffset) {
  if (!(unknown08 & 1) || gf::GfObjUtil::getObj(unknown10) == nullptr) {
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
  fw::debug::drawFont(textX, textY, "[MOTION_ABC]");
  fw::debug::drawFont(x + 35, textY, "life(%.1f)", unknown2c);
  if (unknown28 - 1U < 3 && *unknown40[static_cast<int>(unknown28 - 1U)] != '\0') {
    fw::debug::drawFont(x - 70, y - 40, mm::mtl::Singleton<Extend>::getPtr()->filename(unknown40[unknown28 - 1]));
  }
}

void CharaPlayMotionABC::term() {
  if ((unknown08 & 1) != 0) {
    gf::GfObj *obj = gf::GfObjUtil::getObj(unknown10);
    if (obj != nullptr) {
      stopMotion(obj);
    }
    unknown18->setFootIK(true, CharaIKUpdater::FOOT_TYPE_2);
    unknown08 &= ~1;
  }
}

} // namespace event
