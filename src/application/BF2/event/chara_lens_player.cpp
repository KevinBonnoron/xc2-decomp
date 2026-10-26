#include "event/chara_lens_player.h"

#include "event/manager.h"
#include "fw/fw_debug.h"
#include "ml/scn.h"
#include "ml/scn_cam_util.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec3.h"

namespace event {

f32 CharaLensPlayer::MILD = 0.35f;

// The constructor at 0x71000babb8 clears +0x8 and +0x40, and copies
// mm::Vec2::zero into +0x10, +0x20, and +0x30.
CharaLensPlayer::CharaLensPlayer() : unknown08() {
  f32 x = mm::Vec2::zero.x;
  f32 y = mm::Vec2::zero.y;
  m_target.x = x;
  m_target.y = y;
  unknown20.x = x;
  unknown20.y = y;
  unknown30.x = x;
  unknown30.y = y;
  unknown40 = nullptr;
}

void CharaLensPlayer::create(CharaIKUpdater *ik) { unknown40 = ik; }

void CharaLensPlayer::destroy() { unknown40 = nullptr; }

void CharaLensPlayer::render(const mm::Vec3 &position, f32 height) {
  ml::ScnObjCam *cam = Manager::get()->getScn()->getCam(-1);
  mm::Vec3 screen;
  mm::Vec3 top;
  top.x = position.x;
  top.y = position.y + height + 0.2f;
  top.z = position.z;
  if (!ml::ScnCamUtil::getScreenPos(screen, cam, top)) {
    return;
  }
  s32 x = screen.x;
  s32 y = screen.y;
  fw::debug::drawSquare2D(mm::Rect<s32>(x - 80, y - 105, 160, 40), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<s32>(x - 80, y - 105, 160, 40), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  s32 textX = x - 75;
  s32 textY = y - 100;
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(textX, textY, "LENS");
  if (unknown08.test(FLAG_MANUAL)) {
    fw::debug::drawFont(x - 35, textY, "(manual)");
  } else {
    fw::debug::drawFont(x - 35, textY, "(auto)");
  }
  s32 lineY = y - 83;
  fw::debug::drawFont(x - 65, lineY, "%.1f %.1f", m_target.x, m_target.y);
  s32 padX = screen.x;
  s32 padY = screen.y;
  fw::debug::drawLineSquare2D(mm::Rect<s32>(padX + 40, padY - 105, 40, 40), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawSquare2D(mm::Rect<s32>(padX + static_cast<s32>(m_target.x * 5.0f) + 45, padY - 100 - static_cast<s32>(m_target.y * 5.0f), 30, 30), mm::Col4(0.7f, 0.7f, 0.7f, 0.7f));
}

void CharaLensPlayer::setManualTarget(bool isManual, const mm::Vec2 &target, bool isDirect) {
  if (isManual) {
    unknown08.set(FLAG_MANUAL, true);
    unknown20 = target;
  } else {
    unknown08.set(FLAG_MANUAL, false);
    unknown20 = mm::Vec2::zero;
  }
  unknown08.set(FLAG_DIRECT, isDirect);
}

void CharaLensPlayer::setAutoTarget(const mm::Vec2 &target, bool isDirect) {
  unknown30 = target;
  unknown08.set(FLAG_DIRECT, isDirect);
}

const mm::Vec2 &CharaLensPlayer::getTarget() const { return m_target; }

} // namespace event
