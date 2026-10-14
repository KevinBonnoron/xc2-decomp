#pragma once
#include "types.h"
#include <stddef.h>

namespace mm {
namespace mtl {
class IAllocator;
}
} // namespace mm

namespace fw {

struct PadData {
  PadData()
      : hold(0), trigger(0), release(0), repeat(0), _10(), _28(), alxThreshold(0.2f), alyThreshold(0.2f), arxThreshold(0.2f), aryThreshold(0.2f),
        padNo(-1), _40(), _44() {}

  u32 hold;
  u32 trigger;
  u32 release;
  u32 repeat;
  u8 _10[0x28 - 0x10];
  u8 _28[0x2c - 0x28];
  f32 alxThreshold;
  f32 alyThreshold;
  f32 arxThreshold;
  f32 aryThreshold;
  int padNo;
  u8 _40[0x41 - 0x40];
  u8 _41[0x44 - 0x41];
  u8 _44[0x48 - 0x44];
};

static_assert(offsetof(PadData, alxThreshold) == 0x2c, "");
static_assert(offsetof(PadData, padNo) == 0x3c, "");
static_assert(sizeof(PadData) == 0x48, "");

class PadManager {
public:
  static const PadData *getControlPadData(int padNo);
};

class alignas(8) PadRelay {
public:
  PadRelay();
  ~PadRelay();
  void bind(int padNo, int, mm::mtl::IAllocator *allocator);
  void unbind();
  void update();
  template <typename T, typename F> void bindAction(const char *name, T *object, F function);

  u8 _00[0x38 - 0x00];
};

static_assert(sizeof(PadRelay) == 0x38, "");

} // namespace fw
