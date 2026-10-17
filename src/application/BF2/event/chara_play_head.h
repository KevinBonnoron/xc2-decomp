#pragma once
#include "bdat.h"
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

class CharaPlayHead : public ICmd {
public:
  enum {
    FLAG_PLAY = 1 << 0,
    FLAG_LOOP = 1 << 1,
    FLAG_BLEND_OUT = 1 << 2,
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
    fw::debug::drawSquare2D(mm::Rect<s32>(x + 100, y - 90, 225, 80), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
    fw::debug::drawLineSquare2D(mm::Rect<s32>(x + 100, y - 90, 225, 80), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    s32 titleX = x + 105;
    s32 titleY = y - 85;
    fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawFont(titleX, titleY, "HEAD");
    fw::debug::drawFont(x + 110, y - 65, "head:");
    if ((flags & FLAG_LOOP) != 0) {
      fw::debug::drawFont(x + 170, y - 65, "life(∞)");
    } else {
      fw::debug::drawFont(x + 170, y - 65, "life(%.1f)", life);
    }
    fw::debug::drawFont(x + 110, y - 50, "head:");
    fw::debug::drawFont(x + 170, y - 50, name);
    fw::debug::drawFont(x + 110, y - 35, "blend:");
    fw::debug::drawFont(x + 170, y - 35, "%d>LOOP>%d", static_cast<int>(blendIn), static_cast<int>(blendOut));
  }
  void play(int type, f32 life, bool isBlendIn, bool isBlendOut);
  void idle();
  virtual void init();
  virtual RESULT update(const Param &param);
  virtual void term();

  int getType() const { return type; }

private:
  static const char *type2stat(int type) { return reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("EVT_headtype"), "stat", type, 7)); }
  static f32 type2blend(int type) { return static_cast<s16>(Bdat::getValCheck(Bdat::getFP("EVT_headtype"), "blend", type, 5)); }

  u32 flags;
  gf::GF_OBJ_HANDLE *handle;
  CharaWeightPlayer *weight;
  int type;
  f32 life;
  const char *name;
  f32 blendIn;
  f32 blendOut;
};

static_assert(sizeof(CharaPlayHead) == 0x38, "");

} // namespace event
