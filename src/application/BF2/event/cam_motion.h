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
  u32 unknown40;   // Inferred role: flags; original member name unknown.
  void *unknown48; // Inferred role: eva data; original member name unknown.
  void *unknown50; // Inferred role: eff data; original member name unknown.
  u8 _58[0x60 - 0x58];
  CamEvaPlayer unknown60;    // Inferred role: eva player; original member name unknown.
  CamEvaPlayerEff unknowna0; // Inferred role: eff player; original member name unknown.
};

static_assert(sizeof(CamMotion) == 0xc0, "");

} // namespace event
