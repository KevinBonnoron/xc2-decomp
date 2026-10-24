#pragma once
#include "event/i_manager.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class LightEvt;

class LightManager : public IManager, public mm::mtl::Singleton<LightManager> {
public:
  static constexpr u32 OFFSCR_LIGHT_COUNT = 4;

  enum {
    FLAG_STREAM_MODE = 1 << 0,
  };

  enum {
    DISP_FLAG_LIGHT = 1 << 0,
  };

  LightManager();
  virtual ~LightManager() {}
  bool isStreamMode() const;
  void loadOffScrLight(u32 screenID);
  void clear();
  void update();
  void render();
  void setStreamMode(bool isStreamMode);
  void loadResource(const char *name);
  void clearOffScrLight();
  void playOffScrLight(u32 screenID);
  void loadEvtLight(const char *name);
  void clearEvtLight();
  void playEvtLight(const char *name);
  void setLightDisp(bool isDisp);
  bool isLightDisp() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  u32 unknown10;                           // Inferred role: disp flags; original member name unknown.
  u32 unknown14;                           // Inferred role: flags; original member name unknown.
  LightEvt *unknown18[OFFSCR_LIGHT_COUNT]; // Inferred role: off scr lights; original member name unknown.
  LightEvt *unknown38;                     // Inferred role: evt light; original member name unknown.
};

static_assert(sizeof(LightManager) == 0x40, "");

} // namespace event
