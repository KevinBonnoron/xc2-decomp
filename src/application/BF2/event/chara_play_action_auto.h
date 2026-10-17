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
class GfObj;
} // namespace gf

namespace event {

class CharaDysUpdater;

class CharaPlayActionAuto : public ICmd {
public:
  enum {
    FLAG_MESSAGE = 1 << 0,
    FLAG_STANBY = 1 << 1,
    FLAG_PLAY = 1 << 2,
  };

  enum {
    TYPE_TALK = 1,
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
    fw::debug::drawFont(titleX, titleY, "[ACTION_AUTO]");
    fw::debug::drawFont(x, y - 55, "life(%.1f)", life);
    fw::debug::drawFont(x - 70, y - 40, "TALK");
  }
  virtual ~CharaPlayActionAuto();
  void stanby(f32 life);
  void play(gf::GfObj *obj) const;
  void idle();
  virtual void init();
  virtual RESULT update(const Param &param);
  virtual void term();

private:
  u32 flags;
  gf::GF_OBJ_HANDLE *handle;
  CharaDysUpdater *dys;
  f32 life;
};

static_assert(sizeof(CharaPlayActionAuto) == 0x28, "");

} // namespace event
