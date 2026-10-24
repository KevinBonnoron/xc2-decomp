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
  int unknown00;      // Inferred role: channel; original member name unknown.
  bool unknown04;     // Inferred role: is reserved; original member name unknown.
  bool unknown05;     // Inferred role: is fade out; original member name unknown.
  int unknown08;      // Inferred role: frame; original member name unknown.
  bool unknown0c;     // Inferred role: has color; original member name unknown.
  mm::Col4 unknown10; // Inferred role: color; original member name unknown.
};

static_assert(sizeof(FadeUpdater) == 0x20, "");

} // namespace event
