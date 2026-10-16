#pragma once
#include "mm_math/mm_col4.h"

namespace event {

class FadeUpdater {
public:
  FadeUpdater();
  void clear();
  void update();
  void setup(int channel);
  void reserve(bool isFadeOut, int frame, const mm::Col4 *color);
  bool isFading() const;

private:
  int mChannel;
  bool mIsReserved;
  bool mIsFadeOut;
  int frame;
  bool mHasColor;
  mm::Col4 mColor;
};

static_assert(sizeof(FadeUpdater) == 0x20, "");

} // namespace event
