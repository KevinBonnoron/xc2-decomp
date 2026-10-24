#pragma once
#include "event/cam_base.h"
#include "event/cam_field.h"
#include "event/cam_hands.h"
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
  u32 getScreenID() const { return unknown64; }
  void changeActive(CamBase *cam);
  CamHands *getHands() { return &unknownb0; }
  CamHands *activateHands() {
    changeActive(&unknownb0);
    return &unknownb0;
  }
  CamMotion *activateMotion() {
    changeActive(&unknownbb0);
    return &unknownbb0;
  }
  void start();
  void end();
  virtual void update(const FrameInfo &info);
  virtual void render(const mm::Col4 &color);
  virtual void tail();

private:
  SetEnable unknown40;    // Inferred role: set enable; original member name unknown.
  SetTargetPos unknown48; // Inferred role: set target pos; original member name unknown.
  SetFov unknown50;       // Inferred role: set fov; original member name unknown.
  SetNearfar unknown58;   // Inferred role: set nearfar; original member name unknown.
  u8 _60[0x64 - 0x60];
  u32 unknown64; // Inferred role: screen id; original member name unknown.
  u8 _68[0x70 - 0x68];
  CamField unknown70;                // Inferred role: field; original member name unknown.
  CamHands unknownb0;                // Inferred role: hands; original member name unknown.
  CamMotion unknownbb0;              // Inferred role: motion; original member name unknown.
  CamBase *unknownc70;               // Inferred role: active; original member name unknown.
  CmdQueue<CMD_COUNT, 0> unknownc78; // Inferred role: cmd queue; original member name unknown.
};

static_assert(sizeof(CamObj) == 0x15d0, "");

} // namespace event
