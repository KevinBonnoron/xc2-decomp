#pragma once
#include "event/env_transfer_event.h"
#include "event/env_transfer_field.h"
#include "event/i_manager.h"
#include "gf/data/gf_data_map.h"
#include "mm_mtl/singleton.h"
#include "types.h"

enum EVT_cloudtype {
  EVT_CLOUDTYPE_DEFAULT,
  EVT_CLOUDTYPE_HIGH,
  EVT_CLOUDTYPE_LOW,
};

namespace event {

class EnvManager : public IManager, public mm::mtl::Singleton<EnvManager> {
public:
  enum COLORFILTER_TYPE {
    COLORFILTER_TYPE_STOP,
    COLORFILTER_TYPE_PLAY,
    COLORFILTER_TYPE_FADE,
  };

  enum {
    FLAG_CLOCK_STOP = 1 << 0,
    FLAG_AUTO_RESET_SCENE = 1 << 1,
    FLAG_WEATHER_TYPE = 1 << 2,
    FLAG_GIMMICK_POP_WAIT = 1 << 3,
    FLAG_MOT_BLUR = 1 << 4,
    FLAG_TONE_MAP = 1 << 5,
  };

  enum {
    DISP_FLAG_DISP = 1 << 0,
  };

  EnvManager();
  virtual ~EnvManager() {}
  void setCloudSea(EVT_cloudtype cloudType);
  void clear();
  void setMotBlur(bool isEnable);
  void setToneMap(bool isEnable, f32 toneMap);
  void login();
  void logout();
  void update();
  void updateColorFilter();
  void updateMotBlur();
  void updateToneMap();
  void render();
  void setClockStop(bool isStop);
  void setClock(const char *clock);
  void setClock(f32 clock);
  void setMapWeatherID(gf::WEATHERID weather, f32 frame);
  void setWeatherType(gf::WEATYPE type);
  void startGimmickPopWait();
  void endGimmickPopWait();
  bool isGimmickPopWaiting() const;
  void setColorFilter(COLORFILTER_TYPE type, int filter, int subFilter, f32 frame);
  void stopVignette();
  void playVignette(int filter, int subFilter);
  void saveTransferEnvironment(u32 fromEventID, u32 toEventID);
  bool hasTransferEnvironment(u32 eventID) const;
  void loadTransferEnvironment(u32 eventID);
  void loadFieldEnvironment();
  void setAutoResetSceneEnable(bool isEnable);
  void resetScene();
  void setDisp(bool isDisp);
  bool isDisp() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  u32 unknown10;              // Inferred role: flags; original member name unknown.
  u32 unknown14;              // Inferred role: disp flags; original member name unknown.
  u32 unknown18;              // Inferred role: clock hour; original member name unknown.
  u32 unknown1c;              // Inferred role: clock minute; original member name unknown.
  EVT_cloudtype unknown20;    // Inferred role: cloud type; original member name unknown.
  COLORFILTER_TYPE unknown24; // Inferred role: color filter state; original member name unknown.
  int unknown28;              // Inferred role: color filter; original member name unknown.
  int unknown2c;              // Inferred role: color sub filter; original member name unknown.
  f32 unknown30;              // Inferred role: color filter frame; original member name unknown.
  int unknown34;              // Inferred role: color filter count; original member name unknown.
  u32 unknown38;              // Inferred role: vignette handle; original member name unknown.
  f32 unknown3c;              // Inferred role: tone map; original member name unknown.
  EnvTransferEvent unknown40; // Inferred role: transfer event; original member name unknown.
  EnvTransferField unknown60; // Inferred role: transfer field; original member name unknown.
};

static_assert(sizeof(EnvManager) == 0x78, "");

} // namespace event
