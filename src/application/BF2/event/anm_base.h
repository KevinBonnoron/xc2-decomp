#pragma once
#include "event/curve.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"
#include <stddef.h>

namespace event {

class AnmBase {
public:
  static constexpr size_t KEY_COUNT = 16;

  enum {
    STATE_FIRST = 1 << 0,
    STATE_PLAY = 1 << 1,
    STATE_UPDATE = 1 << 2,
  };

  AnmBase();
  virtual ~AnmBase() {}
  void clear();
  void update(f32 delta);
  void getIndex_Alpha(size_t &index, f32 &alpha, f32 frame, size_t startIndex, f32 startAlpha) const;
  void replay();
  size_t count() const;
  void append(f32 frame);
  void setCv(CV_TYPE cv);
  bool isEnd() const { return unknown60 <= unknown5c; }
  bool isPlay() const { return (unknown08 & STATE_PLAY) != 0; }
  f32 getKeyFrame(size_t index) const { return unknown10[index]; }

protected:
  u32 unknown08;                                  // Inferred role: state; original member name unknown.
  mm::mtl::FixedVector<f32, KEY_COUNT> unknown10; // Inferred role: frames; original member name unknown.
  CV_TYPE m_cv;
  f32 unknown5c;    // Inferred role: frame; original member name unknown.
  f32 unknown60;    // Inferred role: end frame; original member name unknown.
  size_t unknown68; // Inferred role: index; original member name unknown.
  f32 unknown70;    // Inferred role: alpha; original member name unknown.
};

static_assert(sizeof(AnmBase) == 0x78, "");

} // namespace event
