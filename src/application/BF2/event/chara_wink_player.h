#pragma once
#include "mm_mtl/bitflag.h"
#include "types.h"

namespace event {

class CharaWeightPlayer;

class CharaWinkPlayer {
  friend class CharaPlayWink;

public:
  typedef void (CharaWinkPlayer::*State)();

  enum {
    FLAG_UNKNOWN_0 = 0,   // Inferred role: disable idle flag; original name unknown.
    FLAG_UNKNOWN_32 = 32, // Inferred role: max flag; original name unknown.
  };

  CharaWinkPlayer();
  virtual ~CharaWinkPlayer() {}

  void create(CharaWeightPlayer *weight);
  void destroy();
  void update(f32 delta) {
    if (unknown10 == nullptr) {
      return;
    }

    State state = this->unknown18;
    while (state != nullptr) {
      (this->*state)();
      if (state == this->unknown18) {
        break;
      }
      state = this->unknown18;
    }
  }

  void open(bool isDirect);
  void idle(bool isDirect);
  void idle_start();
  void close(bool isDirect);
  void idle_waiting();
  void idle_wink();

private:
  mm::mtl::unknown027<FLAG_UNKNOWN_32> unknown08; // Inferred role: flags; original member name unknown.
  CharaWeightPlayer *unknown10;                   // Inferred role: weight; original member name unknown.
  State unknown18;                                // Inferred role: state; original member name unknown.
  int unknown28;                                  // Inferred role: counter; original member name unknown.
  const char *unknown30;                          // Inferred role: status; original member name unknown.
};

static_assert(sizeof(CharaWinkPlayer) == 0x38, "");

} // namespace event
