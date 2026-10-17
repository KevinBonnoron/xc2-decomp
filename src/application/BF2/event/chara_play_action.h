#pragma once
#include "bdat.h"
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
    if ((flags & FLAG_STANBY) == 0 || gf::GfObjUtil::getObj(handle) == nullptr) {
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
    if ((flags & FLAG_LOOP) != 0) {
      fw::debug::drawFont(x - 5, titleY, "life(∞)");
    } else {
      fw::debug::drawFont(x - 5, titleY, "life(%.1f)", life);
    }
    fw::debug::drawFont(x - 70, y - 40, name);
  }
  static const char *type2stat(int type, u32 index) {
    const char *column;
    switch (index) {
    case 0:
      column = "stat0";
      break;
    case 1:
      column = "stat1";
      break;
    default:
      column = "stat2";
      break;
    }
    return reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("EVT_acttype"), column, type, 7));
  }
  static const char *type2cmd(int type, u32 index) {
    const char *column;
    switch (index) {
    case 0:
      column = "cmd0";
      break;
    case 1:
      column = "cmd1";
      break;
    default:
      column = "cmd2";
      break;
    }
    return reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("EVT_acttype"), column, type, 7));
  }
  static const char *type2idle(int type) { return reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("EVT_acttype"), "statI", type, 7)); }
  void stanby(int type, f32 life, bool isBlendIn, bool isBlendOut);
  static const char *type2name(int type) { return reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("EVT_acttype"), "name", type, 7)); }
  void play(gf::GfObj *obj);
  void idle();
  void clr();
  virtual void init();
  virtual RESULT update(const Param &param);
  virtual void term();

  int getType() const { return type; }
  f32 getLastFrame() const { return (flags & FLAG_STANBY) != 0 ? life : 9999.0f; }

private:
  u32 flags;
  gf::GF_OBJ_HANDLE *handle;
  gf::GfEvtModel *model;
  CharaDysUpdater *dys;
  u8 _28[0x30 - 0x28];
  int type;
  f32 life;
  const char *name;
};

static_assert(sizeof(CharaPlayAction) == 0x40, "");

} // namespace event
