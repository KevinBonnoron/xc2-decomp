#pragma once
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace event {

class VoiceOneShoter {
public:
  static const f32 TO_SEC;
  static constexpr u32 HANDLE_COUNT = 4;

  enum {
    FLAG_PAUSE = 1 << 0,
  };

  VoiceOneShoter();
  virtual ~VoiceOneShoter() {}
  void clear();
  void stop(f32 frame);
  void update();
  bool play(const char *path, f32 volume);
  void pause(bool isPause);

private:
  u32 flags;
  u8 _C[0x10 - 0xC];
  mm::mtl::FixedVector<u32, HANDLE_COUNT> handles;
};

static_assert(sizeof(VoiceOneShoter) == 0x28, "");

} // namespace event
