#pragma once
#include "event/cam_base.h"
#include "event/cam_field.h"
#include "event/cam_motion.h"
#include "event/cmd_queue.h"
#include "event/i_cmd.h"
#include "types.h"

namespace event {

class CamObj : public CamBase {
public:
  static constexpr u32 CMD_COUNT = 8;

  class SetEnable : public ICmd {
  public:
    virtual ~SetEnable() {}
    virtual RESULT update(const Param &param);
  };

  class SetTargetPos : public ICmd {
  public:
    virtual ~SetTargetPos() {}
    virtual RESULT update(const Param &param);
  };

  class SetFov : public ICmd {
  public:
    virtual ~SetFov() {}
    virtual RESULT update(const Param &param);
  };

  class SetNearfar : public ICmd {
  public:
    virtual ~SetNearfar() {}
    virtual RESULT update(const Param &param);
  };

  CamObj(u32 screenID, bool isFocal, bool isStreamMode);
  virtual ~CamObj();
  u32 getScreenID() const { return mScreenID; }
  void changeActive(CamBase *cam);
  void start();
  void end();
  virtual void update(const FrameInfo &info);
  virtual void render(const mm::Col4 &color);
  virtual void tail();

private:
  SetEnable mSetEnable;
  SetTargetPos mSetTargetPos;
  SetFov mSetFov;
  SetNearfar mSetNearfar;
  u8 _60[0x64 - 0x60];
  u32 mScreenID;
  CamField mField;
  u8 _b0[0xbb0 - 0xb0];
  CamMotion mMotion;
  CamBase *mActive;
  CmdQueue<CMD_COUNT, 0> mCmdQueue;
};

static_assert(sizeof(CamObj) == 0x15d0, "");

} // namespace event
