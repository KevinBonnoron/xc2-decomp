#pragma once
#include "event/cam_base.h"
#include "event/cam_eva_player.h"
#include "event/cam_eva_player_eff.h"
#include "types.h"

namespace mm {
struct Vec3;
}

namespace event {

class CamMotion : public CamBase {
public:
  enum {
    FLAG_STREAM_MODE = 1 << 0,
    FLAG_PLAY_EVA = 1 << 1,
    FLAG_PLAY_EFF = 1 << 2,
  };

  CamMotion(bool isFocal, bool isStreamMode);
  virtual ~CamMotion();
  void stop();
  virtual void update(const FrameInfo &info);
  void play(const char *name, const mm::Vec3 &offset);

private:
  u32 flags;
  void *mEvaData;
  void *mEffData;
  u8 _58[0x60 - 0x58];
  CamEvaPlayer mEvaPlayer;
  CamEvaPlayerEff mEffPlayer;
};

static_assert(sizeof(CamMotion) == 0xc0, "");

} // namespace event
