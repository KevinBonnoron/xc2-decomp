#pragma once
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace event {

class VolumePlayer {
public:
  static const f32 TO_SEC;
  static constexpr u32 KEY_COUNT = 40;

  struct Key {
    bool isChange;
    u32 category;
    f32 volume;
    f32 frame;
  };

  VolumePlayer();
  virtual ~VolumePlayer() {}
  void clear();
  void update();
  void change(u32 category, f32 volume, f32 frame);
  void reset(u32 category, f32 volume, f32 frame);

private:
  mm::mtl::FixedVector<Key, KEY_COUNT> mKeys;
};

static_assert(sizeof(VolumePlayer) == 0x290, "");

} // namespace event
