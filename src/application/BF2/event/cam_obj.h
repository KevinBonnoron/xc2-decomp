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
  static constexpr u32 CMD_UNKNOWN_8 = 8; // Inferred role: cmd count; original name unknown.

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
  CamHands *getHands() { return &m_camHands; }
  // Inferred role: motion camera; original name unknown.
  CamMotion *unknown005() { return &m_camMotion; }
  CamHands *activateHands() {
    changeActive(&m_camHands);
    return &m_camHands;
  }
  CamMotion *activateMotion() {
    changeActive(&m_camMotion);
    return &m_camMotion;
  }
  void start();
  void end();
  virtual void update(const FrameInfo &info);
  virtual void render(const mm::Col4 &color);
  virtual void tail();

private:
  SetEnable m_setEnable;       // Inferred role: set enable; original member name unknown.
  SetTargetPos m_setTargetPos; // Inferred role: set target pos; original member name unknown.
  SetFov m_setFov;             // Inferred role: set fov; original member name unknown.
  SetNearfar m_setNearfar;     // Inferred role: set nearfar; original member name unknown.
  u32 unknown60;               // Inferred role: unknown; zeroed with unknown64 by one 64-bit store in the constructor (0x71000b4674), no other CamObj function reads it; original member name unknown.
  u32 unknown64;               // Inferred role: screen id; original member name unknown.
  u8 _68[0x70 - 0x68];
  CamField m_camField;                   // Inferred role: field; original member name unknown.
  CamHands m_camHands;                   // Inferred role: hands; original member name unknown.
  CamMotion m_camMotion;                 // Inferred role: motion; original member name unknown.
  CamBase *m_camBase;                    // Inferred role: active; original member name unknown.
  CmdQueue<CMD_UNKNOWN_8, 0> unknownc78; // Inferred role: cmd queue; original member name unknown.
};

static_assert(sizeof(CamObj) == 0x15d0, "");

} // namespace event
