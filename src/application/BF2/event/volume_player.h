#pragma once
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace event {

class VolumePlayer {
public:
  static const f32 TO_SEC;                  // Name given by the xc2 symbol _ZN5event12VolumePlayer6TO_SECE.
  static constexpr u32 KEY_UNKNOWN_40 = 40; // Inferred role: key count; original name unknown.

  struct Key {
    bool unknown00; // Inferred role: change; original member name unknown.
    u32 unknown04;  // Inferred role: category; original member name unknown.
    f32 unknown08;  // Inferred role: volume; original member name unknown.
    f32 unknown0c;  // Inferred role: frame; original member name unknown.
  };

  VolumePlayer();
  virtual ~VolumePlayer() {}
  void clear();
  void update();
  void change(u32 category, f32 volume, f32 frame);
  void reset(u32 category, f32 volume, f32 frame);

private:
  mm::mtl::FixedVector<Key, KEY_UNKNOWN_40> unknown08; // Inferred role: keys; original member name unknown.
};

static_assert(sizeof(VolumePlayer) == 0x290, "");

} // namespace event
