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
  bool isEnd() const { return endFrame <= frame; }
  bool isPlay() const { return (state & STATE_PLAY) != 0; }
  f32 getKeyFrame(size_t index) const { return frames[index]; }

protected:
  u32 state;
  mm::mtl::FixedVector<f32, KEY_COUNT> frames;
  CV_TYPE cv;
  f32 frame;
  f32 endFrame;
  size_t index;
  f32 alpha;
};

static_assert(sizeof(AnmBase) == 0x78, "");

} // namespace event
