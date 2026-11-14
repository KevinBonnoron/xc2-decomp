#include "event/chara_play_wink.h"

#include <math.h>

#include "event/chara_lens_player.h"
#include "event/chara_play_facial.h"
#include "event/chara_set_tar.h"
#include "event/chara_wink_player.h"
#include "event/i_attach_actor.h"
#include "event/manager.h"
#include "event/object_chara.h"
#include "event/skip_manager.h"
#include "fw/fw_debug.h"
#include "gf/object/gf_obj_util.h"
#include "ml/scn.h"
#include "ml/scn_cam_util.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/singleton.h"

namespace event {

void CharaPlayWink::init() { unknown08 = 0; }

void CharaPlayWink::term() { idle(); }

mm::Vec2 CharaPlayWink::calcLensXYFromTarAxis(const mm::Vec3 &target) {
  mm::Vec2 result(0.0f, 0.0f);
  if (unknown30 != nullptr) {
    mm::Mat44 mat;
    if (unknown30->getBoneMatGlobal(mat, "JU_head")) {
      unknown50 = mat.unknown004();
      if (!(fabsf(unknown50.x - target.x) <= 0.000001f && fabsf(unknown50.y - target.y) <= 0.000001f && fabsf(unknown50.z - target.z) <= 0.000001f)) {
        mm::Vec3 direction = target - unknown50;
        f32 length = sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
        mat.setTrans(mm::Vec3::zero);
        mm::Vec3 axis = unknown40 * length;
        mm::Vec3 from(axis.x * mat.rows[0][0] + axis.y * mat.rows[1][0] + axis.z * mat.rows[2][0] + mat.rows[3][0],
                      axis.x * mat.rows[0][1] + axis.y * mat.rows[1][1] + axis.z * mat.rows[2][1] + mat.rows[3][1],
                      axis.x * mat.rows[0][2] + axis.y * mat.rows[1][2] + axis.z * mat.rows[2][2] + mat.rows[3][2]);
        result = CharaSetTar::calcLensUV(from, direction);
      }
    }
  }
  return result;
}

void CharaPlayWink::update() {
  if ((unknown08 & FLAG_UNKNOWN_0) != 0 && unknown80 != nullptr) {
    bool isSkip = mm::mtl::Singleton<SkipManager>::getPtr()->isSkip();
    mm::Vec2 lens = calcLensXYFromTarAxis(unknown80->getEyePos());
    unknown28->setManualTarget(true, lens, isSkip);
  }
}

void CharaPlayWink::idle() {
  if (gf::GfObjUtil::getObj(unknown10) != nullptr && (unknown08 & FLAG_UNKNOWN_1) != 0) {
    bool isSkip = mm::mtl::Singleton<SkipManager>::getPtr()->isSkip();
    unknown20->idle(isSkip);
    if ((unknown08 & FLAG_UNKNOWN_0) != 0) {
      unknown28->setManualTarget(false, mm::Vec2::zero, isSkip);
    }
    unknown70 = mm::Vec2::zero;
    unknown80 = nullptr;
    unknown60 = -1.0f;
  }
  unknown08 = 0;
}

void CharaPlayWink::render(const mm::Vec3 &position, f32 eyeOffset) {
  if (!(unknown08 & FLAG_UNKNOWN_1)) {
    return;
  }
  ml::ScnObjCam *cam = Manager::get()->getScn()->getCam(-1);
  mm::Vec3 screen;
  mm::Vec3 top;
  top.x = position.x;
  top.y = position.y + eyeOffset + 0.2f;
  top.z = position.z;
  if (ml::ScnCamUtil::getScreenPos(screen, cam, top)) {
    s32 x = screen.x;
    s32 y = screen.y;
    fw::debug::drawSquare2D(mm::Rect<s32>(x - 290, y - 90, 190, 80), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
    fw::debug::drawLineSquare2D(mm::Rect<s32>(x - 290, y - 90, 190, 80), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    s32 titleX = x - 285;
    s32 titleY = y - 85;
    fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawFont(titleX, titleY, "WINK");
    if (!(unknown08 & FLAG_UNKNOWN_2)) {
      fw::debug::drawFont(x - 195, titleY, "life(%.1f)", unknown60);
    } else {
      fw::debug::drawFont(x - 195, titleY, "life(∞)");
    }
    s32 labelX = x - 280;
    s32 typeY = y - 65;
    if (unknown18->unknown08 & CharaPlayFacial::FLAG_UNKNOWN_3) {
      fw::debug::drawFontColor(mm::Col4(0.5f, 0.5f, 0.5f, 1.0f));
    }
    fw::debug::drawFont(labelX, typeY, "type:");
    fw::debug::drawFont(x - 220, typeY, unknown68);
    fw::debug::drawFont(x - 210, y - 50, "(%s)", unknown20->unknown30);
    fw::debug::drawFont(labelX, y - 35, "lens:");
    if (!(unknown08 & FLAG_UNKNOWN_0)) {
      fw::debug::drawFont(x - 220, y - 35, "AUTO");
    } else {
      fw::debug::drawFont(x - 220, y - 35, "%.2f %.2f", unknown70.x, unknown70.y);
    }
    if (unknown18->unknown08 & CharaPlayFacial::FLAG_UNKNOWN_3) {
      fw::debug::drawFont(labelX, typeY, "       --------------");
      fw::debug::drawFont(labelX, y - 50, "       --------------");
      fw::debug::drawFont(labelX, y - 35, "       --------------");
      fw::debug::drawFontColor(mm::Col4::red);
      fw::debug::drawLine2D(mm::Pnt<s32>(x - 90, y - 62), mm::Pnt<s32>(x - 65, y - 77), mm::Col4::red);
      fw::debug::drawLine2D(mm::Pnt<s32>(x - 90, y - 62), mm::Pnt<s32>(x + 97, y - 62), mm::Col4::red);
      fw::debug::drawLine2D(mm::Pnt<s32>(x - 90, y - 62), mm::Pnt<s32>(x - 65, y - 47), mm::Col4::red);
      fw::debug::drawLine2D(mm::Pnt<s32>(x + 97, y + 85), mm::Pnt<s32>(x + 97, y - 62), mm::Col4::red);
      fw::debug::drawLine2D(mm::Pnt<s32>(x + 97, y + 85), mm::Pnt<s32>(x + 107, y + 85), mm::Col4::red);
      fw::debug::drawFont(x - 30, y - 78, "WINK BLOCK!!");
    }
  }
}
} // namespace event
