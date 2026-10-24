#pragma once
#include "event/schedule_item.h"
#include "types.h"

enum EVT_aimtype : int;

namespace gf {
class GfObj;
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class Scheduler {
public:
  typedef void (Scheduler::*Func)(gf::GfObj *obj);

  enum ORDER {
    ORDER_FLD2EVT,
    ORDER_EVT2IDLE,
    ORDER_EVT2FLD,
    ORDER_COUNT,
  };

  enum USE {
    USE_TURN = 1 << 2,
    USE_RETURN = 1 << 3,
    USE_LOOK = 1 << 4,
    USE_LOOK_RESET = 1 << 5,
    USE_FADE = 1 << 6,
    USE_ITEM = 1 << 7,
  };

  enum {
    FLAG_LOOK_START = 1 << 0,
  };

  Scheduler(gf::GF_OBJ_HANDLE *handle, u32 type);
  Scheduler(const Scheduler *scheduler, u32 type);
  virtual ~Scheduler();
  void func_stanby(gf::GfObj *obj);
  void setup();
  void exec();
  void play(ORDER order);
  void func_fld2evt(gf::GfObj *obj);
  void func_evt2idle(gf::GfObj *obj);
  void func_evt2fld(gf::GfObj *obj);
  void func_motionEnd(gf::GfObj *obj);
  void func_motionEnd_loop(gf::GfObj *obj);
  void func_turn(gf::GfObj *obj);
  static f32 getRotY(gf::GfObj *obj, gf::GfObj *target);
  void func_turn_loop(gf::GfObj *obj);
  void func_look(gf::GfObj *obj);
  static void lookTo(bool isLook, gf::GfObj *obj, gf::GfObj *target, EVT_aimtype aim, bool isApply);
  void func_return(gf::GfObj *obj);
  void func_return_loop(gf::GfObj *obj);
  void func_motion(gf::GfObj *obj);
  void func_motion_loop(gf::GfObj *obj);
  void func_item(gf::GfObj *obj);
  void func_item_loop(gf::GfObj *obj);
  void setUse(USE use, bool isUse);
  static f32 getRotY(gf::GfObj *obj);
  bool chkUse(USE use) const { return (unknown0c & use) != 0; }
  bool isPlay(ORDER order) const { return unknown50[order]; }
  gf::GF_OBJ_HANDLE *getHandle() const { return unknown10; }

private:
  u32 unknown08;                // Inferred role: flags; original member name unknown.
  u32 unknown0c;                // Inferred role: use; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown10; // Inferred role: handle; original member name unknown.
  u32 unknown18;                // Inferred role: bdat id; original member name unknown.
  u32 unknown1c;                // Inferred role: type; original member name unknown.
  u32 unknown20;                // Inferred role: aim type; original member name unknown.
  ScheduleItem unknown28;       // Inferred role: item; original member name unknown.
  Func unknown50[ORDER_COUNT];  // Inferred role: funcs; original member name unknown.
  s32 unknown80;                // Inferred role: wait; original member name unknown.
};

static_assert(sizeof(Scheduler) == 0x88, "");

} // namespace event
