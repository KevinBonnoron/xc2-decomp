#include "event/chara_play_talk.h"

#include "event/chara_play_facial.h"
#include "event/manager.h"
#include "fw/fw_debug.h"
#include "ml/scn.h"
#include "ml/scn_cam_util.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec3.h"

namespace event {

void CharaPlayTalk::init() {
  unknown08 = 0;
  unknown68 = 1.0f;
  unknown6c = 1.0f;
  unknown70 = 0.0f;
  unknown74 = 0.0f;
}

void CharaPlayTalk::term() { idle(); }

void CharaPlayTalk::render(const mm::Vec3 &position, f32 eyeOffset) {
  if (!(unknown08 & FLAG_PLAY)) {
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
    fw::debug::drawSquare2D(mm::Rect<s32>(x - 290, y, 190, 180), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
    fw::debug::drawLineSquare2D(mm::Rect<s32>(x - 290, y, 190, 180), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    s32 titleX = x - 285;
    s32 titleY = y + 5;
    fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawFont(titleX, titleY, "TALK");
    if (!(unknown08 & FLAG_LOOP)) {
      fw::debug::drawFont(x - 185, titleY, "life(%.1f)", unknown28);
    } else {
      fw::debug::drawFont(x - 185, titleY, "life(∞)");
    }
    s32 labelX = x - 280;
    fw::debug::drawFont(labelX, y + 25, "priset:");
    s32 valueX = x - 220;
    fw::debug::drawFont(valueX, y + 25, unknown38);
    s32 lipY = y + 45;
    fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawFont(labelX, lipY, "lip:");
    if (unknown18->unknown08 & CharaPlayFacial::FLAG_DISABLE_TALK_LIP) {
      fw::debug::drawFontColor(mm::Col4(0.5f, 0.5f, 0.5f, 1.0f));
    }
    if (!unknown40) {
      fw::debug::drawFont(valueX, lipY, "bdat  =off(1.0)");
    } else {
      fw::debug::drawFont(valueX, lipY, "bdat  =on(%.1f)", unknown5c);
    }
    s32 lipValueY = y + 60;
    if (!unknown41) {
      fw::debug::drawFont(valueX, lipValueY, "lip   =off(1.0)");
    } else {
      if (unknown08 & FLAG_UNKNOWN_2) {
        fw::debug::drawFontColor(mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
      }
      fw::debug::drawFont(valueX, lipValueY, "lip   =on(%.1f)", unknown60);
    }
    s32 weightY = y + 75;
    if (!(unknown18->unknown08 & CharaPlayFacial::FLAG_DISABLE_TALK_LIP)) {
      fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    } else {
      fw::debug::drawFontColor(mm::Col4(0.5f, 0.5f, 0.5f, 1.0f));
    }
    fw::debug::drawFont(valueX, weightY, "weight=%.1f", unknown44);
    s32 weight2Y = y + 90;
    fw::debug::drawFont(valueX, weight2Y, "      =%.1f", unknown64);
    fw::debug::drawFont(valueX, y + 105, "speed =%.1f", unknown48);
    s32 headY = y + 125;
    fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawFont(labelX, headY, "head:");
    if (unknown18->unknown08 & CharaPlayFacial::FLAG_DISABLE_TALK_LIP) {
      fw::debug::drawFontColor(mm::Col4(0.5f, 0.5f, 0.5f, 1.0f));
    }
    fw::debug::drawFont(valueX, headY, "weight=%.1f", unknown4c);
    fw::debug::drawFont(valueX, y + 140, "speed =%.1f", unknown50);
    if (unknown18->unknown08 & CharaPlayFacial::FLAG_DISABLE_TALK_LIP) {
      fw::debug::drawFont(labelX, lipY, "       --------------");
      fw::debug::drawFont(labelX, lipValueY, "       --------------");
      fw::debug::drawFont(labelX, weightY, "       --------------");
      fw::debug::drawFont(labelX, weight2Y, "       --------------");
      fw::debug::drawFont(labelX, y + 110, "       --------------");
      fw::debug::drawFont(labelX, headY, "       --------------");
      fw::debug::drawFont(labelX, y + 140, "       --------------");
      fw::debug::drawFontColor(mm::Col4::red);
      s32 lineX = x - 90;
      s32 lineY = y + 100;
      fw::debug::drawLine2D(mm::Pnt<s32>(lineX, lineY), mm::Pnt<s32>(x - 65, y + 85), mm::Col4::red);
      fw::debug::drawLine2D(mm::Pnt<s32>(lineX, lineY), mm::Pnt<s32>(x + 107, lineY), mm::Col4::red);
      fw::debug::drawLine2D(mm::Pnt<s32>(lineX, lineY), mm::Pnt<s32>(x - 65, y + 115), mm::Col4::red);
      fw::debug::drawFont(x - 30, y + 80, "LIP BLOCK!!");
    }
    s32 blendY = y + 160;
    fw::debug::drawFontColor(mm::Col4::white);
    fw::debug::drawFont(labelX, blendY, "blend:");
    fw::debug::drawFont(valueX, blendY, "%d>LOOP>%d", static_cast<int>(unknown54), static_cast<int>(unknown58));
  }
  if (ml::ScnCamUtil::getScreenPos(screen, cam, top)) {
    s32 x = screen.x;
    s32 y = screen.y;
    fw::debug::drawSquare2D(mm::Rect<s32>(x - 380, y, 80, 25), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
    fw::debug::drawLineSquare2D(mm::Rect<s32>(x - 380, y, 80, 25), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    s32 textY = y + 5;
    fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    if (!(unknown08 & FLAG_MANUAL)) {
      fw::debug::drawFont(x - 375, textY, "AUTO");
    } else {
      fw::debug::drawFont(x - 355, textY, "MANUAL");
    }
  }
}

} // namespace event
