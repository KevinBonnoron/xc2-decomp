#pragma once
#include "event/i_cmd.h"
#include "event/manager.h"
#include "fw/fw_debug.h"
#include "ml/scn.h"
#include "ml/scn_cam_util.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class CharaWeightPlayer;

class CharaPlayFacial : public ICmd {
public:
  enum {
    FLAG_PLAY = 1 << 0,
    FLAG_LOOP = 1 << 1,
    FLAG_DISABLE_TALK_LIP = 1 << 2,
    FLAG_DISABLE_WINK = 1 << 3,
  };

  void render(const mm::Vec3 &position, f32 height) {
    if ((unknown08 & FLAG_PLAY) == 0) {
      return;
    }
    ml::ScnObjCam *cam = Manager::get()->getScn()->getCam(-1);
    mm::Vec3 screen;
    mm::Vec3 head;
    head.x = position.x;
    head.y = position.y + height + 0.2f;
    head.z = position.z;
    if (!ml::ScnCamUtil::getScreenPos(screen, cam, head)) {
      return;
    }
    s32 x = screen.x;
    s32 y = screen.y;
    fw::debug::drawSquare2D(mm::Rect<s32>(x + 100, y, 225, 140), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
    fw::debug::drawLineSquare2D(mm::Rect<s32>(x + 100, y, 225, 140), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    s32 titleX = x + 105;
    s32 titleY = y + 5;
    fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawFont(titleX, titleY, "FACIAL");
    if ((unknown08 & FLAG_LOOP) != 0) {
      fw::debug::drawFont(x + 245, titleY, "life(∞)");
    } else {
      fw::debug::drawFont(x + 245, titleY, "life(%.1f)", unknown24);
    }
    fw::debug::drawFont(x + 110, y + 25, "seat:");
    fw::debug::drawFont(x + 170, y + 25, unknown28);
    fw::debug::drawFont(x + 110, y + 40, "priset:");
    fw::debug::drawFont(x + 170, y + 40, unknown30);
    fw::debug::drawFont(x + 110, y + 60, "brow:");
    fw::debug::drawFont(x + 170, y + 60, unknown38);
    fw::debug::drawFont(x + 290, y + 60, "%.1f", unknown40);
    fw::debug::drawFont(x + 110, y + 75, "eye:");
    fw::debug::drawFont(x + 170, y + 75, unknown48);
    fw::debug::drawFont(x + 290, y + 75, "%.1f", unknown50);
    fw::debug::drawFont(x + 110, y + 90, "lip:");
    fw::debug::drawFont(x + 170, y + 90, unknown58);
    fw::debug::drawFont(x + 290, y + 90, "%.1f", unknown60);
    fw::debug::drawFont(x + 110, y + 110, "blend:");
    fw::debug::drawFont(x + 170, y + 110, "%d>LOOP>%d", static_cast<int>(unknown64), static_cast<int>(unknown68));
  }
  void play(int type, f32 life, int browType, f32 browWeight, int eyeType, f32 eyeWeight, int lipType, f32 lipWeight, f32 blendIn, f32 blendOut);
  void idle();
  virtual void init();
  virtual RESULT update(const Param &param);
  virtual void term();

  int getType() const { return unknown20; }

private:
  u32 unknown08;                // Inferred role: flags; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown10; // Inferred role: handle; original member name unknown.
  CharaWeightPlayer *unknown18; // Inferred role: weight; original member name unknown.
  int unknown20;                // Inferred role: type; original member name unknown.
  f32 unknown24;                // Inferred role: life; original member name unknown.
  const char *unknown28;        // Inferred role: bdat name; original member name unknown.
  const char *unknown30;        // Inferred role: name; original member name unknown.
  const char *unknown38;        // Inferred role: brow stat; original member name unknown.
  f32 unknown40;                // Inferred role: brow weight; original member name unknown.
  const char *unknown48;        // Inferred role: eye stat; original member name unknown.
  f32 unknown50;                // Inferred role: eye weight; original member name unknown.
  const char *unknown58;        // Inferred role: lip stat; original member name unknown.
  f32 unknown60;                // Inferred role: lip weight; original member name unknown.
  f32 unknown64;                // Inferred role: blend in; original member name unknown.
  f32 unknown68;                // Inferred role: blend out; original member name unknown.
};

static_assert(sizeof(CharaPlayFacial) == 0x70, "");

} // namespace event
