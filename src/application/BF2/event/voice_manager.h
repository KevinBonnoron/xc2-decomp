#pragma once
#include "event/i_manager.h"
#include "event/voice_maker.h"
#include "event/voice_one_shoter.h"
#include "event/voice_player.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class VoiceManager : public IManager, public mm::mtl::Singleton<VoiceManager> {
public:
  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: auto voice mode flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: lipsync flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: pause flag; original name unknown.
  };

  enum {
    DISP_FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: disp flag; original name unknown.
  };

  bool playAuto(const char *name, f32 delay, IVoiceEvent *event);

  // Inferred role: player accessor; original name unknown.
  VoicePlayer &unknown001() { return unknown230; }

  VoiceManager();
  virtual ~VoiceManager() {}
  void clear();
  void startScene();
  void update();
  void render();
  void setAutoVoiceMode(bool isAutoVoiceMode, const char *directory, const char *name);
  void setMultipleMode(bool isMultipleMode);
  void preloadAuto(f32 frame, const char *name);
  void preload(f32 frame, const char *name);
  bool play(const char *name, f32 delay, IVoiceEvent *event);
  bool playOneshot(const char *name, f32 volume);
  void pause(bool isPause);
  void setDisp(bool isDisp);
  bool isDisp() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  void setFlag(u32 flag, bool isSet) {
    if (isSet) {
      unknown10 |= flag;
    } else {
      unknown10 &= ~flag;
    }
  }

  u32 unknown10;             // Inferred role: flags; original member name unknown.
  u32 unknown14;             // Inferred role: disp flags; original member name unknown.
  VoiceMaker unknown18;      // Inferred role: maker; original member name unknown.
  VoicePlayer unknown230;    // Inferred role: player; original member name unknown.
  VoiceOneShoter unknown6f8; // Inferred role: one shoter; original member name unknown.
};

static_assert(sizeof(VoiceManager) == 0x720, "");

} // namespace event
