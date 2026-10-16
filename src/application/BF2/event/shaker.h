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

  bool isPlay() const { return (flags & FLAG_PLAY) != 0; }

private:
  u32 flags;
  ShakerRes resList[RES_COUNT];
  u32 resCount;
  ShakerRes *current;
  f32 frame;
  f32 playFrame;
  f32 life;
  f32 fadeIn;
  f32 fadeOut;
  ShakerUpdater updater;
};

static_assert(sizeof(Shaker) == 0xc90, "");

} // namespace event
