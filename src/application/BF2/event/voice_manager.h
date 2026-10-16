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
    FLAG_AUTO_VOICE_MODE = 1 << 0,
    FLAG_LIPSYNC = 1 << 1,
    FLAG_PAUSE = 1 << 2,
  };

  enum {
    DISP_FLAG_DISP = 1 << 0,
  };

  bool playAuto(const char *name, f32 delay, IVoiceEvent *event) {
    if ((flags & FLAG_AUTO_VOICE_MODE) == 0) {
      return false;
    }
    const char *path = maker.makePath(name);
    if (path == nullptr) {
      return false;
    }
    return play(path, delay, event);
  }

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
      flags |= flag;
    } else {
      flags &= ~flag;
    }
  }

  u32 flags;
  u32 dispFlags;
  VoiceMaker maker;
  VoicePlayer player;
  VoiceOneShoter oneShoter;
};

static_assert(sizeof(VoiceManager) == 0x720, "");

} // namespace event
