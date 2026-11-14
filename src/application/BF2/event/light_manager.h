#pragma once
#include "event/i_manager.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class LightEvt;

class LightManager : public IManager, public mm::mtl::Singleton<LightManager> {
public:
  static constexpr u32 OFFSCR_LIGHT_UNKNOWN_4 = 4; // Inferred role: offscr light count; original name unknown.

  static const char *OFF_PATH; // Name given by the xc2 symbol _ZN5event12LightManager8OFF_PATHE.

  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: stream mode flag; original name unknown.
  };

  enum {
    DISP_FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: light flag; original name unknown.
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
  u32 unknown10;                               // Inferred role: disp flags; original member name unknown.
  u32 unknown14;                               // Inferred role: flags; original member name unknown.
  LightEvt *unknown18[OFFSCR_LIGHT_UNKNOWN_4]; // Inferred role: off scr lights; original member name unknown.
  LightEvt *unknown38;                         // Inferred role: evt light; original member name unknown.
};

static_assert(sizeof(LightManager) == 0x40, "");

} // namespace event
