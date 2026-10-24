#pragma once
#include "event/i_cmd.h"
#include "event/manager.h"
#include "fw/fw_debug.h"
#include "gf/object/gf_obj_util.h"
#include "ml/scn.h"
#include "ml/scn_cam_util.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
class GfEvtModel;
class GfObj;
} // namespace gf

namespace event {

class CharaDysUpdater;

class CharaPlayAction : public ICmd {
public:
  enum {
    FLAG_MESSAGE = 1 << 0,
    FLAG_KEEP = 1 << 1,
    FLAG_STANBY = 1 << 2,
    FLAG_BLEND_IN = 1 << 3,
    FLAG_BLEND_OUT = 1 << 4,
    FLAG_LOOP = 1 << 5,
    FLAG_PLAY = 1 << 6,
    FLAG_NONE = 1 << 7,
  };

  enum {
    TYPE_COMBAT = 22,
  };

  void render(const mm::Vec3 &position, f32 height) {
    if ((unknown08 & FLAG_STANBY) == 0 || gf::GfObjUtil::getObj(unknown10) == nullptr) {
      return;
    }
    mm::Vec3 head;
    head.x = position.x;
    head.y = position.y + height + 0.2f;
    head.z = position.z;
    ml::ScnObjCam *cam = Manager::get()->getScn()->getCam(-1);
    mm::Vec3 screen;
    if (!ml::ScnCamUtil::getScreenPos(screen, cam, head)) {
      return;
    }
    s32 x = screen.x;
    s32 y = screen.y;
    fw::debug::drawSquare2D(mm::Rect<s32>(x - 80, y - 60, 160, 40), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
    fw::debug::drawLineSquare2D(mm::Rect<s32>(x - 80, y - 60, 160, 40), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    s32 titleX = x - 75;
    s32 titleY = y - 55;
    fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawFont(titleX, titleY, "[ACTION]");
    if ((unknown08 & FLAG_LOOP) != 0) {
      fw::debug::drawFont(x - 5, titleY, "life(∞)");
    } else {
      fw::debug::drawFont(x - 5, titleY, "life(%.1f)", unknown34);
    }
    fw::debug::drawFont(x - 70, y - 40, unknown38);
  }
  static const char *type2stat(int type, u32 index);
  static const char *type2cmd(int type, u32 index);
  static const char *type2idle(int type);
  void stanby(int type, f32 life, bool isBlendIn, bool isBlendOut);
  static const char *type2name(int type);
  void play(gf::GfObj *obj);
  void idle();
  void clr();
  virtual void init();
  virtual RESULT update(const Param &param);
  virtual void term();

  void keep() { unknown08 |= FLAG_KEEP; }
  int getType() const { return unknown30; }
  f32 getLastFrame() const { return (unknown08 & FLAG_STANBY) != 0 ? unknown34 : 9999.0f; }

private:
  u32 unknown08;                // Inferred role: flags; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown10; // Inferred role: handle; original member name unknown.
  gf::GfEvtModel *unknown18;    // Inferred role: model; original member name unknown.
  CharaDysUpdater *unknown20;   // Inferred role: dys; original member name unknown.
  u8 _28[0x30 - 0x28];
  int unknown30;         // Inferred role: type; original member name unknown.
  f32 unknown34;         // Inferred role: life; original member name unknown.
  const char *unknown38; // Inferred role: name; original member name unknown.
};

static_assert(sizeof(CharaPlayAction) == 0x40, "");

} // namespace event
