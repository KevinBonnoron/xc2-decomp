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
  bool isStreamMode() const { return (flags & FLAG_STREAM_MODE) != 0; }
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
  u32 dispFlags;
  u32 flags;
  LightEvt *mOffScrLights[OFFSCR_LIGHT_COUNT];
  LightEvt *mEvtLight;
};

static_assert(sizeof(LightManager) == 0x40, "");

} // namespace event
