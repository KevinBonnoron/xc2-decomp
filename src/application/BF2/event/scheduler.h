#pragma once
#include "event/schedule_item.h"
#include "types.h"

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
  void func_turn_loop(gf::GfObj *obj);
  void func_look(gf::GfObj *obj);
  void func_return(gf::GfObj *obj);
  void func_return_loop(gf::GfObj *obj);
  void func_motion(gf::GfObj *obj);
  void func_motion_loop(gf::GfObj *obj);
  void func_item(gf::GfObj *obj);
  void func_item_loop(gf::GfObj *obj);
  void setUse(USE use, bool isUse);
  bool chkUse(USE use) const { return (mUse & use) != 0; }
  bool isPlay(ORDER order) const { return mFuncs[order]; }
  gf::GF_OBJ_HANDLE *getHandle() const { return handle; }

private:
  u32 flags;
  u32 mUse;
  gf::GF_OBJ_HANDLE *handle;
  u32 mBdatId;
  u32 mType;
  u32 mAimType;
  ScheduleItem mItem;
  Func mFuncs[ORDER_COUNT];
  s32 mWait;
};

static_assert(sizeof(Scheduler) == 0x88, "");

} // namespace event
