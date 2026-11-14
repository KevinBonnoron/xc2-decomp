#pragma once
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace event {

class VoiceOneShoter {
public:
  static const f32 TO_SEC;                   // Name given by the xc2 symbol _ZN5event14VoiceOneShoter6TO_SECE.
  static constexpr u32 HANDLE_UNKNOWN_4 = 4; // Inferred role: handle count; original name unknown.

  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: pause flag; original name unknown.
  };

  VoiceOneShoter();
  virtual ~VoiceOneShoter() {}
  void clear();
  void stop(f32 frame);
  void update();
  bool play(const char *path, f32 volume);
  void pause(bool isPause);

private:
  u32 unknown08;                                         // Inferred role: flags; original member name unknown.
  u8 unknown0c[0x10 - 0xC];                              // Inferred role: c; original member name unknown.
  mm::mtl::FixedVector<u32, HANDLE_UNKNOWN_4> unknown10; // Inferred role: handles; original member name unknown.
};

static_assert(sizeof(VoiceOneShoter) == 0x28, "");

} // namespace event
