#pragma once
#include "event/shaker_res.h"
#include "event/shaker_updater.h"
#include "types.h"

namespace event {

class Shaker {
public:
  static constexpr u32 RES_COUNT = 8;

  enum {
    FLAG_PLAY = 1 << 0,
    FLAG_LIFE = 1 << 1,
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

  bool isPlay() const { return (unknown08 & FLAG_PLAY) != 0; }

private:
  u32 unknown08;                  // Inferred role: flags; original member name unknown.
  ShakerRes unknown10[RES_COUNT]; // Inferred role: res list; original member name unknown.
  u32 unknown310;                 // Inferred role: res count; original member name unknown.
  ShakerRes *unknown318;          // Inferred role: current; original member name unknown.
  f32 unknown320;                 // Inferred role: frame; original member name unknown.
  f32 unknown324;                 // Inferred role: play frame; original member name unknown.
  f32 unknown328;                 // Inferred role: life; original member name unknown.
  f32 unknown32c;                 // Inferred role: fade in; original member name unknown.
  f32 unknown330;                 // Inferred role: fade out; original member name unknown.
  ShakerUpdater unknown338;       // Inferred role: updater; original member name unknown.
};

static_assert(sizeof(Shaker) == 0xc90, "");

} // namespace event
