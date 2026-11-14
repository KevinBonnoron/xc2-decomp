#pragma once
#include "event/shaker_res.h"
#include "event/shaker_updater.h"
#include "types.h"

namespace event {

class Shaker {
public:
  static constexpr u32 RES_UNKNOWN_8 = 8; // Inferred role: res count; original name unknown.

  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: play flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: life flag; original name unknown.
  };

  Shaker();
  virtual ~Shaker() {}
  void create();
  void destroy();
  void exec(f32 delta, f32 streamDelta);
  void stop();
  f32 getAlpha() const;
  void tail();
  u32 registerShake(const char *name);
  u32 search(const char *name);
  bool play(u32 index, f32 life, f32 fadeIn, f32 fadeOut);

  bool isPlay() const { return (unknown08 & FLAG_UNKNOWN_0) != 0; }

private:
  u32 unknown08;                      // Inferred role: flags; original member name unknown.
  ShakerRes unknown10[RES_UNKNOWN_8]; // Inferred role: res list; original member name unknown.
  u32 unknown310;                     // Inferred role: res count; original member name unknown.
  ShakerRes *unknown318;              // Inferred role: current; original member name unknown.
  f32 unknown320;                     // Inferred role: frame; original member name unknown.
  f32 unknown324;                     // Inferred role: play frame; original member name unknown.
  f32 unknown328;                     // Inferred role: life; original member name unknown.
  f32 unknown32c;                     // Inferred role: fade in; original member name unknown.
  f32 unknown330;                     // Inferred role: fade out; original member name unknown.
  ShakerUpdater unknown338;           // Inferred role: updater; original member name unknown.
};

static_assert(sizeof(Shaker) == 0xc90, "");

} // namespace event
