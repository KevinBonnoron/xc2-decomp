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
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: stream mode flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: play eva flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: play eff flag; original name unknown.
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
