#pragma once
#include "mm_mtl/bitflag.h"
#include "types.h"

namespace event {

class CharaWeightPlayer;

class CharaWinkPlayer {
public:
  typedef void (CharaWinkPlayer::*State)();

  enum {
    FLAG_DISABLE_IDLE = 0,
    FLAG_MAX = 32,
  };

  CharaWinkPlayer();
  virtual ~CharaWinkPlayer() {}

  void create(CharaWeightPlayer *weight);
  void destroy();
  void update(f32 delta) {
    if (mWeight == nullptr) {
      return;
    }

    State state = this->state;
    while (state != nullptr) {
      (this->*state)();
      if (state == this->state) {
        break;
      }
      state = this->state;
    }
  }

  void open(bool isDirect);
  void idle(bool isDirect);
  void idle_start();
  void close(bool isDirect);
  void idle_waiting();
  void idle_wink();

private:
  mm::mtl::BitFlag<FLAG_MAX> flags;
  CharaWeightPlayer *mWeight;
  State state;
  int mCounter;
  const char *mStatus;
};

static_assert(sizeof(CharaWinkPlayer) == 0x38, "");

} // namespace event
