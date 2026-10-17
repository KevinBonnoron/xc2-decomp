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
    if ((flags & FLAG_PLAY) == 0) {
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
    if ((flags & FLAG_LOOP) != 0) {
      fw::debug::drawFont(x + 245, titleY, "life(∞)");
    } else {
      fw::debug::drawFont(x + 245, titleY, "life(%.1f)", life);
    }
    fw::debug::drawFont(x + 110, y + 25, "seat:");
    fw::debug::drawFont(x + 170, y + 25, bdatName);
    fw::debug::drawFont(x + 110, y + 40, "priset:");
    fw::debug::drawFont(x + 170, y + 40, name);
    fw::debug::drawFont(x + 110, y + 60, "brow:");
    fw::debug::drawFont(x + 170, y + 60, browStat);
    fw::debug::drawFont(x + 290, y + 60, "%.1f", browWeight);
    fw::debug::drawFont(x + 110, y + 75, "eye:");
    fw::debug::drawFont(x + 170, y + 75, eyeStat);
    fw::debug::drawFont(x + 290, y + 75, "%.1f", eyeWeight);
    fw::debug::drawFont(x + 110, y + 90, "lip:");
    fw::debug::drawFont(x + 170, y + 90, lipStat);
    fw::debug::drawFont(x + 290, y + 90, "%.1f", lipWeight);
    fw::debug::drawFont(x + 110, y + 110, "blend:");
    fw::debug::drawFont(x + 170, y + 110, "%d>LOOP>%d", static_cast<int>(blendIn), static_cast<int>(blendOut));
  }
  void play(int type, f32 life, int browType, f32 browWeight, int eyeType, f32 eyeWeight, int lipType, f32 lipWeight, f32 blendIn, f32 blendOut);
  void idle();
  virtual void init();
  virtual RESULT update(const Param &param);
  virtual void term();

  int getType() const { return type; }

private:
  u32 flags;
  gf::GF_OBJ_HANDLE *handle;
  CharaWeightPlayer *weight;
  int type;
  f32 life;
  const char *bdatName;
  const char *name;
  const char *browStat;
  f32 browWeight;
  const char *eyeStat;
  f32 eyeWeight;
  const char *lipStat;
  f32 lipWeight;
  f32 blendIn;
  f32 blendOut;
};

static_assert(sizeof(CharaPlayFacial) == 0x70, "");

} // namespace event
